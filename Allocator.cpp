#include "Allocator.hpp"

Memory::Allocator::Allocator()
{
	page = new uint64_t[2048];
	blanks = new Blank[64];
	std::memset(page, 0, 2048);
	std::memset(blanks, 0, 64);
	curr_size = 2048;
	curr_pos = page;
}

template<typename T>
void* Memory::Allocator::request()
{
	size_t size = sizeof(T); 
	if(uint64_t(curr_pos-curr_size) >= uint64_t(size+header_size))
	{
		*curr_pos = size;
		return ++curr_pos;
	}
	else
	{
		//allocation failed
		return nullptr;
	}
}

void Memory::Allocator::del(void* ptr)
{
	if(ptr < page || ptr > page+curr_size)
	{
		std::cout << "Trying to delete non-allocated memory." << std::endl;
		return;
	}

}