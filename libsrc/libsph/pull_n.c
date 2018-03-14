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

#include "pull_n.h"

PARTICLES *Pull_N(PARS *pars,PARTICLES *particles_3)
{

  extern int cluster_size;
  extern NODE_INFO *node_info;

  MPI_Status mpi_status;

  PARTICLES *x_particles               =  NULL;

  char   fname[]                       = "...Pull_N";

  double *X                            = NULL;
  double *Y                            = NULL;
  double *Z                            = NULL;
  double *VX                           = NULL;
  double *VY                           = NULL;
  double *VZ                           = NULL;
  double *P                            = NULL;
  double *RHO                          = NULL;
  double *H                            = NULL;
  double *divV                         = NULL;
  double *U                            = NULL;

  int num                              = LARGE_NEGATIVE_INT;
  int tag6                             = LARGE_NEGATIVE_INT;
  int tag7                             = LARGE_NEGATIVE_INT;
  int tag8                             = LARGE_NEGATIVE_INT;
  int tag62                            = LARGE_NEGATIVE_INT;
  int tag63                            = LARGE_NEGATIVE_INT;
  int tag64                            = LARGE_NEGATIVE_INT;
  int tag65                            = LARGE_NEGATIVE_INT;
  int tag66                            = LARGE_NEGATIVE_INT;
  int tag74                            = LARGE_NEGATIVE_INT;
  int tag75                            = LARGE_NEGATIVE_INT;
  int tag76                            = LARGE_NEGATIVE_INT;
  int tag78                            = LARGE_NEGATIVE_INT;
  int tag79                            = LARGE_NEGATIVE_INT;
  int tag82                            = LARGE_NEGATIVE_INT;
  int tag84                            = LARGE_NEGATIVE_INT;
  int i                                = LARGE_NEGATIVE_INT;
  int j                                = LARGE_NEGATIVE_INT; 
  int k                                = LARGE_NEGATIVE_INT; 
  int l                                = LARGE_NEGATIVE_INT; 
  int node                             = LARGE_NEGATIVE_INT; 
  int nn_ik                            = LARGE_NEGATIVE_INT; 
  int n_offnode_neighbours             = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int *x_NN                            = NULL;
  int *x_nn_index                      = NULL;
  int num_ints                         = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);
/*                                                                           */
/*                                                                           */
/*                                                                           */
  nparticles = node_info[rank].nparticles;

  tag62  = 62*(MAX_TAGS)+rank;
  x_NN = (int *)calloc(NPARTICLES*NN_K,sizeof(int));
  if ( (MPI_Recv(x_NN,NPARTICLES*NN_K,MPI_INT,cluster_size,tag62,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
  {
    printf(" %s(): unable to receive packet \n",fname);
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
  tag63  = 63*(MAX_TAGS)+rank;
  if ( (MPI_Recv(&n_offnode_neighbours,1,MPI_INT,cluster_size,tag63,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
  {
    printf(" %s(): unable to receive packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  } 
  particles_3[0].n_offnode_neighbours = n_offnode_neighbours;
  if (n_offnode_neighbours > 0)
  {
    x_particles = CreateParticles(n_offnode_neighbours,pars);

    tag78  = 78*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&num_ints,1,MPI_INT,cluster_size,tag78,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag79  = 79*(MAX_TAGS)+rank;
    x_nn_index = (int *)calloc(num_ints,sizeof(int));
    if ( (MPI_Recv(x_nn_index,num_ints,MPI_INT,cluster_size,tag79,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 


    tag64  = 64*(MAX_TAGS)+rank;
    X = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(X,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag64,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 

    tag6  = 6*(MAX_TAGS)+rank;
    VX = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(VX,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag6,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag74  = 74*(MAX_TAGS)+rank;
    P = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(P,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag74,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 

    tag75  = 75*(MAX_TAGS)+rank;
    RHO = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(RHO,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag75,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag76  = 76*(MAX_TAGS)+rank;
    H = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(H,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag76,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag82  = 82*(MAX_TAGS)+rank;
    divV = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(divV,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag82,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag82 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag84  = 84*(MAX_TAGS)+rank;
    U = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if ( (MPI_Recv(U,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag84,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag82 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    if (DIMENSIONS == 3)
    {
      tag65  = 65*(MAX_TAGS)+rank;
      Y = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(Y,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag65,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      } 
      tag7  = 7*(MAX_TAGS)+rank;
      VY = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(VY,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag7,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      } 
    }
    if ( (DIMENSIONS == 2) || (DIMENSIONS == 3) )
    {
      tag66  = 66*(MAX_TAGS)+rank;
      Z = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(Z,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag66,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      } 
      tag8  = 8*(MAX_TAGS)+rank;
      VZ = (double *)calloc(n_offnode_neighbours,sizeof(double));
      if ( (MPI_Recv(VZ,n_offnode_neighbours,MPI_DOUBLE,cluster_size,tag8,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive packet \n",fname);
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
      x_particles[0].v[0][i]  = VX[i];
      x_particles[0].p[i]     = P[i];
      x_particles[0].rho[i]   = RHO[i];
      x_particles[0].h[i]     = H[i];
      x_particles[0].divV[i]  = divV[i];
      x_particles[0].U[i]     = U[i];
      if (DIMENSIONS == 2)
      {
        x_particles[0].x[2][i] = Z[i];
        x_particles[0].v[2][i] = VZ[i];
      }
      if (DIMENSIONS == 3)
      {
        x_particles[0].x[1][i] = Y[i];
        x_particles[0].x[2][i] = Z[i];
        x_particles[0].v[1][i] = VY[i];
        x_particles[0].v[2][i] = VZ[i];
      }
    }
    free(X);               X = NULL;
    free(VX);             VX = NULL;
    free(P);               P = NULL;
    free(RHO);           RHO = NULL;
    free(H);               H = NULL;
    free(divV);         divV = NULL;
    free(U);               U = NULL;
    if ((DIMENSIONS ==2) || (DIMENSIONS == 3) )
    {
      free(Z);   Z = NULL;
      free(VZ); VZ = NULL;
    }
    if (DIMENSIONS ==3) 
    {
      free(Y);   Y = NULL;
      free(VY); VY = NULL;
    }
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return x_particles;
}
