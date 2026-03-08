#include "proc.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

void kuchukbaeva::prInput(std::istream& in, OutList& seque)
{
  std::string name = "";
  LIter< std::pair< std::string, InList > > seqTail = seque.beforeBegin();

  while (in >> name) {
    InList seq;
    LIter< unsigned long long > tail = seq.beforeBegin();

    while (true) {
      int c = in.get();
      while (c == ' ' || c == '\t' || c == '\r') {
        c = in.get();
      }
      if (c == '\n' || c == EOF) {
        break;
      }
      in.unget();

      unsigned long long val = 0;
      if (in >> val) {
        tail = seq.insertAfter(tail, val);
      } else {
        in.clear();
        break;
      }
    }
    seqTail = seque.insertAfter(seqTail, std::make_pair(name, std::move(seq)));
  }
}

int kuchukbaeva::execLogic(const OutList& seque, std::ostream& out, std::ostream& err)
{
  if (seque.isEmpty()) {
    out << "0\n";
    return 0;
  }

  List< LCIter< unsigned long long > > iters;
  LIter< LCIter< unsigned long long > > itersTail = iters.beforeBegin();
  for (LCIter< std::pair< std::string, InList > > it = seque.cbegin(); it != seque.cend(); ++it) {
    itersTail = iters.insertAfter(itersTail, (*it).second.cbegin());
  }

  bool hasMore = true;
  List< unsigned long long > sums;
  List< unsigned long long > sumsTail = sums.beforeBegin();

  while (hasMore) {
    hasMore = false;
    List< unsigned long long > row;
    LIter< unsigned long long > rowTail = row.beforeBegin();
    LIter< unsigned long long > iterNode = iters.begin();
    LCIter< std::pair< std::string, InList > > seqIt = seque.cbegin();

    unsigned long long currentSum = 0;
    bool isSum = true;
    bool rowHasElements = false;

    while (iterNode != iters.end()) {
      if (*iterNode != (*seqIt).second.cend()) {
        const unsigned long long val = **iterNode;
        rowTail = row.insertAfter(rowTail, val);
        rowHasElements = true;

        if (std::numeric_limits< unsigned long long >::max() - currentSum < val) {
          isSum = false;
        } else {
          currentSum += val;
        }

        ++(*iterNode);
        hasMore = true;
      }
      ++iterNode;
      ++seqIt;
    }

    if (rowHasElements) {
      bool isFirst = true;
      for (LCIter< unsigned long long > it = row.cbegin(); it != row.cend(); ++it) {
        if (!isFirst) out << " ";
        out << *it;
        isFirst = false;
      }
      out << "\n";
      if (!isSum) {
        err << "Error: Overflow\n";
        return 1;
      }
      sumsTail = sums.insertAfter(sumsTail, currentSum);
    }
  }

  if (sums.isEmpty()) {
    out << "0\n";
  } else {
    isFirst = true;
    for (LCIter< unsigned long long > it = sums.cbegin(); it != sums.cend(); ++it) {
      if (!isFirst) {
        out << " ";
      }
      out << *it;
      isFirst = false;
    }
    out << "\n";
  }
  return 0;
}
