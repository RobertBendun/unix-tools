#include <algorithm>
#include <iostream>

#include <Line.hh>

int main()
{
	std::copy_if(
		std::istream_iterator<Line>(std::cin),
		std::istream_iterator<Line>{},
		std::ostream_iterator<Line>(std::cout),
		[i = 0u](auto const&) mutable { return i++ < 15; }
	);
}