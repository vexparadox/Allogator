#include "main.hpp"


int main(int argc, char const *argv[])
{
	Memory::Allocator alloc(20);
	
	Test* test = alloc.request<Test>();
	alloc.print_page();
	alloc.del<Test>(test);
	alloc.print_page();
}