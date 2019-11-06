#include "float32_t.h"

float32_t FLOAT32_T(double a)
{
  float x                              = LARGE_NEGATIVE_FLOAT;

  if (fabs(a) < (double)EPSILON_LONG_LONG_DOUBLE)
  {
    x = 0.0;
  }
  else
  {
    x = a;
  }
  return x;
}
