
main: main.cpp math.cpp
	g++ main.cpp math.cpp -std=c++14 -o main

run:
	./main "/Users/Konstantin/CLionProjects/calculator/input.txt"

clean:
	rm -f main