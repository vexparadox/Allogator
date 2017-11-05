#include "main.hpp"


int main(int argc, char const *argv[])
{
	Memory::Allocator alloc(50);
	
	Test* test = alloc.request<Test>();
	alloc.del<Test>(test);
	Test* test2 = alloc.request<Test>();	
	Test* test3 = alloc.request<Test>();
	alloc.del<Test>(test2);
	Test* test4 = alloc.request<Test>();
}