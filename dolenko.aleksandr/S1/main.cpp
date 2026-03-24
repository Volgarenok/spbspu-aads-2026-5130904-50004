#include <cctype>
#include <iostream>
#include <string>
#include <utility>

#include "BiList.hpp"

namespace
{
	using Sequence = std::pair< std::string, dolenko::BiList< long long > >;

	dolenko::BiList< Sequence > readSequences(std::istream& in)
	{
		dolenko::BiList< Sequence > sequences;

		std::string name;
		in >> std::skipws;
		while (in >> name)
		{
			dolenko::BiList< long long > numbers;

			in >> std::noskipws;
			while (true)
			{
				char ch = 0;
				if (!in.get(ch))
				{
					break;
				}
				if (ch == '\r')
				{
					continue;
				}
				if (ch == '\n')
				{
					break;
				}
				if (std::isspace(static_cast< unsigned char >(ch)))
				{
					continue;
				}

				in.unget();
				long long value = 0;
				in >> value;
				numbers.push_back(value);
			}

			in >> std::skipws;
			sequences.push_back(Sequence(std::move(name), std::move(numbers)));
		}

		return sequences;
	}
}

int main()
{
	auto sequences = readSequences(std::cin);
	if (sequences.empty())
	{
		std::cout << 0 << '\n';
		return 0;
	}

	bool first = true;
	for (auto it = sequences.begin(); it != sequences.end(); ++it)
	{
		if (!first)
		{
			std::cout << ' ';
		}
		first = false;
		std::cout << (*it).first;
	}
	std::cout << '\n';
	return 0;
}