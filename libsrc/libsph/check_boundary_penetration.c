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

#include "check_boundary_penetration.h"

int CheckBoundaryPenetration(double **x_3,double **v_3,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...CheckBoundaryPenetration";

  double x_l                           = LARGE_NEGATIVE_DOUBLE;
  double z_l                           = LARGE_NEGATIVE_DOUBLE;
  double vx_l                          = LARGE_NEGATIVE_DOUBLE;
  double vz_l                          = LARGE_NEGATIVE_DOUBLE;

  int l                                = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;
  int index                            = LARGE_NEGATIVE_INT;
  int n_interior                       = LARGE_NEGATIVE_INT;
  

#include "pars_include.h"
  verbosity(1,fname,pars);

  n_interior = node_info[rank].n_interior;

  if (DIMENSIONS == 2)
  {
    for (index=0;index<n_interior;index++)
    {
      l    = node_info[rank].interior[index];
      x_l  = x_3[0][l];
      z_l  = x_3[2][l];
      vx_l = v_3[0][l];
      vz_l = v_3[2][l];
      if (x_l > X1-EPSILON_DOUBLE)
      {
        v_3[0][l] = -vx_l;
        x_3[0][l] = X1 - (x_l-X1);
        printf(" %s() -particle %i X1 boundary penetration\n",fname,l);
      }
      if (x_l < X0+EPSILON_DOUBLE)
      {
        v_3[0][l] = -vx_l;
        x_3[0][l] = X0 + (X0-x_l);
        printf(" %s() -particle %i X0 boundary penetration\n",fname,l);
      }
      if (z_l > Z1-EPSILON_DOUBLE)
      {
        v_3[2][l] = -vz_l;
        x_3[2][l] = Z1 - (z_l-Z1);
        printf(" %s() -particle %i Z1 boundary penetration\n",fname,l);
      }
      if (z_l < Z0+EPSILON_DOUBLE)
      {
        v_3[2][l] = -vz_l;
        x_3[2][l] = Z0 + (Z0-z_l);
        printf(" %s() -particle %i Z0 boundary penetration\n",fname,l);
      }
    }
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
