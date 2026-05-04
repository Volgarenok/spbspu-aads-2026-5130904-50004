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
  using Row = dolenko::BiList< long long >;

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

  bool buildTransposedRowsAndSums(const dolenko::BiList< Sequence >& sequences,
      dolenko::BiList< Row >& rows,
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
      bool anyAdded = false;
      Row row;
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

          anyAdded = true;
          row.push_back(value);
          ++(*cur).it;
        }
      }
      if (!anyAdded)
      {
        break;
      }
      rows.push_back(std::move(row));
      sums.push_back(rowSum);
    }
    return true;
  }

  void printRows(const dolenko::BiList< Row >& rows)
  {
    for (auto rowIt = rows.begin(); rowIt != rows.end(); ++rowIt)
    {
      bool first = true;
      for (auto it = (*rowIt).begin(); it != (*rowIt).end(); ++it)
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

  dolenko::BiList< Row > rows;
  dolenko::BiList< long long > sums;
  if (!buildTransposedRowsAndSums(sequences, rows, sums))
  {
    std::cerr << "Error\n";
    return 1;
  }

  printNames(sequences);
  printRows(rows);
  printSums(sums);
  return 0;
}