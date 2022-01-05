#include <iostream>
#include <filesystem>
#include <algorithm>
#include <span>
#include <ranges>
#include <tuple>
#include <array>
#include <bit>
#include <iomanip>

namespace fs = std::filesystem;

// Reference: https://pubs.opengroup.org/onlinepubs/9699919799/ 
//            look for section STDOUT
void ls(fs::directory_entry file)
{
	static constexpr auto RWX = []{
		std::array<std::array<char[3], 0b1000>, 2> all_combinations;
		for (auto &comb : all_combinations)
			for (auto &rwx : comb)
				std::fill_n(rwx, sizeof(rwx), '.');

		for (unsigned j : { 0, 1 }) {
			for (unsigned i = 0b000; i <= 0b111; ++i) {
				if (0b100 & i) all_combinations[j][i][0] = 'r';
				if (0b010 & i) all_combinations[j][i][1] = 'w';
				if (0b001 & i) all_combinations[j][i][2] = "xs"[j];
			}
		}
		return all_combinations;
	}();

	// FILE MODE
	auto p = file.status().permissions();
	std::cout.write(RWX[int(p & fs::perms::set_uid) ? 1 : 0][(size_t(p) / 64) & 0b111], 3); // user
	std::cout.write(RWX[int(p & fs::perms::set_gid) ? 1 : 0][(size_t(p) / 8) & 0b111], 3); // group
	std::cout.write(RWX[0][(size_t(p) / 1) & 0b111], 3); // others
	
	// NUMBER OF LINKS
	std::cout << ' ' << file.hard_link_count();

	// TODO date

	// Filename
	std::cout << ' ' << file.path().filename().c_str() << '\n';
}

void ls(fs::path file)
{
	if (fs::is_directory(file)) {
		for (auto entry : fs::directory_iterator(file)) {
			ls(std::move(entry));
		}
	} else {
		ls(fs::directory_entry{ file });
	}
}

int main(int argc, char **argv)
{
	if (auto args = std::span(argv+1, argv+argc); args.empty()) {
		ls(".");
	} else {
		std::ranges::for_each(args, (void(*)(fs::path))ls);
	}
}
