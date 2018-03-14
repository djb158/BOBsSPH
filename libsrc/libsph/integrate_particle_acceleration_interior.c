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

#include "integrate_particle_acceleration_interior.h"

double **IntegrateParticleAcceleration_INTERIOR(double **vel_x,double **accel_x,double dt,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...IntegrateParticleAcceleration_INTERIOR";

  double **vel                         = NULL;

  int i                                = 0;
  int index                            = 0;
  int n_interior_and_boundary          = 0;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);

  if ((vel=(double **)calloc(3,sizeof(double *)))==NULL)
  {
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  vel[0] = (double *)calloc(NPARTICLES,sizeof(double));
  vel[1] = (double *)calloc(NPARTICLES,sizeof(double));
  vel[2] = (double *)calloc(NPARTICLES,sizeof(double));
  for (i=0;i<NPARTICLES;i++)
  {
    vel[0][i] = LARGE_NEGATIVE_DOUBLE;
    vel[1][i] = LARGE_NEGATIVE_DOUBLE;
    vel[2][i] = LARGE_NEGATIVE_DOUBLE;
  }
/*                                                                           */
/*                                                                           */
/*                                                                           */
  if (DIMENSIONS == 1)
  {
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      i = node_info[rank].interior_and_boundary[index];
      vel[0][i] = vel_x[0][i] + dt*accel_x[0][i];
    }
  }
  if (DIMENSIONS == 2)
  {
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      i = node_info[rank].interior_and_boundary[index];
      vel[0][i] = vel_x[0][i] + dt*accel_x[0][i];
      vel[2][i] = vel_x[2][i] + dt*accel_x[2][i];
    }
  }
  if (DIMENSIONS == 3)
  {
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      i = node_info[rank].interior_and_boundary[index];
      vel[0][i] = vel_x[0][i] + dt*accel_x[0][i];
      vel[1][i] = vel_x[1][i] + dt*accel_x[1][i];
      vel[2][i] = vel_x[2][i] + dt*accel_x[2][i];
    }
  }

  
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return vel;
}
 
