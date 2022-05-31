#######################################################################
#
#   Makefile for the taylor translator
#		
CC=gcc -O
PRECISION=256

all:     1 2 3 4 5 6 7 8 9 10 11 12

1: test1.in
	../taylor -sqrt -o 1.c -main -gmp_precision  $(PRECISION)  test1.in
	$(CC)  1.c -lgmp -lm; 
	a.out > 1;

2: test2.in
	../taylor -sqrt -o 2.c -main -gmp_precision  $(PRECISION)  test2.in
	$(CC)  2.c -lgmp -lm; 
	a.out > 2;

3: test3.in
	../taylor -sqrt -o 3.c -main -gmp_precision  $(PRECISION)  test3.in
	$(CC)  3.c -lgmp -lm; 
	a.out > 3;

4: test4.in
	../taylor -sqrt -o 4.c -main -gmp_precision  $(PRECISION)  test4.in
	$(CC)  4.c -lgmp -lm; 
	a.out > 4;

5: test5.in
	../taylor -sqrt -o 5.c -main -gmp_precision  $(PRECISION)  test5.in
	$(CC)  5.c -lgmp -lm; 
	a.out > 5;

6: test6.in
	../taylor -sqrt -o 6.c -main -gmp_precision  $(PRECISION)  test6.in
	$(CC)  6.c -lgmp -lm; 
	a.out > 6;

7: test7.in
	../taylor -sqrt -o 7.c -main -gmp_precision  $(PRECISION)  test7.in
	$(CC)  7.c -lgmp -lm; 
	a.out > 7;

8: test8.in
	../taylor -sqrt -o 8.c -main -gmp_precision  $(PRECISION)  test8.in
	$(CC)  8.c -lgmp -lm; 
	a.out > 8;

9: test9.in
	../taylor -sqrt -o 9.c -main -gmp_precision  $(PRECISION)  test9.in
	$(CC)  9.c -lgmp -lm; 
	a.out > 9;


10: test10.in
	../taylor -sqrt -o 10.c -main -gmp_precision  $(PRECISION)  test10.in
	$(CC)  10.c -lgmp -lm; 
	a.out > 10;


11: test11.in
	../taylor -sqrt -o 11.c -main -gmp_precision  $(PRECISION)  test11.in
	$(CC)  11.c -lgmp -lm; 
	a.out > 11;

12: test12.in
	../taylor -sqrt -o 12.c -main -gmp_precision  $(PRECISION)  test12.in
	$(CC)  12.c -lgmp -lm; 
	a.out > 12;



z: z.in
	../taylor -sqrt -o z.c -gmp_precision  $(PRECISION)  -step 0 -main -jet -header -sqrt   z.in
	$(CC)  z.c -lgmp -lm; 
	a.out > z;

a: a.in
	../taylor -sqrt -o a.c -gmp_precision  $(PRECISION)  -step -main -jet -header -sqrt a.in
	$(CC)  a.c -lgmp -lm; 
	a.out > a;



clean:
	/bin/rm -rf *.c  1 2 3 4 5 6 7 8 9 10 11 12  a.out z a


