all: app.exe

app.exe: n-bodies.o Vec3D.o 
	g++ n-bodies.o Vec3D.o -o app && make -f Makefile clean

n-bodies.o: n-bodies.cpp KeplerDataBox.h
	g++ -c n-bodies.cpp

Vec3D.o: Vec3D.cpp Vec3D.h
	g++ -c Vec3D.cpp

clean:
	rm *.o
