run: compile
	./Matrix

compile: main.cpp
	g++ -std=c++17 main.cpp -o Matrix