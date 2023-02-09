#include <iostream>
#include <ranges>
#include <algorithm>

#include <Line.hh>

int main()
{
	std::ranges::copy(
		to_range(std::cin) | std::views::transform([](std::string s) { std::ranges::reverse(s); return s; })
		, std::ostream_iterator<Line>(std::cout));
}
