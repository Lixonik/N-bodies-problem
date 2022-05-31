import matplotlib.pyplot as plt

q = input("A number of bodies: ")

option = input("A method of integration('rk4', 'ralston', 'adams', 'rk5', 'adams_10' or 'taylor'): ")
namef = f"data_{option}({q}).txt"
f1 = open(namef, 'r')
x1_list = []
y1_list = []
z1_list = []
x2_list = []
y2_list = []
z2_list = []
x3_list = []
y3_list = []
z3_list = []
kepler_x = []
kepler_y = []
kepler_z = []
f1.readline()
while True:
    line1 = f1.readline()
    if not line1:
    # or line1.split()[-1] == '237258':
        # print(line1)
        break
    vecs = list(map(float, line1.strip('  ').split()))
    x1_list.append(vecs[0])
    y1_list.append(vecs[1])
    z1_list.append(vecs[2])
    x2_list.append(vecs[3])
    y2_list.append(vecs[4])
    z2_list.append(vecs[5])
    x3_list.append(vecs[6])
    y3_list.append(vecs[7])
    z3_list.append(vecs[8])
    # kepler_x.append(vecs[6])
    # kepler_y.append(vecs[7])
    # kepler_z.append(vecs[8])

print("read complete")
print("charts are being made…")

print(len(z1_list))
# Visualisation of orbits ↓
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection="3d")
ax.plot(x1_list, y1_list, z1_list, color="gold")
ax.plot(x2_list, y2_list, z2_list, color="blue")
ax.plot(x3_list, y3_list, z3_list, color="red")
# ax.plot(kepler_x, kepler_y, kepler_z, color="green")
ax.scatter(x1_list[-1], y1_list[-1], z1_list[-1], color="gold", marker=".", s=50, label="Sun")
ax.scatter(x2_list[-1], y2_list[-1], z2_list[-1], color="blue", marker=".", s=50, label="Earth")
ax.scatter(x3_list[-1], y3_list[-1], z3_list[-1], color="red", marker=".", s=50, label="Mercury")
# ax.scatter(kepler_x[-1], kepler_y[-1], kepler_z[-1], color="green", marker="o", s=50, label="Kepler")

ax.set_xlabel("x-coordinate", fontsize=14)
ax.set_ylabel("y-coordinate", fontsize=14)
ax.set_zlabel("z-coordinate", fontsize=14)
ax.set_title("Sun – Earth – Mercury", fontsize=14)
ax.legend(loc="upper left", fontsize=14)

plt.show()
# plt.savefig("*название*.png")
