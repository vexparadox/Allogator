#include "Allocator.hpp"

Memory::Allocator::Allocator(uint64_t initial_size)
{
	page = new uint64_t[initial_size];
	blanks = new Blank[64];
	if(page && blanks)
	{
		std::memset(page, 0, initial_size);
		std::memset(blanks, 0, 64);
		curr_size = initial_size;
		curr_pos = page;
	}
	#if DEBUG
	else
	{
		std::cout << "Allocator's request for memory failed." << std::endl;
	}
	#endif
}