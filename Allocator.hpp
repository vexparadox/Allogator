#pragma once
#include <cstring>
#include <vector>
#include <stdint.h>
#include <iostream>
namespace Memory{
	struct Blank{
		Blank(void* address, uint64_t size) : address(address), size(size) {}
		void* address = nullptr;
		uint64_t size = 0;
	};

	class Allocator{
		uint64_t* page = nullptr; // page of memory

		uint64_t* curr_pos = nullptr; // current position at the end
		std::vector<Blank> blanks; // an array of blanks

		int curr_size = 0;
		int header_size = 8; // how many bytes to hold the size of the header data
	public:
		//construct the allocator
		Allocator(uint64_t initial_size = 2048)
		{
			page = new uint64_t[initial_size];
			if(page)
			{
				std::memset(page, 0, initial_size);
				curr_size = initial_size;
				curr_pos = page;
			}
			#if ALLOC_DEBUG
			else
			{
				std::cout << "Allocator's request for memory failed." << std::endl;
			}
			#endif
		}

		~Allocator()
		{
			delete[] page;
		}

		//delete a block of memory at ptr
		template<typename T>
		void del(void* ptr)
		{
			//we need to cast so we can check if we're in the page size and so we can do arithmatic
			uint64_t* casted = (uint64_t*)ptr;

			if(casted < page || casted > page+curr_size)
			{
				#if ALLOC_DEBUG
				std::cout << "Trying to delete non-allocated memory." << std::endl;
				#endif
				return;
			}

			T* typed_ptr = (T*)ptr;
			typed_ptr->~T();
			//get the size and ptr of where we're deleting
			uint64_t* deleted_ptr = (uint64_t*)(casted-header_size);
			uint64_t deleted_size = *deleted_ptr+header_size;
			#if ALLOC_DEBUG
			std::cout << "Deleting " << deleted_size << " at : " << deleted_ptr << std::endl;
			#endif
			std::memset(deleted_ptr, 0, deleted_size); // write over memory with 0s
			//put into the blanks
			blanks.push_back(Blank(deleted_ptr, deleted_size));
		}

		//request a block of memory sizeof T
		template<typename T>
		T* request()
		{
			size_t size = sizeof(T); 
			// do we have a enough space?
			// the page start+current page size - current_position gives us the remaining space on the end
			int64_t end_remaining_space = int64_t((page+curr_size)-curr_pos);
			int64_t requested = int64_t(size+header_size);
			auto found_blank = blanks.empty() ? blanks.end() : std::find_if(blanks.begin(), blanks.end(), [requested](const Blank& blank){ return blank.size == requested; });
			if(found_blank != blanks.end())
			{
				// we found a blank that'll fit, so use that instead
				uint64_t* address = (uint64_t*)(*found_blank).address; // get the address
				// remove the blank
				blanks.erase(found_blank);
				
				*address = (*found_blank).size; // write the size
				address += header_size; //move past the header size
				
				#if ALLOC_DEBUG
				std::cout << "Requested: " << requested << std::endl;
				std::cout << "Given Blank at: " << address << std::endl;
				#endif
				return new(address)T;
			}
			else if(end_remaining_space >= requested)
			{
				//we do a new allocation at the end
				*curr_pos = size;
				void* address = (uint64_t*)(curr_pos+header_size); //return after the header
				curr_pos += size; // place the curr_pos at the end of this allocated block
				#if ALLOC_DEBUG
				std::cout << "Requested: " << requested << std::endl;
				std::cout << "Given: " << address << std::endl;
				#endif
				return new(address)T;
			}
			else
			{
				#if ALLOC_DEBUG
				//allocation failed
				std::cout << "Not enough space for this object" << std::endl;
				std::cout << "Remaining End: " << end_remaining_space << std::endl;
				std::cout << "Blanks: " << blanks.size() << std::endl;
				std::cout << "Requested: " << requested << std::endl;
				#endif
				return nullptr;
			}
		}

		void print_page()
		{
			#if ALLOC_DEBUG
			for(int i = 0; i < curr_size; i++)
			{
				std::cout << std::hex << page[i] << std::endl;
				if(i%20 == 0 && i!=0)
				{
					std::cout << std::endl;
				}
			}
			#endif
		}
		
	};
}