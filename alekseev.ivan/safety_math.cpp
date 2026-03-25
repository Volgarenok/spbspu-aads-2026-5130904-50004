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

int alekseev::sub(int a, int b)
{
  if (a > 0 && b < 0) {
    if (a > MAX + b) {
      throw std::overflow_error("Sub overflow");
    }
  } else if (a < 0 && b > 0) {
    if (a < MIN + b) {
      throw std::underflow_error("Sub underflow");
    }
  }
  return a - b;
}

int alekseev::mul(int a, int b)
{
  if (!a || !b) {
    return 0;
  }
  if (a > 0 && b > 0) {
    if (a > MAX / b) {
      throw std::overflow_error("Mul overflow");
    }
  } else if (a < 0 && b < 0) {
    if (a < MAX / b) {
      throw std::overflow_error("Mul overflow");
    }
  } else if (a < 0 && b > 0) {
    if (a < MIN / b) {
      throw std::underflow_error("Mul underflow");
    }
  } else if (a > 0 && b < 0) {
    if (b < MIN / a) {
      throw std::underflow_error("Mul underflow");
    }
  }
  return a * b;
}
