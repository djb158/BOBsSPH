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

#include "calculate_particle_acceleration_interior_thread_wrapper.h"

double **CalculateParticleAcceleration_INTERIOR_thread_wrapper(PARTICLES *particles,PARTICLES *x_particles,PARS *pars)
{
  extern NODE_INFO *node_info;

  pthread_t *thread                    = NULL;
  THREAD_DATA *data                    = NULL;

  char   fname[]                       = "...CalculateParticleAcceleration_INTERIOR_thread_wrapper";

  double **a                           = NULL;

  int i                                = LARGE_NEGATIVE_INT;
  int tasks_per_thread                 = LARGE_NEGATIVE_INT;
  int n_interior_and_boundary          = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;
  int *err                             = NULL;

#include "pars_include.h"
  verbosity(1,fname,pars);

  n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
  tasks_per_thread        = (n_interior_and_boundary+COMPUTE_THREADS-1)/COMPUTE_THREADS;
  thread                  = (pthread_t *)calloc(COMPUTE_THREADS,sizeof(pthread_t));
  data                    = (THREAD_DATA *)calloc(COMPUTE_THREADS,sizeof(THREAD_DATA));
  err                     = (int *)calloc(COMPUTE_THREADS,sizeof(int));

  if ((a=(double **)calloc(3,sizeof(double *)))==NULL)
  {
    goto RETURN;
  }

  a[0] = (double *)calloc(NPARTICLES,sizeof(double));
  a[1] = (double *)calloc(NPARTICLES,sizeof(double));
  a[2] = (double *)calloc(NPARTICLES,sizeof(double));
  for (i=0;i<NPARTICLES;i++)
  {
    a[0][i] = LARGE_NEGATIVE_DOUBLE;
    a[1][i] = LARGE_NEGATIVE_DOUBLE;
    a[2][i] = LARGE_NEGATIVE_DOUBLE;
  }

  for (i=0; i<COMPUTE_THREADS; i++)
  {
    data[i].exit_status = &exit_status;
    data[i].start       = i*tasks_per_thread;
    data[i].stop        = (i+1)*tasks_per_thread;
    data[i].matrix      = a;
    data[i].vector      = NULL;
    data[i].particles   = particles;
    data[i].x_particles = x_particles;
    data[i].pars        = pars;
    err[i]              = LARGE_NEGATIVE_INT;
  }
  data[COMPUTE_THREADS-1].stop = n_interior_and_boundary;

  for (i=0; i<COMPUTE_THREADS; i++)
  {
    err[i] = pthread_create(&thread[i], NULL,CalculateParticleAcceleration_INTERIOR, data+i);
  }

  for (i=0; i<COMPUTE_THREADS; i++)
  {
    pthread_join(thread[i], NULL);
  }

  for (i=0; i<COMPUTE_THREADS; i++)
  {
    if ( (*data[i].exit_status == EXIT_FAILURE) || (err[i] != 0) )
    {
      exit_status = EXIT_FAILURE;
      printf(" Rank: %i  %s() -error return from pthread_create for CalculateParticleAcceleration_INTERIOR() \n",rank,fname);
      if (a)
      {
        Free_sph(a[0]);
        Free_sph(a[1]);
        Free_sph(a[2]);
        Free_sph(a);
      }
      a = NULL;
      goto RETURN;
    }
  }

  for (i=0; i<COMPUTE_THREADS; i++)
  {
    data[i].particles   = NULL;
    data[i].x_particles = NULL;
    data[i].pars        = NULL;
    data[i].matrix      = NULL;
    data[i].vector      = NULL;
  }
  Free_sph(thread);
  Free_sph(data);
  Free_sph(err);

  exit_status = EXIT_SUCCESS;
RETURN:
  verbosity(2,fname,pars);
  free(err);
  return a;
}
