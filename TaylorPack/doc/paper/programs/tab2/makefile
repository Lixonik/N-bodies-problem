CC=gcc
CFLAGS=-O3
LFLAGS=-lm -s
TAYLOR=taylor

DRFT=drift.o taylor.o

all: drift taz

drift: $(DRFT)
	$(CC) $(CFLAGS) $(DRFT) -o drift $(LFLAGS)

drift.o: drift.c taylor.h
	$(CC) -ffloat-store -Wall -c drift.c

taylor.o: taylor.c taylor.h
	$(CC) $(CFLAGS) -c taylor.c

taylor.c: rtbp.in
	$(TAYLOR) -name rtbp -o taylor.c -step -jet -sqrt rtbp.in

taylor.h:
	$(TAYLOR) -name rtbp -o taylor.h -header

taz: taz.c
	$(CC) $(CFLAGS) taz.c -o taz $(LFLAGS)

clean:
	rm -f *.o *.h
	rm -f taylor.c
	rm -f drift taz
