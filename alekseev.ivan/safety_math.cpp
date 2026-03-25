#include "safety_math.h"

#include <stdexcept>

int alekseev::sum(int a, int b)
{
  if (a > 0 && b > 0) {
    if (a > MAX - b) {
      throw std::overflow_error("Sum overflow");
    }
  } else if (a < 0 && b < 0) {
    if (a < MIN - b) {
      throw std::underflow_error("Sum underflow");
    }
  }
  return a + b;
}
