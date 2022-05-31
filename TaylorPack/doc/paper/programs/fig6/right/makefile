CC=g++
CFLAGS=-Dx86 -I/usr/local/include/qd/
LFLAGS=-L/usr/local/lib/ -lqd -s
TAYLOR=taylor

HAM=ham.o taylor.o

ham: $(HAM)
	$(CC) $(CFLAGS) $(HAM) -o ham $(LFLAGS)

ham.o: ham.c taylor.h
	$(CC) $(CFLAGS) -c ham.c

taylor.o: taylor.c taylor.h
	$(CC) $(CFLAGS) -O3 -c taylor.c

taylor.c: rtbp.in
	$(TAYLOR) -name rtbp -o taylor.c -step -jet -sqrt rtbp.in

taylor.h:
	$(TAYLOR) -name rtbp -o taylor.h -qd_real -header

clean:
	rm -f *.o *.h
	rm -f taylor.c
	rm -f ham
