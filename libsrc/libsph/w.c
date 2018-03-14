/*---------------------------------------------------------------------------*\
|                                                                             |
|  File: 
|                                                                             |
|  Function: 
|                                                                             |
|  Purpose:  
|            
|                                                                             |
|  Call:                                                                      |
|           
|                                                                             |
|  Input:   
|           
|                                                                             |
|                                                                             |
|  Output:  
|          
|                                                                             |
|  Global variables:  
|                                                                             |
|  Required resources:  
|                                                                             |
|  Error:  
|-----------------------------------------------------------------------------|
|                                                                             |
|  David Brown 29-Jul-2015   initial version                                  |
|                                                                             |
|-----------------------------------------------------------------------------|
|                                                                             |
|   Copyright (c) 2015,2016 David Brown                                       |
|                                                                             |
|   This file is part of BOBsSPH                                              |
|                                                                             |
|   BOBsSPH is free software: you can redistribute it and/or modify           |
|   it under the terms of the GNU General Public License as published by      |
|   the Free Software Foundation, either version 3 of the License, or         |
|   (at your option) any later version.                                       |
|                                                                             |
|   BOBsSPH is distributed in the hope that it will be useful,                |
|   but WITHOUT ANY WARRANTY; without even the implied warranty of            |
|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             |
|   GNU General Public License for more details.                              |
|                                                                             |
|   You should have received a copy of the GNU General Public License         |
|   along with BOBsSPH.  If not, see <http://www.gnu.org/licenses/>.          |
|                                                                             |
\*---------------------------------------------------------------------------*/

#include <stdlib.h>
#include <math.h>

#define SQRTPI (1.77245385090551602729)
#define PI3o2  (5.56832799683170787119)

double W(double f,double h,int dim,double kernel_width)
{
  double w                             = -999999999.0;
  double f2                            = f*f;
  double f3                            = f2*f;
  double X                             = -999999999.0;

/*                                                                                  */
/*                                  Gaussian Kernel                                 */
/*                                                                                  */

  if (dim == 1)
  {
    X = SQRTPI*h;
  }
  if (dim == 2)
  {
    X = M_PI*h*h;
  }
  if (dim == 3)
  {
    X = PI3o2*h*h*h;
  }

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
