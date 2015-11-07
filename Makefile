CC=g++
CFLAGS=--std=c++14 -Wall -pedantic -O2
LIBS=-lm
BIN=RayTracer
SRC=./src
ZIP=xmarta00.zip

all:	color.o light.o material.o matrix.o object.o plane.o ray.o scene.o sphere.o texture.o vector.o
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)/main.cpp color.o light.o material.o matrix.o object.o plane.o ray.o scene.o sphere.o texture.o vector.o $(LIBS)

color.o:
	$(CC) $(CFLAGS) -o color.o -c $(SRC)/Color.cpp

light.o:	color.o vector.o
	$(CC) $(CFLAGS) -o light.o -c $(SRC)/Light.cpp

material.o:	color.o texture.o
	$(CC) $(CFLAGS) -o material.o -c $(SRC)/Material.cpp

matrix.o:	vector.o
	$(CC) $(CFLAGS) -o matrix.o -c $(SRC)/Matrix.cpp

object.o:	material.o
	$(CC) $(CFLAGS) -o object.o -c $(SRC)/Object.cpp

plane.o:
	$(CC) $(CFLAGS) -o plane.o -c $(SRC)/Plane.cpp

ray.o:	vector.o
	$(CC) $(CFLAGS) -o ray.o -c $(SRC)/Ray.cpp

scene.o:	color.o light.o object.o
	$(CC) $(CFLAGS) -o scene.o -c $(SRC)/Scene.cpp

sphere.o:	ray.o
	$(CC) $(CFLAGS) -o sphere.o -c $(SRC)/Sphere.cpp

texture.o:	color.o vector.o
	$(CC) $(CFLAGS) -o texture.o -c $(SRC)/Texture.cpp

vector.o:
	$(CC) $(CFLAGS) -o vector.o -c $(SRC)/Vector.cpp

doc:
	doxygen doxyfile

clean:
	rm -rf *.o *~ $(BIN) $(ZIP) $(DOC) result.bmp

clear: clean

push:
	git push -u origin master

run:
	./$(BIN)

pack: clean
	zip -r $(ZIP) ./src/ Makefile doxyfile TODO README.txt
