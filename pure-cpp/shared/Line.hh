#pragma once

#include <istream>
#include <iterator>
#include <ostream>
#include <ranges>
#include <string>

struct Line : std::string
{
	Line() = default;
	Line(Line const&) = default;
	Line(Line &&) = default;
	~Line() = default;
	Line& operator=(Line const&) = default;
	Line& operator=(Line &&) = default;

	Line(std::string &&s) : std::string(std::move(s)) {}
	Line(std::string const& s) : std::string(s) {}

	Line& operator=(std::string &s) { static_cast<std::string&>(*this) = s; return *this; }
	Line& operator=(std::string &&s) { static_cast<std::string&>(*this) = std::move(s); return *this; }
};

inline std::istream& operator>>(std::istream& is, Line &line)
{
	return std::getline(is, static_cast<std::string&>(line));
}

inline std::ostream& operator<<(std::ostream& os, Line const& line)
{
	return os << static_cast<std::string const&>(line) << '\n';
}

template<typename T=Line>
auto to_range(std::istream &in)
{
	return std::ranges::subrange(std::istream_iterator<T>(in), std::istream_iterator<T>());
}
