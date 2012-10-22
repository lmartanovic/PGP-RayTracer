CC=g++
CFLAGS=-Wall -Wextra -Weffc++ -pedantic -O
DFLAGS=-DDEBUG -g -pg
LIBS=
BIN=rt
DOC=./doc
SRC=./src
ZIP=xmarta00.zip

all:	vector.o
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)/main.cpp vector.o $(LIBS)

vector.o:
	$(CC) $(CFLAGS) -o vector.o -c $(SRC)/Vector.cpp $(LIBS)

debug:
	$(CC) $(CFLAGS) $(DFLAGS) -o $(BIN) $(SRC) $(LiBS)

doc:
	doxygen doxyfile

clean:
	rm -rf *.o *~ $(BIN) $(ZIP) $(DOC)

clear: clean

run:
	./$(BIN)

pack: clean
	zip -r $(ZIP) ./src/ Makefile doxyfile TODO README.txt
