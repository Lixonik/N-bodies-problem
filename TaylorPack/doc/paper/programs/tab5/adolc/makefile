CPP=g++
CPPFLAGS=-O3
ADOL_H=-I/usr/include/adolc
ADOL_LIB=-ladolc

all: lorenz pepe rtbp

RTBP=main-rtbp.o rtbp.o

rtbp: $(RTBP)
	$(CPP) $(CPPFLAGS) $(RTBP) -o rtbp $(ADOL_LIB)

main-rtbp.o: main-rtbp.cc params.h
	$(CPP) -c $(CPPFLAGS) $(ADOL_H) main-rtbp.cc

rtbp.o: rtbp.cc
	$(CPP) -c $(CPPFLAGS) $(ADOL_H) rtbp.cc

LRNZ=main-lorenz.o lorenz.o

lorenz: $(LRNZ)
	$(CPP) $(CPPFLAGS) $(LRNZ) -o lorenz $(ADOL_LIB)

main-lorenz.o: main-lorenz.cc params.h
	$(CPP) -c $(CPPFLAGS) $(ADOL_H) main-lorenz.cc

lorenz.o: lorenz.cc
	$(CPP) -c $(CPPFLAGS) $(ADOL_H) lorenz.cc

PEPE=main-pepe.o pepe.o

pepe: $(PEPE)
	$(CPP) $(CPPFLAGS) $(PEPE) -o pepe $(ADOL_LIB)

main-pepe.o: main-pepe.cc params.h
	$(CPP) -c $(CPPFLAGS) $(ADOL_H) main-pepe.cc

pepe.o: pepe.cc
	$(CPP) -c $(CPPFLAGS) $(ADOL_H) pepe.cc

clean:
	rm -f *.o
	rm lorenz pepe rtbp
