#pragma once

#include <istream>
#include <filesystem>
#include <string_view>

namespace unix_tools
{
	extern void for_each_file(std::istream &s);

	extern std::string_view Program_Name;
	extern std::filesystem::path Current_File;
}