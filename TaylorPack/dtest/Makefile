#######################################################################
#
#   Makefile for the taylor translator
#		

all:     1 2 3 4 5 6 7 8 9 10 11 12

1: test1.in
	../taylor -o 1.c -main -ddouble test1.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 1.c ../dd/libdoubledouble.a -lm; 
	a.out > 1;

2: test2.in
	../taylor -o 2.c -main -ddouble test2.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 2.c ../dd/libdoubledouble.a -lm; 
	a.out > 2;

3: test3.in
	../taylor -o 3.c -main -ddouble test3.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 3.c ../dd/libdoubledouble.a -lm; 
	a.out > 3;

4: test4.in
	../taylor -o 4.c -main -ddouble test4.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 4.c ../dd/libdoubledouble.a -lm; 
	a.out > 4;

5: test5.in
	../taylor -o 5.c -main -ddouble test5.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 5.c ../dd/libdoubledouble.a -lm; 
	a.out > 5;

6: test6.in
	../taylor -o 6.c -main -ddouble test6.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 6.c ../dd/libdoubledouble.a -lm; 
	a.out > 6;

7: test7.in
	../taylor -o 7.c -main -ddouble test7.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 7.c ../dd/libdoubledouble.a -lm; 
	a.out > 7;

8: test8.in
	../taylor -o 8.c -main -ddouble test8.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 8.c ../dd/libdoubledouble.a -lm; 
	a.out > 8;

9: test9.in
	../taylor -o 9.c -main -ddouble test9.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 9.c ../dd/libdoubledouble.a -lm; 
	a.out > 9;


10: test10.in
	../taylor -o 10.c -main -ddouble test10.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 10.c ../dd/libdoubledouble.a -lm; 
	a.out > 10;

11: test11.in
	../taylor -o 11.c -main -ddouble test11.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 11.c ../dd/libdoubledouble.a -lm; 
	a.out > 11;

12: test11.in
	../taylor -o 12.c -main -ddouble test12.in
	g++ -I../dd  -m486 -O3 -DDD_INLINE -Dx86 12.c ../dd/libdoubledouble.a -lm; 
	a.out > 12;



z: z.in
	../taylor -ddouble -o z.c -main -step 0 -header -jet z.in
	g++ -I../dd  -m486 -g -DDD_INLINE -Dx86 z.c ../dd/libdoubledouble.a -lm; 
	a.out> z;


a: a.in
	../taylor -ddouble -o a.c -main -header -jet a.in
	g++ -I../dd  -m486 -g -DDD_INLINE -Dx86 a.c ../dd/libdoubledouble.a -lm; 
	a.out> a;



clean:
	/bin/rm -rf *.c  1 2 3 4 5 6 7 8 9 10 11 12 a.out z a


