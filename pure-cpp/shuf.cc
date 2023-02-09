#include <algorithm>
#include <iostream>
#include <random>

#include <Line.hh>

int main()
{
	std::vector<std::string> lines;
	std::ranges::copy(cin_range, std::back_inserter(lines));

	std::mt19937 rnd{std::random_device{}()};
	std::ranges::shuffle(lines, rnd);
	std::ranges::copy(lines, std::ostream_iterator<Line>(std::cout));
}
