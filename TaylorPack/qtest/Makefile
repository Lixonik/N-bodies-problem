#######################################################################
#
#   Makefile for the taylor translator
#		
CC=g++ -I../qd/include -O -Dx86

all:     1 2 3 4 5 6 7 8 9 10 11 12

1: test1.in
	../taylor -qd -o 1.c -main test1.in
	$(CC)  1.c -lqd
	a.out > 1;

2: test2.in
	../taylor -qd -o 2.c -main test2.in
	$(CC)  2.c -lqd
	a.out > 2;

3: test3.in
	../taylor -qd -o 3.c -main test3.in
	$(CC)  3.c -lqd
	a.out > 3;

4: test4.in
	../taylor -qd -o 4.c -main test4.in
	$(CC)  4.c -lqd
	a.out > 4;

5: test5.in
	../taylor -qd -o 5.c -main test5.in
	$(CC)  5.c -lqd
	a.out > 5;

6: test6.in
	../taylor -qd -o 6.c -main test6.in
	$(CC)  6.c -lqd
	a.out > 6;

7: test7.in
	../taylor -qd -o 7.c -main test7.in
	$(CC)  7.c -lqd
	a.out > 7;

8: test8.in
	../taylor -qd -o 8.c -main test8.in
	$(CC)  8.c -lqd
	a.out > 8;

9: test9.in
	../taylor -qd -o 9.c -main test9.in
	$(CC)  9.c -lqd
	a.out > 9;


10: test10.in
	../taylor -qd -o 10.c -main test10.in
	$(CC)  10.c -lqd
	a.out > 10;


11: test11.in
	../taylor -qd -o 11.c -main test11.in
	$(CC)  11.c -lqd
	a.out > 11;

12: test12.in
	../taylor -qd -o 12.c -main test12.in
	$(CC)  12.c -lqd
	a.out > 12;



z: z.in
	../taylor -qd -o z.c -main -step 0 -header -jet z.in
	g++ -I../qd/include -Dx86 -g  z.c -lqd
	a.out> z;


a: a.in
	../taylor -qd -o a.c -step -main -header -jet a.in
	g++ -I../qd/include -Dx86 -g  a.c -lqd
	a.out> a;




clean:
	/bin/rm -rf *.c  1 2 3 4 5 6 7 8 9 10 11 12 a.out z a


