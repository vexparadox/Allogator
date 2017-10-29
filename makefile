all:
	g++ *.cpp -std=c++14 -o out -g
run: all
	./out