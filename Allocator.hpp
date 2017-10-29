#pragma once
#include <cstring>
#include <stdint.h>
#include <iostream>
namespace Memory{
	struct Blank{
		void* address = nullptr;
		uint64_t size = 0;
	};
	class Allocator{
		uint64_t* page = nullptr; // page of memory

		uint64_t* curr_pos = nullptr; // current position at the end
		Blank* blanks = nullptr; // an array of blanks

		int curr_size;
		int header_size = 64; // basically 64 bit to hold the size of the header data
	public:
		//construct the allocator
		Allocator(uint64_t initial_size = 2048);

		//delete a block of memory at ptr
		void del(void* ptr);

		//request a block of memory sizeof T
		template<typename T>
		T* request()
		{
			size_t size = sizeof(T); 
			// do we have a enough space?
			// the page start+current page size - current_position gives us the remaining
			int64_t remaining_space = int64_t((page+curr_size)-curr_pos);
			if(remaining_space >= int64_t(size+header_size))
			{
				*curr_pos = size;
				void* address = ++curr_pos;
				curr_pos += size;
				return new(address)T;
			}
			else
			{
				#if DEBUG
				//allocation failed
				std::cout << "Not enough space for this object" << std::endl;
				std::cout << "Remaining: " << remaining_space << std::endl;
				std::cout << "Requested: " << size << std::endl;
				#endif
				return nullptr;
			}
		}
	};
}