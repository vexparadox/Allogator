#pragma once
#include "Allocator.hpp"

class Test{
public:
	Test(){ std::cout << "Created Test" << std::endl; }
	~Test(){ std::cout << "Destroyed Test" << std::endl;}
	int x;
	int y;
	int z;
};