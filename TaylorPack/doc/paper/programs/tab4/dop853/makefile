F77=g77
FFLAGS=-O3
LFLAGS=-s

all: rtbp lorenz pepe

RTBP=main-rtbp.o dop853.o rtbp.o

rtbp: $(RTBP)
	$(F77) $(FFLAGS) $(RTBP) -o rtbp $(LFLAGS)

main-rtbp.o: main-rtbp.f
	$(F77) $(FFLAGS) -c main-rtbp.f

rtbp.o: rtbp.f
	$(F77) $(FFLAGS) -c rtbp.f

LRNZ=main-lorenz.o dop853.o lorenz.o

lorenz: $(LRNZ)
	$(F77) $(FFLAGS) $(LRNZ) -o lorenz $(LFLAGS)

main-lorenz.o: main-lorenz.f
	$(F77) $(FFLAGS) -c main-lorenz.f

lorenz.o: lorenz.f
	$(F77) $(FFLAGS) -c lorenz.f

PEPE=main-pepe.o dop853.o pepe.o

pepe: $(PEPE)
	$(F77) $(FFLAGS) $(PEPE) -o pepe $(LFLAGS)

main-pepe.o: main-pepe.f
	$(F77) $(FFLAGS) -c main-pepe.f

pepe.o: pepe.f
	$(F77) $(FFLAGS) -c pepe.f

dop853.o: dop853.f
	$(F77) $(FFLAGS) -c dop853.f

clean:
	rm -f *.o
	rm -f lorenz pepe rtbp
