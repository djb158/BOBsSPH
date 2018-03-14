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

#include "integrate_particle_velocity_interior.h"

double **IntegrateParticleVelocity_INTERIOR(double **x_0,double **v_0,double dt,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...IntegrateParticleVelocity_INTERIOR";

  double **x_1 = NULL;

  int l                                = 0;
  int index                            = 0;
  int n_interior_and_boundary                       = 0;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);

  if ((x_1=(double **)calloc(3,sizeof(double *)))==NULL)
  {
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
 
  x_1[0] = (double *)calloc(NPARTICLES,sizeof(double));
  x_1[1] = (double *)calloc(NPARTICLES,sizeof(double));
  x_1[2] = (double *)calloc(NPARTICLES,sizeof(double));
/*                                                                           */
/*                                                                           */
/*                                                                           */
  if (DIMENSIONS == 1)
  {
    for (l=0;l<NPARTICLES;l++)
    {
      x_1[0][l] = x_0[0][l];
    }
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      l = node_info[rank].interior_and_boundary[index];
      x_1[0][l] = x_0[0][l] + dt*v_0[0][l];
    }
  }
  if (DIMENSIONS == 2)
  {
    for (l=0;l<NPARTICLES;l++)
    {
      x_1[0][l] = x_0[0][l];
      x_1[2][l] = x_0[2][l];
    }
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      l = node_info[rank].interior_and_boundary[index];
      x_1[0][l] = x_0[0][l] + dt*v_0[0][l];
      x_1[2][l] = x_0[2][l] + dt*v_0[2][l];
    }
  }
  if (DIMENSIONS == 3)
  {
    for (l=0;l<NPARTICLES;l++)
    {
      x_1[0][l] = x_0[0][l];
      x_1[1][l] = x_0[1][l];
      x_1[2][l] = x_0[2][l];
    }
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      l = node_info[rank].interior_and_boundary[index];
      x_1[0][l] = x_0[0][l] + dt*v_0[0][l];
      x_1[1][l] = x_0[1][l] + dt*v_0[1][l];
      x_1[2][l] = x_0[2][l] + dt*v_0[2][l];
    }
  }


  exit_status = EXIT_SUCCESS;
  
RETURN:
  verbosity(2,fname,pars);
  return x_1;
}
