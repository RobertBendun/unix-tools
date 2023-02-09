#include <filesystem>
#include <iostream>
#include <span>

int main(int argc, char **argv)
{
	std::span<char*> args(argv+1, argv+argc);

	unsigned const pos_base_index = args.size() && args.front() == std::string_view("--");

	if (args.size() < 1+pos_base_index || args.size() > 2+pos_base_index) {
		std::cerr << "basename: wrong number of arguments" << std::endl;
		return 1;
	}

	std::string_view const path_str = args[pos_base_index];
	std::string_view const suffix_str = args.size() == 2+pos_base_index ? args[pos_base_index+1] : "";

	auto const filename = std::filesystem::path(path_str).filename().string();

	std::cout << (filename.ends_with(suffix_str)
			? std::string_view(filename).substr(0, filename.size()-suffix_str.size())
			: std::string_view(filename)) << std::endl;
}
