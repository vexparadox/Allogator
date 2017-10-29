#include "main.hpp"

std::unique_ptr<Net::NetworkManager> manager;

int main(int argc, char const *argv[])
{
	Memory::Allocator alloc;
	void* ptr = nullptr;
	Net::NetworkManager* nm = new(alloc.request<Net::NetworkManager>())Net::NetworkManager; 
}