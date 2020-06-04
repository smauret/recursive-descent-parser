
main: main.cpp math.cpp
	g++ main.cpp math.cpp -std=c++14 -o main

run:
	./main

clean:
	rm -f main