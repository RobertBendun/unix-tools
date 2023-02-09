#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>

#include <Line.hh>

auto head(std::output_iterator<Line> auto &out, std::ranges::range auto &&range, unsigned n)
{
	out = std::ranges::copy(std::forward<decltype(range)>(range) | std::views::take(n), out).out;
}

int main(int argc, char **argv)
{
	std::span args(argv+1, argv+argc);

	unsigned files_count = 0;
	unsigned length = 10;

	{
		bool accept_any = false;
		for (auto it = args.begin(); it != args.end(); ++it) {
			if (!accept_any) {
				if (*it == std::string_view("-n")) {
					if (++it == args.end()) {
						std::cerr << "head: parameter -n expects number of lines to be provided\n";
						std::exit(1);
					}
					unsigned result = 0;
					std::string_view n(*it);
					std::from_chars(n.data(), n.data()+n.size(), result); // TODO Check error
					continue;
				}

				if (*it == std::string_view("--")) {
					accept_any = true;
					continue;
				}
			}

			files_count++;
		}
	}

	auto out = std::ostream_iterator<Line>(std::cout);
	if (args.empty()) {
		head(out, to_range(std::cin), length);
		return 0;
	}


	{
		bool first = true;
		bool accept_any = false;
		for (auto it = args.begin(); it != args.end(); ++it) {
			if (!accept_any) {
				if (*it == std::string_view("-n")) {
					++it; // We know that there is next since we check above in -n handler
					continue;
				}
				if (*it == std::string_view("--")) {
					accept_any = true;
					continue;
				}
			}

			if (files_count > 1) {
				std::string_view name = *it == std::string_view("-") ? "standard input" : *it;
				if (first) *out++ = "==> " + std::string(name) + " <==";
				else       *out++ = "\n==> " + std::string(name) + " <==";
				first = false;
			}

			if (*it == std::string_view("-")) {
				head(out, to_range(std::cin), length);
				continue;
			}

			std::ifstream file_handler(*it);
			head(out, to_range(file_handler), length);
		}
	}
}
