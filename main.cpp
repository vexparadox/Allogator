#include "main.hpp"


int main(int argc, char const *argv[])
{
	Memory::Allocator alloc(20);
	
	Test* test = alloc.request<Test>();
	alloc.del<Test>(test);
	
}