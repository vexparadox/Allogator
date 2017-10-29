#pragma once
#include <cstring>
#include <stdint.h>
#include <iostream>
namespace Memory{
	struct Blank{
		uint64_t address = 0;;
		uint64_t size = 0;
	};
	class Allocator{
		uint64_t* page = nullptr; // page of memory

		uint64_t* curr_pos = nullptr; // current position at the end
		Blank* blanks = nullptr; // an array of blanks

		int curr_size;
		int header_size = 64;
	public:
		//construct the allocator
		Allocator(uint64_t initial_size = 2048);

		//delete a block of memory at ptr
		void del(void* ptr);

		//request a block of memory sizeof T
		template<typename T>
		void* request()
		{
			size_t size = sizeof(T); 
			if(uint64_t(curr_pos-curr_size) >= uint64_t(size+header_size))
			{
				*curr_pos = size;
				void* address = ++curr_pos;
				curr_pos += size;
				return address;
			}
			else
			{
				//allocation failed
				std::cout << "Not enough space for this object" << std::endl;
				std::cout << "Remaining: " << uint64_t(curr_pos-curr_size) << std::endl;
				std::cout << "Requested: " << size << std::endl;
				return nullptr;
			}
		}
	};
}