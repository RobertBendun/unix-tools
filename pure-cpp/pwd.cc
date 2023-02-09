#include <filesystem>
#include <iostream>
#include <span>
#include <algorithm>


int main(int argc, char **argv)
{
	std::span<char*> args(argv+1, argv+argc);

	bool l_spotted = false;
	bool p_spotted = false;

	for (std::string_view arg : args) {
		if (arg == "-P") { l_spotted = false; p_spotted = true; continue; }
		if (arg == "-L") { p_spotted = false; l_spotted = true; continue; }

		std::cerr << "pwd: unrecognized option: " << arg << std::endl;
		return 1;
	}

	if (!l_spotted and !p_spotted) {
		p_spotted = true;
	}

	auto const current_path = std::filesystem::current_path();

	if (l_spotted) {
		throw std::runtime_error("unimplemented");
	}

	// It seems that C++ handles -P option by default?
	std::cout << current_path.string() << std::endl;
}
