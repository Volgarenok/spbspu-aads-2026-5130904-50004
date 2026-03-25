#ifndef SAFETY_MATH_H
#define SAFETY_MATH_H

#include <limits>

namespace alekseev {
  int sum(int a, int b);
  int sub(int a, int b);
  int mul(int a, int b);
  int div(int a, int b);
  int mod(int a, int b);
  int flip(int a);

  const int MAX = std::numeric_limits< int >::max();
  const int MIN = std::numeric_limits< int >::min();
}

#endif
