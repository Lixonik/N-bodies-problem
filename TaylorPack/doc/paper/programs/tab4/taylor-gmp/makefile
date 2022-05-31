CC=gcc
CFLAGS=-O3
LFLAGS=-lgmp -lm -s
TAYLOR=taylor

all: lorenz pepe rtbp

LRNZ=main-lorenz.o lorenz.o

lorenz: $(LRNZ)
	$(CC) $(CFLAGS) $(LRNZ) -o lorenz $(LFLAGS)

main-lorenz.o: main-lorenz.c lorenz.h
	$(CC) $(CFLAGS) -c main-lorenz.c

lorenz.o: lorenz.c lorenz.h
	$(CC) $(CFLAGS) -c lorenz.c

lorenz.c: lorenz.in
	$(TAYLOR) -name lorenz -o lorenz.c -step -jet -headername lorenz.h lorenz.in

lorenz.h: lorenz.in
	$(TAYLOR) -name lorenz -o lorenz.h -gmp -header lorenz.in

RTBP=main-rtbp.o rtbp.o

rtbp: $(RTBP)
	$(CC) $(CFLAGS) $(RTBP) -o rtbp $(LFLAGS)

main-rtbp.o: main-rtbp.c rtbp.h
	$(CC) $(CFLAGS) -c main-rtbp.c

rtbp.o: rtbp.c rtbp.h
	$(CC) $(CFLAGS) -c rtbp.c

rtbp.c: rtbp.in
	$(TAYLOR) -name rtbp -o rtbp.c -step -jet -sqrt -headername rtbp.h rtbp.in

rtbp.h: rtbp.in
	$(TAYLOR) -name rtbp -o rtbp.h -gmp -header rtbp.in

PEPE=main-pepe.o pepe.o

pepe: $(PEPE)
	$(CC) $(CFLAGS) $(PEPE) -o pepe $(LFLAGS)

main-pepe.o: main-pepe.c pepe.h
	$(CC) $(CFLAGS) -c main-pepe.c

pepe.o: pepe.c pepe.h
	$(CC) $(CFLAGS) -c pepe.c

pepe.c: pepe.in
	$(TAYLOR) -name pepe -o pepe.c -step -jet -headername pepe.h pepe.in

pepe.h: pepe.in
	$(TAYLOR) -name pepe -o pepe.h -gmp -header pepe.in

clean:
	rm -f *.o

reallyclean:
	rm -f *.o
	rm -f *.h
	rm -f lorenz rtbp pepe
	rm -f lorenz.c rtbp.c pepe.c
