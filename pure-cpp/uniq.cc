#include <algorithm>
#include <iostream>

#include <Line.hh>

int main()
{
	std::ranges::unique_copy(to_range(std::cin), std::ostream_iterator<Line>(std::cout));
}
