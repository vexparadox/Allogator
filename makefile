all:
	g++ *.cpp -std=c++14 -o out -g -DDEBUG
release:
	g++ *.cpp -std=c++14 -o out_release -O3
run: all
	./out