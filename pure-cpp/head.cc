#include <algorithm>
#include <iostream>

#include <Line.hh>

int main()
{
	std::ranges::copy(cin_range | std::views::take(15), std::ostream_iterator<Line>(std::cout));
}
