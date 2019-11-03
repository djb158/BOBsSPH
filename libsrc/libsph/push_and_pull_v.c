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

#include "push_and_pull_v.h"

int Push_and_Pull_V(PARTICLES *particles,PARS *pars,PARTICLES *x_particles)
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  MPI_Status mpi_status;

  char   fname[]                       = "...Push_and_Pull_V";

  double *VX                           = NULL;
  double *VY                           = NULL;
  double *VZ                           = NULL;

  int exit_status                      = EXIT_FAILURE;
  int tag13                            = LARGE_NEGATIVE_INT;
  int tag14                            = LARGE_NEGATIVE_INT;
  int tag15                            = LARGE_NEGATIVE_INT;
  int tag16                            = LARGE_NEGATIVE_INT;
  int tag18                            = LARGE_NEGATIVE_INT;
  int tag19                            = LARGE_NEGATIVE_INT;
  int tag20                            = LARGE_NEGATIVE_INT;
  int tag37                            = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int n_offnode_neighbours             = LARGE_NEGATIVE_INT;
  int i                                = LARGE_NEGATIVE_INT;

#include "pars_include.h"
  verbosity(1,fname,pars);
  nparticles = NPARTICLES;
/*                                                                           */
/*                 PUSH V TO NEIGHBOUR NODE                                  */
/*                                                                           */
  tag13  = 13*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].v[0],nparticles,MPI_DOUBLE,cluster_size,tag13,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send tag13 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag37  = 37*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].species,nparticles,MPI_INT,cluster_size,tag37,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send tag37 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  if (DIMENSIONS == 3)
  {
    tag14 = 14*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].v[1],nparticles,MPI_DOUBLE,cluster_size,tag14,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag14 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    tag15 = 15*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].v[2],nparticles,MPI_DOUBLE,cluster_size,tag15,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag15 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  if (DIMENSIONS == 2)
  {
    tag16 = 16*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].v[2],nparticles,MPI_DOUBLE,cluster_size,tag16,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag16 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 PULL OFF NODE PARTICLES V FROM NEIGHBOUR NODE             */
/*                                                                           */

  n_offnode_neighbours = particles[0].n_offnode_neighbours;
  if (n_offnode_neighbours > 0)
  {
    tag18  = 18*(MAX_TAGS)+rank;
    VX = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(VX,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag18,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag18 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if (DIMENSIONS == 3)
    {
      tag19  = 19*(MAX_TAGS)+rank;
      VY = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(VY,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag19,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag19 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    if ( (DIMENSIONS == 2) ||  (DIMENSIONS == 3) )
    {
      tag20  = 20*(MAX_TAGS)+rank;
      VZ = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(VZ,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag20,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag20 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }

    for (i=0;i<n_offnode_neighbours;i++)
    {
      x_particles[0].v[0][i] = VX[i];
      if (DIMENSIONS == 2)
      {
        x_particles[0].v[2][i] = VZ[i];
      }
      if (DIMENSIONS == 3)
      {
        x_particles[0].v[1][i] = VY[i];
        x_particles[0].v[2][i] = VZ[i];
      }
    }
    free(VX); VX = NULL;
    if ((DIMENSIONS ==2) || (DIMENSIONS == 3) )
    {
      free(VZ); VZ = NULL;
    }
    if (DIMENSIONS ==3) 
    {
      free(VY); VY = NULL;
    }
  }
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
