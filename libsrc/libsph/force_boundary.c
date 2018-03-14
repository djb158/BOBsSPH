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

#include "force_boundary.h"

int ForceBoundary(PARTICLES *particles_3,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...ForceBoundary";

  int l                                = LARGE_NEGATIVE_INT;
  int j                                = LARGE_NEGATIVE_INT;
  int l0                               = LARGE_NEGATIVE_INT;
  int l1                               = LARGE_NEGATIVE_INT;
  int l2                               = LARGE_NEGATIVE_INT;
  int g                                = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;
  

#include "pars_include.h"
  verbosity(1,fname,pars);

  l1 = 137118;
  l2 = 137534;

  for (g=-15;g<5;g++)
  {
    l0 = (l1+l2)/2 + g*417;
    for (l=l1;l<l2+1;l++)
    {
      j = l + g*417;
      particles_3[0].h[j]       = particles_3[0].h[l0];
      particles_3[0].p[j]       = particles_3[0].p[l0];
      particles_3[0].rho[j]     = particles_3[0].rho[l0];
      particles_3[0].U[j]       = particles_3[0].U[l0];
      particles_3[0].dUdt[j]    = particles_3[0].dUdt[l0];
      particles_3[0].divV[j]    = particles_3[0].divV[l0];
      particles_3[0].x[0][j]    = particles_3[0].x[0][l0];
      particles_3[0].v[0][j]    = particles_3[0].v[0][l0];
      particles_3[0].v[2][j]    = particles_3[0].v[2][l0];
      particles_3[0].dvdt[0][j] = particles_3[0].dvdt[0][l0];
      particles_3[0].dvdt[2][j] = particles_3[0].dvdt[2][l0];
    }
  }

/*
  for (g=0;g<5;g++)
  {
    for (l=l1;l<l2+1;l++)
    {
      j = l + g*417;
      particles_3[0].h[j]       = particles_3[0].h[l0];
      particles_3[0].p[j]       = particles_3[0].p[l0];
      particles_3[0].rho[j]     = particles_3[0].rho[l0];
      particles_3[0].U[j]       = particles_3[0].U[l0];
      particles_3[0].dUdt[j]    = particles_3[0].dUdt[l0];
      particles_3[0].divV[j]    = particles_3[0].divV[l0];
      particles_3[0].x[0][j]    = particles_3[0].x[0][l0];
      particles_3[0].v[0][j]    = particles_3[0].v[0][l0];
      particles_3[0].v[2][j]    = particles_3[0].v[2][l0];
      particles_3[0].dvdt[0][j] = particles_3[0].dvdt[0][l0];
      particles_3[0].dvdt[2][j] = particles_3[0].dvdt[2][l0];
    }
  }
*/
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
