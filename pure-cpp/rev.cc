#include <iostream>
#include <ranges>
#include <algorithm>

#include <Line.hh>

int main()
{
	std::ranges::copy(
		std::ranges::subrange(std::istream_iterator<Line>(std::cin), std::istream_iterator<Line>{})
		| std::views::transform([](std::string s) { std::ranges::reverse(s); return s; })
		, std::ostream_iterator<Line>(std::cout));

}
