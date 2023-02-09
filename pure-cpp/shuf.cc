#include <algorithm>
#include <iostream>
#include <random>

#include <Line.hh>

int main()
{
	std::vector<std::string> lines;
	std::copy(std::istream_iterator<Line>(std::cin), {}, std::back_inserter(lines));

	std::mt19937 rnd{std::random_device{}()};
	std::shuffle(std::begin(lines), std::end(lines), rnd);
	std::copy(std::begin(lines), std::end(lines), std::ostream_iterator<Line>(std::cout));
}
