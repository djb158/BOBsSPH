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

#include "push_and_pull_n_and_x.h"

PARTICLES *Push_and_Pull_N_and_X(PARTICLES *particles_3,PARS *pars)
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  MPI_Status mpi_status;

  PARTICLES *x_particles               = NULL;

  char   fname[]                       = "...Push_and_Pull_N_and_X";

  double *X                            = NULL;
  double *Y                            = NULL;
  double *Z                            = NULL;

  int *x_NN                            = NULL;
  int *x_nn_index                      = NULL;
  int exit_status                      = EXIT_FAILURE;
  int tag1                             = LARGE_NEGATIVE_INT;
  int tag2                             = LARGE_NEGATIVE_INT;
  int tag3                             = LARGE_NEGATIVE_INT;
  int tag4                             = LARGE_NEGATIVE_INT;
  int tag5                             = LARGE_NEGATIVE_INT;
  int tag6                             = LARGE_NEGATIVE_INT;
  int tag7                             = LARGE_NEGATIVE_INT;
  int tag8                             = LARGE_NEGATIVE_INT;
  int tag9                             = LARGE_NEGATIVE_INT;
  int tag10                            = LARGE_NEGATIVE_INT;
  int tag11                            = LARGE_NEGATIVE_INT;
  int tag12                            = LARGE_NEGATIVE_INT;
  int tag36                            = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int j                                = LARGE_NEGATIVE_INT;
  int k                                = LARGE_NEGATIVE_INT;
  int l                                = LARGE_NEGATIVE_INT;
  int num                              = LARGE_NEGATIVE_INT;
  int i                                = LARGE_NEGATIVE_INT;
  int action                           = LARGE_NEGATIVE_INT; 
  int n_offnode_neighbours             = LARGE_NEGATIVE_INT;
  int num_ints                         = LARGE_NEGATIVE_INT;

#include "pars_include.h"
  verbosity(1,fname,pars);
  nparticles = NPARTICLES;
/*                                                                           */
/*                                                                           */
/*                                                                           */
  if (rank == 0)
  {
    action = LARGE_NEGATIVE_INT;
    tag1  = 1*(MAX_TAGS)+rank;
    if ( (MPI_Send(&action,1,MPI_INT,cluster_size,tag1,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag1 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  tag2  = 2*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles_3[0].x[0],nparticles,MPI_DOUBLE,cluster_size,tag2,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send tag2 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  tag36  = 36*(MAX_TAGS)+rank;
  if ( (MPI_Send(particles_3[0].species,nparticles,MPI_INT,cluster_size,tag36,MPI_COMM_WORLD)) != MPI_SUCCESS)
  {
    printf(" %s(): unable to send tag36 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

  if (DIMENSIONS == 2)
  {
    tag3  = 3*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles_3[0].x[2],nparticles,MPI_DOUBLE,cluster_size,tag3,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag3 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }

  if (DIMENSIONS == 3)
  {
    tag4 = 4*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles_3[0].x[1],nparticles,MPI_DOUBLE,cluster_size,tag4,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag4 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    tag5 = 5*(MAX_TAGS)+rank;
    if ( (MPI_Send(particles_3[0].x[2],nparticles,MPI_DOUBLE,cluster_size,tag5,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag5 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }

/*
###### PULL 
*/

  tag6  = 6*(MAX_TAGS)+rank;
  x_NN = (int *)calloc(NPARTICLES*NN_K,sizeof(int));
  if ( (MPI_Recv(x_NN,NPARTICLES*NN_K,MPI_INT,cluster_size,tag6,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
  {
    printf(" %s(): unable to receive tag6 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  } 

  j = 0;
  for (i=0;i<NPARTICLES;i++)
  {
    for (k=0;k<NN_K;k++)
    {
      particles_3[0].nn[i][k] = x_NN[j]; 
      j++;
    }
  }
  free(x_NN);
  x_NN = NULL;
  tag7  = 7*(MAX_TAGS)+rank;
  if ( (MPI_Recv(&n_offnode_neighbours,1,MPI_INT,cluster_size,tag7,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
  {
    printf(" %s(): unable to receive tag7 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  } 
  particles_3[0].n_offnode_neighbours = n_offnode_neighbours;
  if (n_offnode_neighbours > 0)
  {
    x_particles = CreateParticles(n_offnode_neighbours,pars);

    tag8  = 8*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&num_ints,1,MPI_INT,cluster_size,tag8,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag8 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag9  = 9*(MAX_TAGS)+rank;
    x_nn_index = (int *)calloc(num_ints,sizeof(int));
    if ( (MPI_Recv(x_nn_index,num_ints,MPI_INT,cluster_size,tag9,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag9 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag10  = 10*(MAX_TAGS)+rank;
    X = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(X,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag10,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag10 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 

    if (DIMENSIONS == 3)
    {
      tag11  = 11*(MAX_TAGS)+rank;
      Y = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(Y,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag11,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag11 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      } 
    }
    if ( (DIMENSIONS == 2) || (DIMENSIONS == 3) )
    {
      tag12  = 12*(MAX_TAGS)+rank;
      Z = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(Z,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag12,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag12 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      } 
    }

    l = 0;
    for (i=0;i<NPARTICLES;i++)
    {
      num =  x_nn_index[l];
      l++;
      particles_3[0].nn_index[i].num                   = num;
      particles_3[0].nn_index[i].node                  = NULL;
      particles_3[0].nn_index[i].n_offnode_neighbours  = NULL;
      if (num > 0)
      {
        particles_3[0].nn_index[i].node                  = (int *)calloc(num,sizeof(int));
        particles_3[0].nn_index[i].n_offnode_neighbours  = (int *)calloc(num,sizeof(int));
        for (j=0;j<num;j++)
        {
          particles_3[0].nn_index[i].node[j]                 = x_nn_index[l];
          l++;
          particles_3[0].nn_index[i].n_offnode_neighbours[j] =x_nn_index[l]; 
          l++;
        }
      }
    }
    Free_sph(x_nn_index);

    for (i=0;i<n_offnode_neighbours;i++)
    {
      x_particles[0].x[0][i]  = X[i];
      x_particles[0].m[i]     = PARTICLE_MASS;
      if (DIMENSIONS == 2)
      {
        x_particles[0].x[2][i] = Z[i];
      }
      if (DIMENSIONS == 3)
      {
        x_particles[0].x[1][i] = Y[i];
        x_particles[0].x[2][i] = Z[i];
      }
    }
    free(X);               X = NULL;
    if ((DIMENSIONS ==2) || (DIMENSIONS == 3) )
    {
      free(Z);   Z = NULL;
    }
    if (DIMENSIONS ==3) 
    {
      free(Y);   Y = NULL;
    }
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return x_particles;
}
