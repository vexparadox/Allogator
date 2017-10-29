#include "main.hpp"


int main(int argc, char const *argv[])
{
	Memory::Allocator alloc;
	
	Test* test = new(alloc.request<Test>())Test;
}