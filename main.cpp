#include "main.hpp"

std::unique_ptr<Net::NetworkManager> manager;

int main(int argc, char const *argv[])
{
	manager = std::make_unique<Net::NetworkManager>();
	return 0;
}