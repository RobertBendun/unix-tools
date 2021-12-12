#include <filesystem>
#include <iostream>

int main()
{
	std::cout << std::filesystem::current_path().c_str() << std::endl;
}