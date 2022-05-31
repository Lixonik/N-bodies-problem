CC=gcc
CFLAGS=-O3
LFLAGS=-lgmp -lm -s
TAYLOR=taylor

HAM=ham.o taylor.o

ham: $(HAM)
	$(CC) $(CFLAGS) $(HAM) -o ham $(LFLAGS)

ham.o: ham.c taylor.h
	$(CC) -c $(CFLAGS) ham.c

taylor.o: taylor.c taylor.h
	$(CC) -c $(CFLAGS) taylor.c

taylor.c: rtbp.in
	$(TAYLOR) -name rtbp -o taylor.c -step -jet -sqrt rtbp.in

taylor.h:
	$(TAYLOR) -name rtbp -o taylor.h -gmp -header

clean:
	rm -f *.o *.h
	rm -f taylor.c
	rm -f ham
