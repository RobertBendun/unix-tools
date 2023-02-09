#include <algorithm>
#include <iostream>

#include <Line.hh>

int main()
{
	std::ranges::unique_copy(cin_range, std::ostream_iterator<Line>(std::cout));
}
