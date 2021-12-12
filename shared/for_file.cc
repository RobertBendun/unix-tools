#include <iostream>
#include <fstream>
#include <span>

#include "for_file.hh"

namespace fs = std::filesystem;
using namespace std::string_view_literals;

namespace unix_tools
{
	std::string_view Program_Name;
	std::filesystem::path Current_File;
}

int main(int argc, char **argv)
try {
	auto program_path = fs::path(argv[0]).filename();
	unix_tools::Program_Name = program_path.c_str();

	for (auto arg : std::span(argv+1, argv+argc)) {
		unix_tools::Current_File = arg;
		if (arg == "-"sv) {
			unix_tools::Current_File = "<stdin>";
			unix_tools::for_each_file(std::cin);
		} else if (std::ifstream file(unix_tools::Current_File); file) {
			unix_tools::for_each_file(file);
		} else {
			std::cerr << unix_tools::Program_Name << ": couldn't open file: " << arg << std::endl;
			return 1;
		}
	}
} catch (std::exception const& exception) {
	std::cerr << unix_tools::Program_Name << ": " << exception.what() << std::endl;
	return 1;
}
