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

#include "set_n.h"

int Set_N(PARS *pars)
{
  extern int cluster_size;

  FILE *out_ptr                        = NULL;

  MPI_Status mpi_status;

  char   fname[]                       = "...Set_N";

  double **all_points                  = NULL;
  double **v_all_points                = NULL;
  double *p_all_points                 = NULL;
  double *rho_all_points               = NULL;
  double *h_all_points                 = NULL;
  double *u_all_points                 = NULL;
  double *divv_all_points              = NULL;
  double *X                            = NULL;
  double *Y                            = NULL;
  double *Z                            = NULL;
  double *species                      = NULL;
  double *P                            = NULL;
  double *RHO                          = NULL;
  double *divV                         = NULL;
  double *U                            = NULL;
  double *H                            = NULL;
  double *VX                           = NULL;
  double *VY                           = NULL;
  double *VZ                           = NULL;

  int num_ints                         = LARGE_NEGATIVE_INT;
  int num                              = LARGE_NEGATIVE_INT;
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
  int tag13                            = LARGE_NEGATIVE_INT;
  int tag14                            = LARGE_NEGATIVE_INT;
  int tag15                            = LARGE_NEGATIVE_INT;
  int tag16                            = LARGE_NEGATIVE_INT;
  int tag17                            = LARGE_NEGATIVE_INT;
  int tag18                            = LARGE_NEGATIVE_INT;
  int tag19                            = LARGE_NEGATIVE_INT;
  int tag20                            = LARGE_NEGATIVE_INT;
  int tag21                            = LARGE_NEGATIVE_INT;
  int tag22                            = LARGE_NEGATIVE_INT;
  int tag23                            = LARGE_NEGATIVE_INT;
  int tag24                            = LARGE_NEGATIVE_INT;
  int tag25                            = LARGE_NEGATIVE_INT;
  int tag26                            = LARGE_NEGATIVE_INT;
  int tag27                            = LARGE_NEGATIVE_INT;
  int tag28                            = LARGE_NEGATIVE_INT;
  int tag29                            = LARGE_NEGATIVE_INT;
  int tag30                            = LARGE_NEGATIVE_INT;
  int tag31                            = LARGE_NEGATIVE_INT;
  int tag32                            = LARGE_NEGATIVE_INT;
  int tag33                            = LARGE_NEGATIVE_INT;
  int tag34                            = LARGE_NEGATIVE_INT;
  int tag35                            = LARGE_NEGATIVE_INT;
  int tag36                            = LARGE_NEGATIVE_INT;
  int tag37                            = LARGE_NEGATIVE_INT;
  int tag38                            = LARGE_NEGATIVE_INT;
  int tag39                            = LARGE_NEGATIVE_INT;
  int tag40                            = LARGE_NEGATIVE_INT;
  int tag41                            = LARGE_NEGATIVE_INT;
  int tag42                            = LARGE_NEGATIVE_INT;
  int i_rank                           = LARGE_NEGATIVE_INT;
  int i                                = LARGE_NEGATIVE_INT;
  int j                                = LARGE_NEGATIVE_INT;
  int k                                = LARGE_NEGATIVE_INT;
  int l                                = LARGE_NEGATIVE_INT;
  int n                                = LARGE_NEGATIVE_INT;
  int node                             = LARGE_NEGATIVE_INT;
  int i_start                          = LARGE_NEGATIVE_INT;
  int i_end                            = LARGE_NEGATIVE_INT;
  int offset                           = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int n_offnode_neighbours             = LARGE_NEGATIVE_INT; 
  int exit_status                      = EXIT_FAILURE;
  int **NN                             = NULL;
  int *x_nn_index                      = NULL;
  int *x_NN                            = NULL;
  int nn_ik                            = LARGE_NEGATIVE_INT;
  int action                           = LARGE_NEGATIVE_INT;
  int *n_off                           = NULL;
  
  logical add                          = FALSE;

  NN_INDEX *nn_index                   = NULL;

#include "pars_include.h"
  verbosity(1,fname,pars);
  tag1  = 1*(MAX_TAGS)+0;
  if ( (MPI_Recv(&action,1,MPI_INT,0,tag1,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
  {
    printf(" %s(): unable to receive tag1 packet \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
/*                                                                           */
/*                 action = LARGE_POSITIVE_INT  means no need to call this   */
/*                 routine, processing has completed.                        */
/*                                                                           */
  if (action == LARGE_POSITIVE_INT)
  {
    exit_status = action;
    goto RETURN;
  }

  nparticles = NPARTICLES;
  n_off      = (int *)calloc(cluster_size,sizeof(int));
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    n_off[i_rank] = LARGE_NEGATIVE_INT;
  }
/* ######################################################################### */
/*                                                                           */
/*            BLOCK 1: PUSH_AND_PULL_N_AND_X :  START                        */
/*                                                                           */
  all_points = (double **)calloc(TOTAL_PARTICLES,sizeof(double *));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    all_points[i] = (double *)calloc(DIMENSIONS,sizeof(double));
    if (DIMENSIONS == 1)
    {
      all_points[i][0] = LARGE_NEGATIVE_DOUBLE;
    }
    if (DIMENSIONS == 2)
    {
      all_points[i][0] = LARGE_NEGATIVE_DOUBLE;
      all_points[i][1] = LARGE_NEGATIVE_DOUBLE;
    }
    if (DIMENSIONS == 3)
    {
      all_points[i][0] = LARGE_NEGATIVE_DOUBLE;
      all_points[i][1] = LARGE_NEGATIVE_DOUBLE;
      all_points[i][2] = LARGE_NEGATIVE_DOUBLE;
    }
  }
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    tag2  = 2*(MAX_TAGS)+ i_rank;
    X = (double *)calloc(nparticles,sizeof(double));
    if ( (MPI_Recv(X,nparticles,MPI_DOUBLE,i_rank,tag2,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag2 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = (double *)calloc(nparticles,sizeof(double));
    printf(" here 100 \n");
    if ( (MPI_Recv(species,nparticles,MPI_DOUBLE,i_rank,tag36,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag36 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }

    for (i=0;i<nparticles;i++)
    {
      j = i_rank*nparticles + i;
      if (species[i] != MASK_VOID)
      {
        all_points[j][0]= X[i];
      }
    }
    Free_sph(X);
    if (DIMENSIONS == 2)
    {
      tag3  = 3*(MAX_TAGS)+ i_rank;
      Z = (double *)calloc(nparticles,sizeof(double));
      if ( (MPI_Recv(Z,nparticles,MPI_DOUBLE,i_rank,tag3,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag3 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      for (i=0;i<nparticles;i++)
      {
        j = i_rank*nparticles + i;
        if (species[i] != MASK_VOID)
        {
          all_points[j][1]= Z[i];
        }
      }
      Free_sph(Z);
    }
    if (DIMENSIONS == 3)
    {
      tag4  = 4*(MAX_TAGS)+ i_rank;
      Y = (double *)calloc(nparticles,sizeof(double));
      if ( (MPI_Recv(Y,nparticles,MPI_DOUBLE,i_rank,tag4,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag4 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      tag5  = 5*(MAX_TAGS)+ i_rank;
      Z = (double *)calloc(nparticles,sizeof(double));
      if ( (MPI_Recv(Z,nparticles,MPI_DOUBLE,i_rank,tag5,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag5 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      for (i=0;i<nparticles;i++)
      {
        j = i_rank*nparticles + i;
        if (species[i] != MASK_VOID)
        {
          all_points[j][1] = Y[i];
          all_points[j][2] = Z[i];
        }
      }
      Free_sph(Y);
      Free_sph(Z);
    }
    Free_sph(species);
  }
/*                                                                           */
/*                 calculate all neighbours                                  */
/*                                                                           */
  NN = (int **)calloc(TOTAL_PARTICLES,sizeof(int *));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    NN[i] = (int *)calloc(NN_K,sizeof(int));
    for (k=0;k<NN_K;k++)
    {
      NN[i][k] = LARGE_NEGATIVE_INT;
    }
  }
  if ((UpdateRij(NN,all_points,pars)) == EXIT_FAILURE)
  {
    printf(" %s(): Error return from UpdateRij \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    n_offnode_neighbours = 0;
    num_ints             = NPARTICLES;
    X        = (double *)calloc(1,sizeof(double));
    Y        = (double *)calloc(1,sizeof(double));
    Z        = (double *)calloc(1,sizeof(double));
    nn_index = (NN_INDEX *)calloc(NPARTICLES,sizeof(NN_INDEX));
    for (i=0;i<NPARTICLES;i++)
    {
      nn_index[i].node                    = (int *)calloc(1,sizeof(int));
      nn_index[i].n_offnode_neighbours    = (int *)calloc(1,sizeof(int));
      nn_index[i].num                     = 0;
      nn_index[i].node[0]                 = LARGE_NEGATIVE_INT;
      nn_index[i].n_offnode_neighbours[0] = LARGE_NEGATIVE_INT;
    }
    x_NN = (int *)calloc(NPARTICLES*NN_K,sizeof(int));
    i_start = (i_rank+0)*NPARTICLES;
    i_end   = (i_rank+1)*NPARTICLES;
    l       = 0;
    for (i=i_start;i<i_end;i++)
    {
      if (i < TOTAL_PARTICLES)
      {
      for (k=0;k<NN_K;k++)
      {
        nn_ik = NN[i][k];
        node  = nn_ik/NPARTICLES;
        j     = nn_ik%NPARTICLES;
        x_NN[l] = nn_ik;
        l++;
        if (node != i_rank)
        {
          add = TRUE;
/*                                                                           */
/*                 accomodates different off nodes, but for the same j index */
/*                                                                           */
          num = nn_index[j].num;
          if (num > 0)
          {
            for (n=0;n<num;n++)
            {
              if (nn_index[j].node[n] == node)
              {
                add = FALSE;
                break;
              }
            }
          }
          if (add)
          {
            n_offnode_neighbours++;
            num                                   = nn_index[j].num + 1;
            nn_index[j].num                       = num;
            if (num > 1)
            {
              nn_index[j].node                    = (int *)realloc(nn_index[j].node,num*sizeof(int));
              nn_index[j].n_offnode_neighbours    = (int *)realloc(nn_index[j].n_offnode_neighbours,num*sizeof(int));
            }
            nn_index[j].node[num-1]               = node;
            num_ints++;
            nn_index[j].n_offnode_neighbours[num-1] = n_offnode_neighbours-1;
            num_ints++;
            if (n_offnode_neighbours > 1)
            {
              X = (double *)realloc(X,(n_offnode_neighbours)*sizeof(double));
            }
            X[n_offnode_neighbours-1] = all_points[nn_ik][0];

            if (DIMENSIONS == 2)
            {
              if (n_offnode_neighbours > 1)
              {
                Z  = (double *)realloc(Z,(n_offnode_neighbours)*sizeof(double));
              }
              Z[n_offnode_neighbours-1]  = all_points[nn_ik][1];
            }
            if (DIMENSIONS == 3)
            {
              if (n_offnode_neighbours > 1)
              {
                Y = (double *)realloc(Y,(n_offnode_neighbours)*sizeof(double));
                Z = (double *)realloc(Z,(n_offnode_neighbours)*sizeof(double));
              }
              Y[n_offnode_neighbours-1] = all_points[nn_ik][1];
              Z[n_offnode_neighbours-1] = all_points[nn_ik][2];
            }
          }
        }
      }
      }
    }
    n_off[i_rank] = n_offnode_neighbours;
    tag6  = 6*(MAX_TAGS)+i_rank;
    if ( (MPI_Send(x_NN,NPARTICLES*NN_K,MPI_INT,i_rank,tag6,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag6 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    Free_sph(x_NN);

    tag7  = 7*(MAX_TAGS)+i_rank;
    if ( (MPI_Send(&n_offnode_neighbours,1,MPI_INT,i_rank,tag7,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send tag7 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if (n_offnode_neighbours > 0)
    {
      x_nn_index = (int *)calloc(num_ints,sizeof(int));
      l = 0;
      for (i=0;i<NPARTICLES;i++)
      {
        num =  nn_index[i].num;
        x_nn_index[l] = num;
        l++;
        if (num > 0)
        {
          for (j=0;j<num;j++)
          {
            x_nn_index[l] = nn_index[i].node[j];
            l++;
            x_nn_index[l] = nn_index[i].n_offnode_neighbours[j];
            l++;
          }
        }
      }
      tag8  = 8*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&num_ints,1,MPI_INT,i_rank,tag8,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag8 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      tag9  = 9*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(x_nn_index,num_ints,MPI_INT,i_rank,tag9,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag9 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      Free_sph(x_nn_index);

      tag10  = 10*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(X,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag10,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag10 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if (DIMENSIONS == 3)
      {
        tag11  = 11*(MAX_TAGS)+i_rank;
        if ( (MPI_Send(Y,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag11,MPI_COMM_WORLD)) != MPI_SUCCESS)
        {
          printf(" %s(): unable to send tag11 packet \n",fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
      }
      if ( (DIMENSIONS == 2) || (DIMENSIONS == 3) )
      {
        tag12  = 12*(MAX_TAGS)+i_rank;
        if ( (MPI_Send(Z,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag12,MPI_COMM_WORLD)) != MPI_SUCCESS)
        {
          printf(" %s(): unable to send tag12 packet \n",fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
      }
    }
    Free_sph(X);
    Free_sph(Y);
    Free_sph(Z);
    if (nn_index)
    {
      for (i=0;i<NPARTICLES;i++)
      {
        Free_sph(nn_index[i].node);
        Free_sph(nn_index[i].n_offnode_neighbours);
      }
      Free_sph(nn_index);
    }
  }
  if (all_points)
  {
    for (i=0;i<TOTAL_PARTICLES;i++)
    {
      free(all_points[i]); all_points[i] = NULL;
    }
    free(all_points); all_points = NULL;
  }
/*                                                                           */
/*                               BLOCK 1: END                                */
/*                                                                           */
/* ######################################################################### */


/* ######################################################################### */
/*                                                                           */
/*            BLOCK 2: PUSH_AND_PULL_V :  START                              */
/*                                                                           */
  v_all_points = (double **)calloc(TOTAL_PARTICLES,sizeof(double *));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    v_all_points[i] = (double *)calloc(DIMENSIONS,sizeof(double));
    if (DIMENSIONS == 1)
    {
      v_all_points[i][0] = LARGE_NEGATIVE_DOUBLE;
    }
    if (DIMENSIONS == 2)
    {
      v_all_points[i][0] = LARGE_NEGATIVE_DOUBLE;
      v_all_points[i][1] = LARGE_NEGATIVE_DOUBLE;
    }
    if (DIMENSIONS == 3)
    {
      v_all_points[i][0] = LARGE_NEGATIVE_DOUBLE;
      v_all_points[i][1] = LARGE_NEGATIVE_DOUBLE;
      v_all_points[i][2] = LARGE_NEGATIVE_DOUBLE;
    }
  }
/*                                                                           */
/*                 receive X coord velocity from the compute nodes           */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    tag13  = 13*(MAX_TAGS)+ i_rank;
    VX = (double *)calloc(nparticles,sizeof(double));
    if ( (MPI_Recv(VX,nparticles,MPI_DOUBLE,i_rank,tag13,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag13 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = (double *)calloc(nparticles,sizeof(double));
    printf(" here 101 \n");
    if ( (MPI_Recv(species,nparticles,MPI_DOUBLE,i_rank,tag37,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag37 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    for (i=0;i<nparticles;i++)
    {
      if (species[i] != MASK_VOID)
      {
        j = i_rank*nparticles + i;
        v_all_points[j][0] = VX[i];
      }
    }
    Free_sph(VX);
/*                                                                           */
/*                 receive Y coord information from the compute nodes        */
/*                                                                           */
    if (DIMENSIONS == 3)
    {
      VY = (double *)calloc(nparticles,sizeof(double));
      tag14  = 14*(MAX_TAGS)+ i_rank;
      if ( (MPI_Recv(VY,nparticles,MPI_DOUBLE,i_rank,tag14,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag14n packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      tag15  = 15*(MAX_TAGS)+ i_rank;
      VZ = (double *)calloc(nparticles,sizeof(double));
      if ( (MPI_Recv(VZ,nparticles,MPI_DOUBLE,i_rank,tag15,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag15 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      for (i=0;i<nparticles;i++)
      {
        if (species[i] != MASK_VOID)
        {
          j = i_rank*nparticles + i;
          v_all_points[j][1] = VY[i];
          v_all_points[j][2] = VZ[i];
        }
      }
      Free_sph(VY);
      Free_sph(VZ);
    }
/*                                                                           */
/*                 receive Z coord information from the compute nodes        */
/*                                                                           */
    if (DIMENSIONS == 2)
    {
      tag16  = 16*(MAX_TAGS)+ i_rank;
      VZ = (double *)calloc(nparticles,sizeof(double));
      if ( (MPI_Recv(VZ,nparticles,MPI_DOUBLE,i_rank,tag16,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
      {
        printf(" %s(): unable to receive tag16  packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      for (i=0;i<nparticles;i++)
      {
        if (species[i] != MASK_VOID)
        {
          j = i_rank*nparticles + i;
          v_all_points[j][1] = VZ[i];
        }
      }
      Free_sph(VZ);
    }
    Free_sph(species);
  }
/*                                                                           */
/*                 now disperse among the ranks                              */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    nn_index = (NN_INDEX *)calloc(NPARTICLES,sizeof(NN_INDEX));
    for (i=0;i<NPARTICLES;i++)
    {
      nn_index[i].node                    = (int *)calloc(1,sizeof(int));
      nn_index[i].n_offnode_neighbours    = (int *)calloc(1,sizeof(int));
      nn_index[i].num                     = 0;
      nn_index[i].node[0]                 = LARGE_NEGATIVE_INT;
      nn_index[i].n_offnode_neighbours[0] = LARGE_NEGATIVE_INT;
    }
    l = 0;
    n_offnode_neighbours = n_off[i_rank];
    VX = (double *)calloc(n_offnode_neighbours,sizeof(double));
    if (DIMENSIONS == 2)
    {
      VZ = (double *)calloc(n_offnode_neighbours,sizeof(double));
    }
    if (DIMENSIONS == 3)
    {
      VY = (double *)calloc(n_offnode_neighbours,sizeof(double));
      VZ = (double *)calloc(n_offnode_neighbours,sizeof(double));
    }
    
    i_start = (i_rank+0)*NPARTICLES;
    i_end   = (i_rank+1)*NPARTICLES;
    for (i=i_start;i<i_end;i++)
    {
      if (i < TOTAL_PARTICLES)
      {
      for (k=0;k<NN_K;k++)
      {
        nn_ik = NN[i][k];
        node  = nn_ik/NPARTICLES;
        j     = nn_ik%NPARTICLES;
        if (node != i_rank)
        {
          add = TRUE;
/*                                                                           */
/*                 accomodates different off nodes, but for the same j index */
/*                                                                           */
          num = nn_index[j].num;
          if (num > 0)
          {
            for (n=0;n<num;n++)
            {
              if (nn_index[j].node[n] == node)
              {
                add = FALSE;
                break;
              }
            }
          }
          if (add)
          {
            l++;
            num                                   = nn_index[j].num + 1;
            nn_index[j].num                       = num;
            if (num > 1)
            {
              nn_index[j].node                    = (int *)realloc(nn_index[j].node,num*sizeof(int));
              nn_index[j].n_offnode_neighbours    = (int *)realloc(nn_index[j].n_offnode_neighbours,num*sizeof(int));
            }
            nn_index[j].node[num-1]               = node;
            nn_index[j].n_offnode_neighbours[num-1] = l-1;
            VX[l-1] = v_all_points[nn_ik][0]; 
            if (DIMENSIONS == 2)
            {
              VZ[l-1] = v_all_points[nn_ik][1]; 
            }
            if (DIMENSIONS == 3)
            {
              VY[l-1] = v_all_points[nn_ik][1];
              VZ[l-1] = v_all_points[nn_ik][2];
            }
          }
        }
      }
      }
    }

    if (n_offnode_neighbours > 0)
    {
      tag18  = 18*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(VX,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag18,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag18 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if (DIMENSIONS == 3)
      {
        tag19  = 19*(MAX_TAGS)+i_rank;
        if ( (MPI_Send(VY,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag19,MPI_COMM_WORLD)) != MPI_SUCCESS)
        {
          printf(" %s(): unable to send tag19 packet \n",fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
      }
      if ( (DIMENSIONS == 2) || (DIMENSIONS == 3) )
      {
        tag20  = 20*(MAX_TAGS)+i_rank;
        if ((MPI_Send(VZ,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag20,MPI_COMM_WORLD)) != MPI_SUCCESS)
        {
          printf(" %s(): unable to send tag20 packet \n",fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
      }
    }
    Free_sph(VX);
    if (DIMENSIONS == 2)
    {
      Free_sph(VZ);
    }
    if (DIMENSIONS == 3)
    {
      Free_sph(VZ);
      Free_sph(VY);
    }
    if (nn_index)
    {
      for (i=0;i<NPARTICLES;i++)
      {
        Free_sph(nn_index[i].node);
        Free_sph(nn_index[i].n_offnode_neighbours);
      }
      Free_sph(nn_index);
    }
  }
  if (v_all_points)
  {
    for (i=0;i<TOTAL_PARTICLES;i++)
    {
      free(v_all_points[i]); v_all_points[i] = NULL;
    }
    free(v_all_points); v_all_points = NULL;
  }
/*                                                                           */
/*                               BLOCK 2: END                                */
/*                                                                           */
/* ######################################################################### */

/* ######################################################################### */
/*                                                                           */
/*            BLOCK 3: PUSH_AND_PULL_U :  START                              */
/*                                                                           */
  u_all_points = (double *)calloc(TOTAL_PARTICLES,sizeof(double));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    u_all_points[i] = LARGE_NEGATIVE_DOUBLE;
  }
/*                                                                           */
/*                 receive X coord information from the compute nodes        */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    tag21 = 21*(MAX_TAGS)+ i_rank;
    U = (double *)calloc(nparticles,sizeof(double));
    if ( (MPI_Recv(U,nparticles,MPI_DOUBLE,i_rank,tag21,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag21 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = (double *)calloc(nparticles,sizeof(double));
    printf(" here 102 \n");
    if ( (MPI_Recv(species,nparticles,MPI_DOUBLE,i_rank,tag38,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag38 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    for (i=0;i<nparticles;i++)
    {
      if (species[i] != MASK_VOID)
      {
        j = i_rank*nparticles + i;
        u_all_points[j] = U[i];
      }
    }
    Free_sph(U);
    Free_sph(species);
  }
/*                                                                           */
/*                 now disperse among the ranks                              */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    l       = 0;
    nn_index = (NN_INDEX *)calloc(NPARTICLES,sizeof(NN_INDEX));
    for (i=0;i<NPARTICLES;i++)
    {
      nn_index[i].node                    = (int *)calloc(1,sizeof(int));
      nn_index[i].n_offnode_neighbours    = (int *)calloc(1,sizeof(int));
      nn_index[i].num                     = 0;
      nn_index[i].node[0]                 = LARGE_NEGATIVE_INT;
      nn_index[i].n_offnode_neighbours[0] = LARGE_NEGATIVE_INT;
    }
    n_offnode_neighbours = n_off[i_rank];
    U = (double *)calloc(n_offnode_neighbours,sizeof(double));
    i_start = (i_rank+0)*NPARTICLES;
    i_end   = (i_rank+1)*NPARTICLES;
    for (i=i_start;i<i_end;i++)
    {
      if (i < TOTAL_PARTICLES)
      {
      for (k=0;k<NN_K;k++)
      {
        nn_ik = NN[i][k];
        node  = nn_ik/NPARTICLES;
        j     = nn_ik%NPARTICLES;
        if (node != i_rank)
        {
          add = TRUE;
/*                                                                           */
/*                 accomodates different off nodes, but for the same j index */
/*                                                                           */
          num = nn_index[j].num;
          if (num > 0)
          {
            for (n=0;n<num;n++)
            {
              if (nn_index[j].node[n] == node)
              {
                add = FALSE;
                break;
              }
            }
          }
          if (add)
          {
            l++;
            num                                   = nn_index[j].num + 1;
            nn_index[j].num                       = num;
            if (num > 1)
            {
              nn_index[j].node                    = (int *)realloc(nn_index[j].node,num*sizeof(int));
              nn_index[j].n_offnode_neighbours    = (int *)realloc(nn_index[j].n_offnode_neighbours,num*sizeof(int));
            }
            nn_index[j].node[num-1]               = node;
            nn_index[j].n_offnode_neighbours[num-1] = l-1;
            U[l-1] = u_all_points[nn_ik]; 
          }
        }
      }
      }
    }

    if (n_offnode_neighbours > 0)
    {
      tag23  = 23*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(U,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag23,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag23 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    Free_sph(U);
    if (nn_index)
    {
      for (i=0;i<NPARTICLES;i++)
      {
        Free_sph(nn_index[i].node);
        Free_sph(nn_index[i].n_offnode_neighbours);
      }
      Free_sph(nn_index);
    }
  }
  if (u_all_points)
  {
    free(u_all_points); u_all_points = NULL;
  }
/*                                                                           */
/*                               BLOCK 3: END                                */
/*                                                                           */
/* ######################################################################### */

/* ######################################################################### */
/*                                                                           */
/*            BLOCK 4: PUSH_AND_PULL_H :  START                              */
/*                                                                           */
  h_all_points = (double *)calloc(TOTAL_PARTICLES,sizeof(double));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    h_all_points[i] = LARGE_NEGATIVE_DOUBLE;
  }
/*                                                                           */
/*                 receive X coord information from the compute nodes        */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    tag24  = 24*(MAX_TAGS)+ i_rank;
    H = (double *)calloc(nparticles,sizeof(double));
    if ( (MPI_Recv(H,nparticles,MPI_DOUBLE,i_rank,tag24,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag24 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = (double *)calloc(nparticles,sizeof(double));
    printf(" here 103 \n");
    if ( (MPI_Recv(species,nparticles,MPI_DOUBLE,i_rank,tag39,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag39 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    for (i=0;i<nparticles;i++)
    {
      if (species[i] != MASK_VOID)
      {
        j = i_rank*nparticles + i;
        h_all_points[j] = H[i];
      }
    }
    Free_sph(H);
    Free_sph(species);
  }
/*                                                                           */
/*                 now disperse among the ranks                              */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    l       = 0;
    nn_index = (NN_INDEX *)calloc(NPARTICLES,sizeof(NN_INDEX));
    for (i=0;i<NPARTICLES;i++)
    {
      nn_index[i].node                    = (int *)calloc(1,sizeof(int));
      nn_index[i].n_offnode_neighbours    = (int *)calloc(1,sizeof(int));
      nn_index[i].num                     = 0;
      nn_index[i].node[0]                 = LARGE_NEGATIVE_INT;
      nn_index[i].n_offnode_neighbours[0] = LARGE_NEGATIVE_INT;
    }
    n_offnode_neighbours = n_off[i_rank];
    H = (double *)calloc(n_offnode_neighbours,sizeof(double));
    i_start = (i_rank+0)*NPARTICLES;
    i_end   = (i_rank+1)*NPARTICLES;
    l       = 0;
    for (i=i_start;i<i_end;i++)
    {
      if (i < TOTAL_PARTICLES)
      {
      for (k=0;k<NN_K;k++)
      {
        nn_ik = NN[i][k];
        node  = nn_ik/NPARTICLES;
        j     = nn_ik%NPARTICLES;
        if (node != i_rank)
        {
          add = TRUE;
/*                                                                           */
/*                 accomodates different off nodes, but for the same j index */
/*                                                                           */
          num = nn_index[j].num;
          if (num > 0)
          {
            for (n=0;n<num;n++)
            {
              if (nn_index[j].node[n] == node)
              {
                add = FALSE;
                break;
              }
            }
          }
          if (add)
          {
            l++;
            num                                   = nn_index[j].num + 1;
            nn_index[j].num                       = num;
            if (num > 1)
            {
              nn_index[j].node                    = (int *)realloc(nn_index[j].node,num*sizeof(int));
              nn_index[j].n_offnode_neighbours    = (int *)realloc(nn_index[j].n_offnode_neighbours,num*sizeof(int));
            }
            nn_index[j].node[num-1]               = node;
            nn_index[j].n_offnode_neighbours[num-1] = l-1;
            H[l-1] = h_all_points[nn_ik]; 
          }
        }
      }
      }
    }

    if (n_offnode_neighbours > 0)
    {
      tag26  = 26*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(H,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag26,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag26 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    Free_sph(H);
    if (nn_index)
    {
      for (i=0;i<NPARTICLES;i++)
      {
        Free_sph(nn_index[i].node);
        Free_sph(nn_index[i].n_offnode_neighbours);
      }
      Free_sph(nn_index);
    }
  }
  if (h_all_points)
  {
    free(h_all_points); h_all_points = NULL;
  }
/*                                                                           */
/*                               BLOCK 4: END                                */
/*                                                                           */
/* ######################################################################### */

/* ######################################################################### */
/*                                                                           */
/*            BLOCK 5: PUSH_AND_PULL_RHO :  START                            */
/*                                                                           */

  rho_all_points = (double *)calloc(TOTAL_PARTICLES,sizeof(double));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    rho_all_points[i] = LARGE_NEGATIVE_DOUBLE;
  }
/*                                                                           */
/*                 receive X coord information from the compute nodes        */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    tag27  = 27*(MAX_TAGS)+ i_rank;
    RHO = (double *)calloc(nparticles,sizeof(double));
    if ( (MPI_Recv(RHO,nparticles,MPI_DOUBLE,i_rank,tag27,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag27 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = (double *)calloc(nparticles,sizeof(double));
    printf(" here 104 \n");
    if ( (MPI_Recv(species,nparticles,MPI_DOUBLE,i_rank,tag40,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag40 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    for (i=0;i<nparticles;i++)
    {
      if (species[i] != MASK_VOID)
      {
        j = i_rank*nparticles + i;
        rho_all_points[j] = RHO[i];
      }
    }
    Free_sph(RHO);
    Free_sph(species);
  }
/*                                                                           */
/*                 now disperse among the ranks                              */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    l       = 0;
    nn_index = (NN_INDEX *)calloc(NPARTICLES,sizeof(NN_INDEX));
    for (i=0;i<NPARTICLES;i++)
    {
      nn_index[i].node                    = (int *)calloc(1,sizeof(int));
      nn_index[i].n_offnode_neighbours    = (int *)calloc(1,sizeof(int));
      nn_index[i].num                     = 0;
      nn_index[i].node[0]                 = LARGE_NEGATIVE_INT;
      nn_index[i].n_offnode_neighbours[0] = LARGE_NEGATIVE_INT;
    }
    n_offnode_neighbours = n_off[i_rank];
    RHO  = (double *)calloc(n_offnode_neighbours,sizeof(double));
    i_start = (i_rank+0)*NPARTICLES;
    i_end   = (i_rank+1)*NPARTICLES;
    l       = 0;
    for (i=i_start;i<i_end;i++)
    {
      if (i < TOTAL_PARTICLES)
      {
      for (k=0;k<NN_K;k++)
      {
        nn_ik = NN[i][k];
        node  = nn_ik/NPARTICLES;
        j     = nn_ik%NPARTICLES;
        if (node != i_rank)
        {
          add = TRUE;
/*                                                                           */
/*                 accomodates different off nodes, but for the same j index */
/*                                                                           */
          num = nn_index[j].num;
          if (num > 0)
          {
            for (n=0;n<num;n++)
            {
              if (nn_index[j].node[n] == node)
              {
                add = FALSE;
                break;
              }
            }
          }
          if (add)
          {
            l++;
            num                                   = nn_index[j].num + 1;
            nn_index[j].num                       = num;
            if (num > 1)
            {
              nn_index[j].node                    = (int *)realloc(nn_index[j].node,num*sizeof(int));
              nn_index[j].n_offnode_neighbours    = (int *)realloc(nn_index[j].n_offnode_neighbours,num*sizeof(int));
            }
            nn_index[j].node[num-1]               = node;
            nn_index[j].n_offnode_neighbours[num-1] = l-1;
            RHO[l-1] = rho_all_points[nn_ik]; 
          }
        }
      }
      }
    }

    if (n_offnode_neighbours > 0)
    {
      tag29  = 29*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(RHO,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag29,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag29 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    Free_sph(RHO);
    if (nn_index)
    {
      for (i=0;i<NPARTICLES;i++)
      {
        Free_sph(nn_index[i].node);
        Free_sph(nn_index[i].n_offnode_neighbours);
      }
      Free_sph(nn_index);
    }
  }
  if (rho_all_points)
  {
    free(rho_all_points); rho_all_points = NULL;
  }
/*                                                                           */
/*                               BLOCK 5: END                                */
/*                                                                           */
/* ######################################################################### */

/* ######################################################################### */
/*                                                                           */
/*            BLOCK 6: PUSH_AND_PULL_P :  START                              */
/*                                                                           */
  p_all_points = (double *)calloc(TOTAL_PARTICLES,sizeof(double));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    p_all_points[i] = LARGE_NEGATIVE_DOUBLE;
  }
/*                                                                           */
/*                 receive X coord information from the compute nodes        */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    tag30  = 30*(MAX_TAGS)+ i_rank;
    P = (double *)calloc(nparticles,sizeof(double));
    if ( (MPI_Recv(P,nparticles,MPI_DOUBLE,i_rank,tag30,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag30 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = (double *)calloc(nparticles,sizeof(double));
    printf(" here 105 \n");
    if ( (MPI_Recv(species,nparticles,MPI_DOUBLE,i_rank,tag41,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag41 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    for (i=0;i<nparticles;i++)
    {
      if (species[i] != MASK_VOID)
      {
        j = i_rank*nparticles + i;
        p_all_points[j] = P[i];
      }
    }
    Free_sph(P);
    Free_sph(species);
  }
/*                                                                           */
/*                 now disperse among the ranks                              */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    l       = 0;
    nn_index = (NN_INDEX *)calloc(NPARTICLES,sizeof(NN_INDEX));
    for (i=0;i<NPARTICLES;i++)
    {
      nn_index[i].node                    = (int *)calloc(1,sizeof(int));
      nn_index[i].n_offnode_neighbours    = (int *)calloc(1,sizeof(int));
      nn_index[i].num                     = 0;
      nn_index[i].node[0]                 = LARGE_NEGATIVE_INT;
      nn_index[i].n_offnode_neighbours[0] = LARGE_NEGATIVE_INT;
    }
    n_offnode_neighbours = n_off[i_rank];
    P = (double *)calloc(n_offnode_neighbours,sizeof(double));
    i_start = (i_rank+0)*NPARTICLES;
    i_end   = (i_rank+1)*NPARTICLES;
    l       = 0;
    for (i=i_start;i<i_end;i++)
    {
      if (i < TOTAL_PARTICLES)
      {
      for (k=0;k<NN_K;k++)
      {
        nn_ik = NN[i][k];
        node  = nn_ik/NPARTICLES;
        j     = nn_ik%NPARTICLES;
        if (node != i_rank)
        {
          add = TRUE;
/*                                                                           */
/*                 accomodates different off nodes, but for the same j index */
/*                                                                           */
          num = nn_index[j].num;
          if (num > 0)
          {
            for (n=0;n<num;n++)
            {
              if (nn_index[j].node[n] == node)
              {
                add = FALSE;
                break;
              }
            }
          }
          if (add)
          {
            l++;
            num                                   = nn_index[j].num + 1;
            nn_index[j].num                       = num;
            if (num > 1)
            {
              nn_index[j].node                    = (int *)realloc(nn_index[j].node,num*sizeof(int));
              nn_index[j].n_offnode_neighbours    = (int *)realloc(nn_index[j].n_offnode_neighbours,num*sizeof(int));
            }
            nn_index[j].node[num-1]               = node;
            nn_index[j].n_offnode_neighbours[num-1] = l-1;
            P[l-1] = p_all_points[nn_ik]; 
          }
        }
      }
      }
    }

    if (n_offnode_neighbours > 0)
    {
      tag32  = 32*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(P,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag32,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag32 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    Free_sph(P);
    if (nn_index)
    {
      for (i=0;i<NPARTICLES;i++)
      {
        Free_sph(nn_index[i].node);
        Free_sph(nn_index[i].n_offnode_neighbours);
      }
      Free_sph(nn_index);
    }
  }
  if (p_all_points)
  {
    free(p_all_points); p_all_points = NULL;
  }
/*                                                                           */
/*                               BLOCK 6: END                                */
/*                                                                           */
/* ######################################################################### */

/* ######################################################################### */
/*                                                                           */
/*            BLOCK 7: PUSH_AND_PULL_divV :  START                            */
/*                                                                           */

  divv_all_points = (double *)calloc(TOTAL_PARTICLES,sizeof(double));
  for (i=0;i<TOTAL_PARTICLES;i++)
  {
    divv_all_points[i] = LARGE_NEGATIVE_DOUBLE;
  }
/*                                                                           */
/*                 receive X coord information from the compute nodes        */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    tag33  = 33*(MAX_TAGS)+ i_rank;
    divV = (double *)calloc(nparticles,sizeof(double));
    if ( (MPI_Recv(divV,nparticles,MPI_DOUBLE,i_rank,tag33,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag33 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = (double *)calloc(nparticles,sizeof(double));
    printf(" here 106 \n");
    if ( (MPI_Recv(species,nparticles,MPI_DOUBLE,i_rank,tag42,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive tag42 packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    for (i=0;i<nparticles;i++)
    {
      if (species[i] != MASK_VOID)
      {
        j = i_rank*nparticles + i;
        divv_all_points[j] = divV[i];
      }
    }
    Free_sph(divV);
    Free_sph(species);
  }
/*                                                                           */
/*                 now disperse among the ranks                              */
/*                                                                           */
  for (i_rank=0;i_rank<cluster_size;i_rank++)
  {
    l       = 0;
    nn_index = (NN_INDEX *)calloc(NPARTICLES,sizeof(NN_INDEX));
    for (i=0;i<NPARTICLES;i++)
    {
      nn_index[i].node                    = (int *)calloc(1,sizeof(int));
      nn_index[i].n_offnode_neighbours    = (int *)calloc(1,sizeof(int));
      nn_index[i].num                     = 0;
      nn_index[i].node[0]                 = LARGE_NEGATIVE_INT;
      nn_index[i].n_offnode_neighbours[0] = LARGE_NEGATIVE_INT;
    }
    n_offnode_neighbours = n_off[i_rank];
    divV = (double *)calloc(n_offnode_neighbours,sizeof(double));
    i_start = (i_rank+0)*NPARTICLES;
    i_end   = (i_rank+1)*NPARTICLES;
    l       = 0;
    for (i=i_start;i<i_end;i++)
    {
      if (i < TOTAL_PARTICLES)
      {
      for (k=0;k<NN_K;k++)
      {
        nn_ik = NN[i][k];
        node  = nn_ik/NPARTICLES;
        j     = nn_ik%NPARTICLES;
        if (node != i_rank)
        {
          add = TRUE;
/*                                                                           */
/*                 accomodates different off nodes, but for the same j index */
/*                                                                           */
          num = nn_index[j].num;
          if (num > 0)
          {
            for (n=0;n<num;n++)
            {
              if (nn_index[j].node[n] == node)
              {
                add = FALSE;
                break;
              }
            }
          }
          if (add)
          {
            l++;
            num                                   = nn_index[j].num + 1;
            nn_index[j].num                       = num;
            if (num > 1)
            {
              nn_index[j].node                    = (int *)realloc(nn_index[j].node,num*sizeof(int));
              nn_index[j].n_offnode_neighbours    = (int *)realloc(nn_index[j].n_offnode_neighbours,num*sizeof(int));
            }
            nn_index[j].node[num-1]               = node;
            nn_index[j].n_offnode_neighbours[num-1] = l-1;
            divV[l-1] = divv_all_points[nn_ik]; 
          }
        }
      }
      }
    }

    if (n_offnode_neighbours > 0)
    {
      tag35  = 35*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(divV,n_offnode_neighbours,MPI_DOUBLE,i_rank,tag35,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag35 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    Free_sph(divV);
    if (nn_index)
    {
      for (i=0;i<NPARTICLES;i++)
      {
        Free_sph(nn_index[i].node);
        Free_sph(nn_index[i].n_offnode_neighbours);
      }
      Free_sph(nn_index);
    }
  }
  if (divv_all_points)
  {
    free(divv_all_points); divv_all_points = NULL;
  }
/*                                                                           */
/*                               BLOCK 7: END                                */
/*                                                                           */
/* ######################################################################### */
  exit_status = EXIT_SUCCESS;

RETURN:

  if (NN)
  {
    for (i=0;i<TOTAL_PARTICLES;i++)
    {
       free(NN[i]); NN[i] = NULL;
    }
    free(NN); NN = NULL;
  }
  if (n_off)
  {
    free(n_off); n_off = NULL;
  }

  verbosity(2,fname,pars);
  return exit_status;
}
