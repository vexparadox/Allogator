#include "main.hpp"


int main(int argc, char const *argv[])
{
	Memory::Allocator alloc(50);
	
	Test* test = alloc.request<Test>();
	alloc.del<Test>(test);
	Test* test2 = alloc.request<Test>();	
}