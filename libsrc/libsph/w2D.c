/*---------------------------------------------------------------------------*\
|                                                                             |
| File:                                                                       |
|             w2D.c                                                           |
|                                                                             |
| Function:                                                                   |
|             real_t W2D(real_t f,real_t h,real_t kernel_width)               |
|                                                                             |
| Call:                                                                       |
|             X = W2D(f,h,kernel_width);                                      |
|                                                                             |
| Purpose:                                                                    |
|             This function defines the SPH kernel function to be used        |
|             for 2D simulations                                              |
|                                                                             |
| Input:      real_t f             non-dimensional particle separation        |
|             real_t h             smoothing length                           |
|             real_t kernel_width  multiples of h where W2D vanishes          |
|                                                                             |
| Output:     W2D                                                             |
|                                                                             |
| Returned                                                                    |
| Value:      real_t                                                          |
|                                                                             |
| Global                                                                      |
| Variables:  None                                                            |
|                                                                             |
| Required                                                                    |
| Resources:  None                                                            |
|                                                                             |
| Error checking: None                                                        |
|                                                                             |
\*---------------------------------------------------------------------------*/

#include <stdlib.h>
#include <math.h>

typedef double real_t;

real_t W2D(real_t f,real_t h,real_t kernel_width)
{
  real_t w                             = -999999999.0;
  real_t f2                            = f*f;
  real_t f3                            = f2*f;
  real_t X                             = -999999999.0;
/*                                                                           */
/*                                  Gaussian Kernel                          */
/*                                                                           */
  X = M_PI*h*h;
  if ((0.0 <= f) && (f <= kernel_width) )
  {
    w = exp(-f2);
  }
  else
  {
    w = 0.0;
  }

  w = w/X;

  return w;
}
