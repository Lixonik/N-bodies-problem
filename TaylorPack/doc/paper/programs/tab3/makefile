CC=gcc
CFLAGS=-O3
LFLAGS=-lgmp -lm -s
TAYLOR=taylor

RTBP=main-rtbp.o taylor.o

all: rtbp difer

rtbp: $(RTBP)
	$(CC) $(CFLAGS) $(RTBP) -o rtbp $(LFLAGS)

main-rtbp.o: main-rtbp.c taylor.h
	$(CC) $(CFLAGS) -c main-rtbp.c

taylor.o: taylor.c taylor.h
	$(CC) $(CFLAGS) -c taylor.c

taylor.c: rtbp.in
	$(TAYLOR) -name rtbp -o taylor.c -step -jet -sqrt rtbp.in

taylor.h:
	$(TAYLOR) -name rtbp -o taylor.h -gmp -header

difer: difer.c taylor.h
	$(CC) $(CFLAGS) difer.c -o difer $(LFLAGS)

clean:
	rm -f *.o *.h
	rm -f taylor.c
	rm -f rtbp difer
