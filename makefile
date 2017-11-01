all:
	g++ *.cpp -std=c++14 -o out -g -DALLOC_DEBUG
release:
	g++ *.cpp -std=c++14 -o out_release -O3
run: all
	./out