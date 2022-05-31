#######################################################################
#
#   Makefile for the taylor translator
#		

all:     taylor

HEADER1= y.tab.h
HEADER2= Node.h NodeCode.h
LEXSRC = Lex.l
YACCSRC= parse.y
SRC    = lex.yy.c y.tab.c Node.c  Parse.c  Code.c Code1.c Sum.c Main.c CodeMain.c
OBJ    = $(SRC:.c=.o)

CC=gcc
LEXLIB = -lfl
OPFLAG = -O3 -Wall

Node.h: NodeCode.h
	@/usr/bin/touch Node.h

lex.yy.c: Lex.l $(HEADER1)
	flex -l Lex.l

y.tab.h: parse.y
	bison -y -d parse.y 

y.tab.c: y.tab.h
	bison -y -v parse.y 

taylor: $(OBJ) 
	gcc -s -o taylor $(OPFLAG) $(OBJ) $(LEXLIB) -lm

clean:
	/bin/rm -rf *.o lex.yy.c y.tab.c y.tab.h y.output  *~ parse

.c.o: 
	$(CC) $(OPFLAG)   -c $<

#######################################################################
