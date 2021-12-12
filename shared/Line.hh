#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <iterator>

struct Line : std::string {};

inline std::istream& operator>>(std::istream& is, Line &line)
{
	return std::getline(is, static_cast<std::string&>(line));
}

inline std::ostream& operator<<(std::ostream& os, Line const& line)
{
	return os << static_cast<std::string const&>(line) << '\n';
}
