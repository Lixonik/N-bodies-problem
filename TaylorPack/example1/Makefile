#######################################################################

all: example1


example1:  main.c 
	gcc -O  -o example1 main.c e.c -lm

e.c:
	../taylor  -o e.c input

clean:
	/bin/rm e.c example1 *.o

#######################################################################
