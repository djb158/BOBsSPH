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

#include "push_n.h"

int Push_N(PARTICLES *particles,PARS *pars)
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  MPI_Status mpi_status;

  char   fname[]                       = "...Push_N";
  int exit_status                      = EXIT_FAILURE;
  int tag1                             = LARGE_NEGATIVE_INT;
  int tag2                             = LARGE_NEGATIVE_INT;
  int tag3                             = LARGE_NEGATIVE_INT;
  int tag4                             = LARGE_NEGATIVE_INT;
  int tag58                            = LARGE_NEGATIVE_INT;
  int tag59                            = LARGE_NEGATIVE_INT;
  int tag60                            = LARGE_NEGATIVE_INT;
  int tag61                            = LARGE_NEGATIVE_INT;
  int tag70                            = LARGE_NEGATIVE_INT;
  int tag71                            = LARGE_NEGATIVE_INT;
  int tag72                            = LARGE_NEGATIVE_INT;
  int tag80                            = LARGE_NEGATIVE_INT;
  int tag81                            = LARGE_NEGATIVE_INT;
  int tag83                            = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int i                                = LARGE_NEGATIVE_INT;
  int action                           = LARGE_NEGATIVE_INT;

#include "pars_include.h"
  verbosity(1,fname,pars);
/*                                                                           */
/*                                                                           */
/*                                                                           */
  if (rank == 0)
  {
    action = LARGE_NEGATIVE_INT;
    tag80  = 80*(MAX_TAGS)+rank;
    if ( (MPI_Send(&action,1,MPI_INT,cluster_size,tag80,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag80 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  nparticles = node_info[rank].nparticles;
  tag58  = 58*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].x[0],nparticles,MPI_DOUBLE,cluster_size,tag58,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag1  = 1*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].v[0],nparticles,MPI_DOUBLE,cluster_size,tag1,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag70  = 70*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].p,nparticles,MPI_DOUBLE,cluster_size,tag70,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag71  = 71*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].rho,nparticles,MPI_DOUBLE,cluster_size,tag71,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag72  = 72*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].h,nparticles,MPI_DOUBLE,cluster_size,tag72,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag81  = 81*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].divV,nparticles,MPI_DOUBLE,cluster_size,tag81,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send tag81 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag83  = 83*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles[0].U,nparticles,MPI_DOUBLE,cluster_size,tag83,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send tag81 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  if (DIMENSIONS == 3)
  {
    tag59 = 59*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].x[1],nparticles,MPI_DOUBLE,cluster_size,tag59,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    tag2 = 2*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].v[1],nparticles,MPI_DOUBLE,cluster_size,tag2,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    tag60 = 60*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].x[2],nparticles,MPI_DOUBLE,cluster_size,tag60,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    tag3 = 3*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].v[2],nparticles,MPI_DOUBLE,cluster_size,tag3,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  if (DIMENSIONS == 2)
  {
    tag61  = 61*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].x[2],nparticles,MPI_DOUBLE,cluster_size,tag61,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    tag4  = 4*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles[0].v[2],nparticles,MPI_DOUBLE,cluster_size,tag4,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
