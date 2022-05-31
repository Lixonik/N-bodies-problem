CC=gcc
CFLAGS=-O3
LFLAGS=-lgmp -lm -s
TAYLOR=taylor

RTBP=rtbp.o taylor.o taylor_gmp.o

rtbp: $(RTBP)
	$(CC) $(CFLAGS) $(RTBP) -o rtbp $(LFLAGS)

rtbp.o: rtbp.c taylor_gmp.h
	$(CC) -O0 -ffloat-store -Wall -c rtbp.c

taylor.o: taylor.c taylor.h
	$(CC) $(CFLAGS) -c taylor.c

taylor.c: rtbp.in
	$(TAYLOR) -name rtbp -o taylor.c -step -jet -sqrt rtbp.in

taylor.h:
	$(TAYLOR) -name rtbp -o taylor.h -header

taylor_gmp.o: taylor_gmp.c taylor_gmp.h
	$(CC) $(CFLAGS) -c taylor_gmp.c

taylor_gmp.c:
	$(TAYLOR) -name rtbp_gmp -o taylor_gmp.c -step -jet -sqrt -headername taylor_gmp.h rtbp.in

taylor_gmp.h:
	$(TAYLOR) -name rtbp_gmp -o taylor_gmp.h -gmp -header

clean:
	rm -f *.o *.h
	rm -f taylor.c taylor_gmp.c
	rm -f rtbp
