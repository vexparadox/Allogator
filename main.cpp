#include "main.hpp"


int main(int argc, char const *argv[])
{
	Memory::Allocator alloc(2);
	
	Test* test = new(alloc.request<Test>())Test;
}