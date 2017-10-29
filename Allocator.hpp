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
		template<typename T>
		void del(void* ptr)
		{
			//we need to cast so we can check if we're in the page size and so we can do arithmatic
			uint64_t* casted = (uint64_t*)ptr;

			if(casted < page || casted > page+curr_size)
			{
				#if DEBUG
				std::cout << "Trying to delete non-allocated memory." << std::endl;
				#endif
				return;
			}

			T* typed_ptr = (T*)ptr;
			typed_ptr->~T();
			//get the size and ptr of where we're deleting
			uint64_t* deleted_ptr = --casted;
			uint64_t deleted_size = *deleted_ptr;

			std::memset(deleted_ptr, 0, deleted_size); // write over memory with 0s
			//put into the blanks
			for(int i = 0; i < 64; i++){
				if(blanks[i].address == nullptr)
				{
					blanks[i].address = deleted_ptr;
					blanks[i].size = deleted_size;
				}
			}
		}

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