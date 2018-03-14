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

#include "push_and_pull_p.h"

int Push_and_Pull_P(PARTICLES *particles,PARS *pars,PARTICLES *x_particles)
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  MPI_Status mpi_status;

  char   fname[]                       = "...Push_and_Pull_P";

  double *P                            = NULL;

  int exit_status                      = EXIT_FAILURE;
  int tag30                            = LARGE_NEGATIVE_INT;
  int tag32                            = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int n_offnode_neighbours             = LARGE_NEGATIVE_INT;
  int i                                = LARGE_NEGATIVE_INT;

#include "pars_include.h"
  verbosity(1,fname,pars);
  nparticles = NPARTICLES;
/*                                                                           */
/*                                                                           */
/*                                                                           */
  tag30  = 30*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].p,nparticles,MPI_DOUBLE,cluster_size,tag30,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send tag30 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  n_offnode_neighbours = particles[0].n_offnode_neighbours;
  if (n_offnode_neighbours > 0)
  {
    tag32  = 32*(MAX_TAGS)+rank;
    P = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(P,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag32,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag32 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    for (i=0;i<n_offnode_neighbours;i++)
    {
      x_particles[0].p[i] = P[i];
    }
    Free_sph(P);
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
