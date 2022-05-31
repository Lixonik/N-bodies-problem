import os

# Спрашиваем:
# показать графики инвариантов — обсудить
# про допуски
# уточнить ТЗ
# про барик (точно ли порядок норм)

class TaylorCodeGenerator:
    def __init__(self):
        stream = open(input("Введите название файла: ") + ".txt", 'r')

        self.G = "6.67408e-20"
        self.names = []
        self.M = []
        self.calculation_M = []
        self.r = []
        self.v = []
        self.N = 0
        self.filename = ""
        self.order = -1
        self.order = int(input("Введите желаемый порядок метода Тейлора: "))
        self.step = 0.0
        self.step = float(input("Введите желаемый шаг метода Тейлора (0 -- автоподбор): "))

        for line in stream:
            if line[0] == 'N':
                self.names.append(line[line.find(' '):-1])
            elif line[0] == 'G':
                self.M.append(f"{line[line.find(' '):-1]} / G")
                self.calculation_M.append(float(line[line.find(' '):-1]) / float(self.G))
            elif line[0] == 'p':
                for rline in line[line.find('{') + 1: line.find('}') - 1].split(', '):
                    self.r.append(rline)
            elif line[0] == 'v':
                for vline in line[line.find('{') + 1: line.find('}') - 1].split(', '):
                    self.v.append(vline)

        stream.close()

        if not (len(self.names) == len(self.M) == len(self.r)/3 == len(self.v)/3):
            print("Некорректный файл!")

            return

        self.N = len(self.names)  # COUNT OF BODIES

    def __str__(self):
        string = f"Количество тел: {self.N}"

        for i in range(self.N):
            string += f"\nName: {self.names[i]}\nMass: {self.M[i]}\nr: {self.r[2*i+i%3:2*i+i%3+3]}\nv: {self.v[2*i+i%3:2*i+i%3+3]}"

        return string

    def __repr__(self):
        string = f"Количество тел: {self.N}"

        for i in range(self.N):
            string += f"\nName: {self.names[i]}\nMass: {self.M[i]}\nr: {self.r[2*i+i%3:2*i+i%3+3]}\nv: {self.v[2*i+i%3:2*i+i%3+3]}"

        return string

    def model_generation(self):
        self.filename = f"{self.N}bp"
        stream = open(self.filename + ".eq", 'w')
        stream.write(f"G = {self.G};\n")

        for i in range(self.N):
            stream.write(f"M{i + 1} = {self.M[i]};\n")

        stream.write('\n')

        for i in range(self.N):
            for axis in range(120, 123):
                stream.write(f"diff(r{i + 1}{chr(axis)}, t) = v{i + 1}{chr(axis)};\n")
            stream.write('\n')

        for i in range(self.N):
            for axis in range(120, 123):
                diff_v = f"diff(v{i + 1}{chr(axis)}, t) = "
                for j in range(self.N):
                    if (j != i):
                        diff_v += f"G*M{j + 1} * (r{j + 1}{chr(axis)} - r{i + 1}{chr(axis)}) / sqrt((r{j + 1}x - r{i + 1}x)^2 + (r{j + 1}y - r{i + 1}y)^2 + (r{j + 1}z - r{i + 1}z)^2)^3 + "
                stream.write(diff_v[:-3] + ";\n")
            stream.write('\n')

        initial_values = "initial_values = " + ", ".join(self.r+self.v)

        stream.write(initial_values[:-2] + ";\n")
        
        if self.step:
            stream.write("absolute_error_tolerance = 0;\nrelative_error_tolerance = 0;\n")

        stream.close()

    def output(self):
        main = open(f"main_{self.filename}.c", 'r')

        content = ""

        content += main.readline()
        content += "#include \"stdlib.h\"\n#include \"invariants.c\"\n"

        for line in main:
            if "/* the main loop */" in line:
                content += "\t /* the main loop */\n" + f"\t FILE *stream = fopen(\"data_taylor({self.N}).txt\", \"w\");\n"
                content += f"\t FILE *inv_stream = fopen(\"scalars_taylor({self.N}).txt\", \"w\");\n"
                content += "\t double** b = (double**)malloc(sizeof(double*)*2);\n"
                content += "\t b[0] = (double*)malloc(sizeof(double)*3);\n"
                content += "\t b[1] = (double*)malloc(sizeof(double)*3);\n\n"
                content += f"\t barycentre(xx, M, {self.N}, b, inv_stream, 0);\n"
                content += f"\t zeroing_barycentre(xx, b, {self.N});"
            elif "xx" in line and "yy" in line and "zz" in line and 'i' not in line:
                content += line + f"\t double M[{self.N}] = " + '{' + f"{str(self.calculation_M)[1:-1]}" + "};\n"
            elif "printf(\"%g" in line:
                content += "\t\t fprintf(stream," + line[line.find("%") - 1:]
                # content += "\t\t printf(\"%f\\n\", startT);\n"
            elif "exit(0);" in line:
                content += "\tfree(b[0]);\n\tfree(b[1]);\n\tfree(b);\n"
                content += "\tfclose(stream);\n\tfclose(inv_stream);\n" + "\texit(0);\n"
            elif "order=" in line and self.order != -1:
                content += line[:line.find("order=")] + f"order={self.order}, " + line[line.find("itmp"):]
            elif "dstep=" in line and self.step:
                content += line[:line.find("dstep=")] + f"dstep={self.step};\n"
            elif "itmp = " in line and self.step:
                content += line.replace('1', '0', 1)
                content += "\t\t if (startT > stopT) break;\n"
            elif "do  {" in line:
                content += line
                content += f"\t\t barycentre(xx, M, {self.N}, b, inv_stream, 1);\n"
                content += f"\t\t momentum(xx, M, {self.N}, inv_stream);\n"
                content += f"\t\t angular_momentum(xx, M, {self.N}, inv_stream);\n"
                content += f"\t\t energy(xx, M, {self.N}, inv_stream);\n"
                content += f"\t\t fprintf(inv_stream, \"\\n\");\n\n"
            else:
                content += line

        main.close()
        main = open(f"main_{self.filename}.c", 'w')
        main.write(content)
        main.close()

    def taylorun(self):
        
        os.system(f"taylor -name {self.filename} -o {self.filename}.c -jet -step {self.filename}.eq")  # taylor -name nbp -o nbp.c -jet -step nbp.eq
        os.system(f"taylor -name {self.filename} -o taylor.h -header")  # taylor -name nbp -o main_nbp.c -main_only nbp.eq
        os.system(f"taylor -name {self.filename} -o main_{self.filename}.c -main_only {self.filename}.eq")  # taylor -name nbp -o main_nbp.c -main_only nbp.eq

        stream = open(f"{self.filename}.c", 'r')
        content = ""

        for line in stream:
            content += line

        stream.close()

        stream = open(f"{self.filename}.c", 'w')
        stream.write(content)

        stream.close()

        self.output()

        os.system(f"gcc -O3 main_{self.filename}.c {self.filename}.c -lm -s -o {self.filename}")  # gcc -O3 main_nbp.c nbp.c -lm -s
        os.system(f"./{self.filename}")


if __name__ == '__main__':
    producer = TaylorCodeGenerator()
    print(producer)
    producer.model_generation()
    producer.taylorun()
