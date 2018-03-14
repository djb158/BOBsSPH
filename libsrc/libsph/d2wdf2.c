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

#include "d2wdf2.h"

double d2Wdf2(double f,double h,int dim,double kernel_width)
{
  char   fname[]                       = "...dWdf";

  double d2wdf2                        = 0.0;
  double f2                            = 0.0;
  double f3                            = 0.0;

  f2 = f*f;
  f3 = f2*f;
/*                                                                                  */
/*                                  Gaussian Kernel                                 */
/*                                                                                  */
  if ((0.0 <= f) && (f <= kernel_width))
  {
    d2wdf2 =  2.0*(double)W2D((real_t)f,(real_t)h,(real_t)kernel_width)*(2.0*f2-1.0);
  }
  else
  {
    d2wdf2 = 0.0;
  }

  return d2wdf2;
}
