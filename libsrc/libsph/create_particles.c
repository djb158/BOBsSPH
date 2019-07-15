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
|   Copyright (c) 2015,2016,2017 David Brown                                  |
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

#include "create_particles.h"

PARTICLES *CreateParticles(int N,PARS *pars)
{
  extern int cluster_size;

  char   fname[]                       = "...CreateParticles";

  PARTICLES *particles                 = NULL;

  int i                                = 0;
  int j                                = 0;
  int k                                = 0;
  int number_of_doubles                = 0;
  int number_of_ints                   = 0;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);

  if ( (particles=(PARTICLES *)calloc(1,sizeof(PARTICLES)))==NULL)
  {
    printf(" InitializeParticles: -unable to allocate memory to structure PARTICLES, aborting\n");
    exit_status  = EXIT_FAILURE;
    goto RETURN;
  }
/*                                                                           */
/*                                                                           */
/*                                                                           */
  particles[0].x                    = (double **)calloc(3,sizeof(double *));
  particles[0].v                    = (double **)calloc(3,sizeof(double *));
  particles[0].dvdt                 = (double **)calloc(3,sizeof(double *));
  particles[0].m                    = (double *)calloc(N,sizeof(double));
  particles[0].h                    = (double *)calloc(N,sizeof(double));
  particles[0].p                    = (double *)calloc(N,sizeof(double));
  particles[0].rho                  = (double *)calloc(N,sizeof(double));
  particles[0].U                    = (double *)calloc(N,sizeof(double));
  particles[0].dUdt                 = (double *)calloc(N,sizeof(double));
  particles[0].divV                 = (double *)calloc(N,sizeof(double));
  particles[0].x[0]                 = (double *)calloc(N,sizeof(double));
  particles[0].x[1]                 = (double *)calloc(N,sizeof(double));
  particles[0].x[2]                 = (double *)calloc(N,sizeof(double));
  particles[0].v[0]                 = (double *)calloc(N,sizeof(double));
  particles[0].v[1]                 = (double *)calloc(N,sizeof(double));
  particles[0].v[2]                 = (double *)calloc(N,sizeof(double));
  particles[0].dvdt[0]              = (double *)calloc(N,sizeof(double));
  particles[0].dvdt[1]              = (double *)calloc(N,sizeof(double));
  particles[0].dvdt[2]              = (double *)calloc(N,sizeof(double));
  particles[0].raw_index            = (int *)calloc(N,sizeof(int));
  particles[0].species              = (int *)calloc(N,sizeof(int));
  particles[0].nn                   = (int **)calloc(N,sizeof(int *));
  particles[0].nn_index             = (NN_INDEX *)calloc(N,sizeof(NN_INDEX));

  number_of_doubles                 = NUMBER_OF_DOUBLES;
  number_of_ints                    = NUMBER_OF_INTS;
  particles[0].number_of_doubles    = number_of_doubles;
  particles[0].number_of_ints       = number_of_ints;
  particles[0].steps_to_reindex     = STEPS_TO_REINDEX;
  particles[0].t                    = LARGE_NEGATIVE_DOUBLE;
  particles[0].step                 = 0;
  particles[0].rank                 = rank;
  particles[0].n_offnode_neighbours = LARGE_NEGATIVE_INT;
/*                                                                           */
/*                 regular nodes will only have one of the following vector  */
/*                 elements set, ie when i == rank, the rank == cluster_size */
/*                 node will have all of them set.                           */
/*                                                                           */
  for (i=0;i<N;i++)
  {
    particles[0].nn[i]                             = (int *)calloc(NN_K,sizeof(int));
    for (k=0;k<NN_K;k++)
    {
      particles[0].nn[i][k]                        = LARGE_NEGATIVE_INT;
    }
    particles[0].nn_index[i].num                   = LARGE_NEGATIVE_INT;
    particles[0].nn_index[i].node                  = NULL;
    particles[0].nn_index[i].n_offnode_neighbours  = NULL;
    particles[0].raw_index[i]                      = LARGE_NEGATIVE_INT;
    particles[0].species[i]                        = LARGE_NEGATIVE_INT;
    particles[0].m[i]                              = PARTICLE_MASS;
    particles[0].h[i]                              = LARGE_NEGATIVE_DOUBLE;
    particles[0].x[0][i]                           = LARGE_NEGATIVE_DOUBLE;
    particles[0].x[1][i]                           = LARGE_NEGATIVE_DOUBLE;
    particles[0].x[2][i]                           = LARGE_NEGATIVE_DOUBLE;
    particles[0].v[0][i]                           = LARGE_NEGATIVE_DOUBLE;
    particles[0].v[1][i]                           = LARGE_NEGATIVE_DOUBLE;
    particles[0].v[2][i]                           = LARGE_NEGATIVE_DOUBLE;
    particles[0].dvdt[0][i]                        = LARGE_NEGATIVE_DOUBLE;
    particles[0].dvdt[1][i]                        = LARGE_NEGATIVE_DOUBLE;
    particles[0].dvdt[2][i]                        = LARGE_NEGATIVE_DOUBLE;
    particles[0].p[i]                              = LARGE_NEGATIVE_DOUBLE;
    particles[0].rho[i]                            = LARGE_NEGATIVE_DOUBLE;
    particles[0].U[i]                              = LARGE_NEGATIVE_DOUBLE;
    particles[0].dUdt[i]                           = LARGE_NEGATIVE_DOUBLE;
    particles[0].divV[i]                           = LARGE_NEGATIVE_DOUBLE;
  }
/*                                                                            */
/*                                                                            */
/*                                                                            */
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return particles;
}
