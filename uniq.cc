#include <algorithm>
#include <iostream>

#include <Line.hh>

int main()
{
	std::unique_copy(
		std::istream_iterator<Line>(std::cin), {},
		std::ostream_iterator<Line>(std::cout)
	);
}
