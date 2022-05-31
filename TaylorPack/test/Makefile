#######################################################################
#
#   Makefile for the taylor translator
#		
CC=gcc -O

all:     1 2 3 4 5 6 7 8 9 10 11 12

1: test1.in
	../taylor -o 1.c -main test1.in
	$(CC)  1.c -lm; 
	a.out > 1;

2: test2.in
	../taylor -o 2.c -main test2.in
	$(CC)  2.c -lm; 
	a.out > 2;

3: test3.in
	../taylor -o 3.c -main test3.in
	$(CC)  3.c -lm; 
	a.out > 3;

4: test4.in
	../taylor -o 4.c -main test4.in
	$(CC)  4.c -lm; 
	a.out > 4;

5: test5.in
	../taylor -o 5.c -main test5.in
	$(CC)  5.c -lm; 
	a.out > 5;

6: test6.in
	../taylor -o 6.c -main test6.in
	$(CC)  6.c -lm; 
	a.out > 6;

7: test7.in
	../taylor -o 7.c -main test7.in
	$(CC)  7.c -lm; 
	a.out > 7;

8: test8.in
	../taylor -o 8.c -main test8.in
	$(CC)  8.c -lm; 
	a.out > 8;

9: test9.in
	../taylor -o 9.c -main test9.in
	$(CC)  9.c -lm; 
	a.out > 9;


10: test10.in
	../taylor -o 10.c -main test10.in
	$(CC)  10.c -lm; 
	a.out > 10;


11: test11.in
	../taylor -o 11.c -main test11.in
	$(CC)  11.c -lm; 
	a.out > 11;

12: test12.in
	../taylor -o 12.c -main test12.in
	$(CC)  12.c -lm; 
	a.out > 12;


z: z.in
	../taylor -o z.c  -step 0 -main -jet -header z.in
	$(CC)  z.c -lm; 
	a.out > z;

a: a.in
	../taylor -o a.c  -step -main -jet -header a.in
	$(CC)  a.c -lm; 
	a.out > a;



clean:
	/bin/rm -rf *.c  1 2 3 4 5 6 7 8 9 10 11 12 a.out z a


