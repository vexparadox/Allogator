#include "main.hpp"


int main(int argc, char const *argv[])
{
	Memory::Allocator alloc;
	
	Test* test = alloc.request<Test>();
	alloc.del<Test>(test);
}