#include <iostream>
#include <filesystem>
#include <sstream>
#include <array>
#include <string_view>
#include <ranges>
#include <span>

using namespace std::string_view_literals;

char const* Compiler;

constexpr auto Standalone = std::array {
	"ls"sv,
	"uniq"sv,
	"head"sv,
	"pwd"sv,
	"shuf"sv
};

constexpr auto With_For_Each_File = std::array {
	"cat"sv
};


namespace fs = std::filesystem;

auto cmd(auto const& ...printable)
{
	std::ostringstream os;
	os << Compiler << " -std=c++20 -O3 -Wall -Wextra ";
	(os << ... << printable);
	std::cout << "[CMD] " << os.str() << std::endl;
	std::system(os.str().c_str());
}

bool is_rebuild_needed(fs::path const& src, fs::path const& exe)
{
	return !fs::exists(exe) || fs::last_write_time(exe) < fs::last_write_time(src);
}

void maybe_rebuild_itself()
{
	auto const exe = fs::canonical(fs::path("/proc/self/exe"));
	auto const src = exe.parent_path() / __FILE__;

	// TODO use std::error_code
	if (is_rebuild_needed(src, exe)) {
		std::cout << "[INFO] Changes to building script has been made, rebuilding self...\n";
		cmd(src, " -o ", exe);
	}
}

char const* getenv_or_default(char const* name, char const* default_value)
{
	if (auto p = getenv(name); p)
		return p;
	return default_value;
}

int main(int argc, char **argv)
{
	Compiler = getenv_or_default("CXX", "g++");

	maybe_rebuild_itself();

	if (++argv; *argv && *argv == "clean"sv) {
		auto clean = [](auto collection) {
			for (auto exe : collection)
				if (fs::remove(exe))
					std::cout << "[REMOVED] " << exe << '\n';
		};

		clean(Standalone);
		clean(With_For_Each_File);
		return 0;
	}

	for (auto exe : Standalone) {
		auto src = fs::path(exe); src += ".cc";
		if (is_rebuild_needed(src, exe)) {
			cmd("-Ishared -o ", exe, ' ', src);
		}
	}

		for (auto exe : With_For_Each_File) {
		auto src = fs::path(exe); src += ".cc";
		if (is_rebuild_needed(src, exe)) {
			cmd("-Ishared shared/for_file.cc -o ", exe, ' ', src);
		}
	}
}
