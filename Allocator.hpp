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
		Allocator();
		template<typename T>
		void* request();
		void del(void*);
	};
}