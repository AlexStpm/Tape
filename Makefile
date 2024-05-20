all: build test clean
.PHONY: all build run test clean

build:
	g++ main.cpp Tape.cpp NaturalMergeTapeSort.cpp -o main
	g++ Generator.cpp -o generate
	mkdir tmp

run:
	./main $(fileName)

test:
	./generate 0
	./generate 1
	./generate 5
	./generate 1000
	./generate 1000000
	echo "15          ab           32           18          " > tapeInvalid.txt
	g++ UnitTests.cpp NaturalMergeTapeSort.cpp Tape.cpp -o test -lgtest
	./test

clean:
	rm tape*.txt
	rm output.txt
