CC=cc
CFLAGS=-O -Aa
LFLAGS=-lm -s
TAYLOR=taylor

HAM=ham.o taylor.o

ham: $(HAM)
	$(CC) $(CFLAGS) $(HAM) -o ham $(LFLAGS)

ham.o: ham.c taylor.h
	$(CC) +O0 -Aa -Wall -c ham.c

taylor.o: taylor.c taylor.h
	$(CC) $(CFLAGS) -c taylor.c

taylor.c: rtbp.in
	$(TAYLOR) -name rtbp -o taylor.c -step -jet -sqrt rtbp.in

taylor.h:
	$(TAYLOR) -name rtbp -o taylor.h -header

clean:
	rm -f *.o *.h
	rm -f taylor.c
	rm -f ham
