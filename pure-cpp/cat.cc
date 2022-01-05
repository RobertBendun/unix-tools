#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <span>

#include "for_file.hh"

using namespace std::string_view_literals;

void unix_tools::for_each_file(std::istream &s)
{
	std::copy(std::istreambuf_iterator<char>(s), {}, std::ostreambuf_iterator<char>{std::cout});
}
