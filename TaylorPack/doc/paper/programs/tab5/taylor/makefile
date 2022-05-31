CC=gcc
CFLAGS=-O3
LFLAGS=-lm -s
TAYLOR=taylor

all: lorenz rtbp pepe

LRNZ=main-lorenz.o lorenz.o

lorenz: $(LRNZ)
	$(CC) $(CFLAGS) $(LRNZ) -o lorenz $(LFLAGS)

main-lorenz.o: main-lorenz.c lorenz.h ../params.h
	$(CC) -c $(CFLAGS) main-lorenz.c

lorenz.o: lorenz.c lorenz.h
	$(CC) -c $(CFLAGS) lorenz.c

lorenz.c: lorenz.in
	$(TAYLOR) -name lorenz -o lorenz.c -jet -headername lorenz.h lorenz.in

lorenz.h:
	$(TAYLOR) -name lorenz -o lorenz.h -header lorenz.in

RTBP=main-rtbp.o rtbp.o

rtbp: $(RTBP)
	$(CC) $(CFLAGS) $(RTBP) -o rtbp $(LFLAGS)

main-rtbp.o: main-rtbp.c rtbp.h ../params.h
	$(CC) -c $(CFLAGS) main-rtbp.c

rtbp.o: rtbp.c rtbp.h
	$(CC) -c $(CFLAGS) rtbp.c

rtbp.c: rtbp.in
	$(TAYLOR) -name rtbp -o rtbp.c -jet -headername rtbp.h rtbp.in

rtbp.h:
	$(TAYLOR) -name rtbp -o rtbp.h -header rtbp.in

PEPE=main-pepe.o pepe.o

pepe: $(PEPE)
	$(CC) $(CFLAGS) $(PEPE) -o pepe $(LFLAGS)

main-pepe.o: main-pepe.c pepe.h ../params.h
	$(CC) -c $(CFLAGS) main-pepe.c

pepe.o: pepe.c pepe.h
	$(CC) -c $(CFLAGS) pepe.c

pepe.c: pepe.in
	$(TAYLOR) -name pepe -o pepe.c -jet -headername pepe.h pepe.in

pepe.h:
	$(TAYLOR) -name pepe -o pepe.h -header pepe.in

clean:
	rm -f *.o
	rm -f lorenz.c rtbp.c pepe.c
	rm -f lorenz.h rtbp.h pepe.h
	rm -f lorenz rtbp pepe
