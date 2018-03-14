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

#include "dwdf.h"

double dWdf(double f,double h,int dim,double kernel_width)
{
  char   fname[]                       = "...dWdf";

  double dwdf = 0.0;
  double f2   = 0.0;
  double f3   = 0.0;

  f2 = f*f;
  f3 = f2*f;
/*                                                                                  */
/*                                  Gaussian Kernel                                 */
/*                                                                                  */
  if ((0.0 <= f) && (f <= kernel_width))
  {
    dwdf =  -2.0*f*(double)W2D((real_t)f,(real_t)h,(real_t)kernel_width);
  }
  else
  {
    dwdf = 0.0;
  }
/*                                                                                  */
/*                                  Spline Kernel                                   */
/*                                                                                  */
/*if ((0.0 <= f) && (f < 1.0) )
  {
    dwdf = -3.0*f + 2.25*f2;
  }
  else if ((1.0 <= f) && (f < 2.0) )
  {
    dwdf = -0.75*(2.0-f)*(2.0-f);
  }
  else
  {
    dwdf = 0.0;
  } */

  return dwdf;
}
