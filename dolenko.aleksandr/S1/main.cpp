#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <utility>

#include "BiList.hpp"

namespace
{
	using Sequence = std::pair< std::string, dolenko::BiList< long long > >;
	using NumIter = dolenko::LCIter< long long >;

	struct Cursor
	{
		NumIter it;
		NumIter end;
	};

	bool safeAdd(long long a, long long b, long long& result) noexcept
	{
		if ((b > 0) && (a > (std::numeric_limits< long long >::max() - b)))
		{
			return false;
		}
		if ((b < 0) && (a < (std::numeric_limits< long long >::min() - b)))
		{
			return false;
		}
		result = a + b;
		return true;
	}

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

	void printNames(const dolenko::BiList< Sequence >& sequences)
	{
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
	}

	bool printTransposedAndCollectSums(const dolenko::BiList< Sequence >& sequences,
		dolenko::BiList< long long >& sums)
	{
		dolenko::BiList< Cursor > cursors;
		for (auto it = sequences.begin(); it != sequences.end(); ++it)
		{
			const auto& nums = (*it).second;
			cursors.push_back(Cursor{ nums.begin(), nums.end() });
		}

		while (true)
		{
			bool anyPrinted = false;
			bool firstInRow = true;
			long long rowSum = 0;
			for (auto cur = cursors.begin(); cur != cursors.end(); ++cur)
			{
				if ((*cur).it != (*cur).end)
				{
					const long long value = *(*cur).it;
					if (!safeAdd(rowSum, value, rowSum))
					{
						return false;
					}

					if (!firstInRow)
					{
						std::cout << ' ';
					}
					firstInRow = false;
					anyPrinted = true;
					std::cout << value;
					++(*cur).it;
				}
			}
			if (!anyPrinted)
			{
				break;
			}
			std::cout << '\n';
			sums.push_back(rowSum);
		}
		return true;
	}

	void printSums(const dolenko::BiList< long long >& sums)
	{
		bool first = true;
		for (auto it = sums.begin(); it != sums.end(); ++it)
		{
			if (!first)
			{
				std::cout << ' ';
			}
			first = false;
			std::cout << *it;
		}
		std::cout << '\n';
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
	printNames(sequences);
	dolenko::BiList< long long > sums;
	if (!printTransposedAndCollectSums(sequences, sums))
	{
		std::cerr << "Error\n";
		return 1;
	}
	printSums(sums);
	return 0;
}