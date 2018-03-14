#include "set_burn_mark.h"

int SetBurnMark(PARTICLES *particles,PARS *pars)
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  char   fname[]                       = "...SetBurnMark";

  double x1                            = 0.0;
  double start_burn_l                  = 0.0;
  double start_burn_r                  = 0.0;
  double burn_delta_l                  = 0.0;
  double burn_delta_r                  = 0.0;
  double z1                            = 0.0;
  double h                             = 0.0;
  double x_r                           = 0.0;
  double x_l                           = 0.0;
  double z_0                           = 0.0;
  double d_l                           = 0.0;
  double d_r                           = 0.0;
  double min_r                         = 0.0;
  double max_l                         = 0.0;

  int l                                = 0;
  int exit_status                      = EXIT_FAILURE;
  int i_rank                           = 0;
  int tag10                            = 0;
  int tag11                            = 0;
  int i                                = 0;
  int nparticles                       = 0;
  int n_contains_burn_l                = 0;
  int n_contains_burn_r                = 0;

  MPI_Status mpi_status;

#include "pars_include.h"
  verbosity(1,fname,pars);

  nparticles        = node_info[rank].nparticles;
  start_burn_l      = node_info[rank].start_burn_l;
  start_burn_r      = node_info[rank].start_burn_r;
  burn_delta_l      = node_info[rank].burn_delta_l;
  burn_delta_r      = node_info[rank].burn_delta_r;
  n_contains_burn_l = node_info[rank].n_contains_burn_l;
  n_contains_burn_r = node_info[rank].n_contains_burn_r;

  x_r = node_info[rank].burn_r;
  x_l = node_info[rank].burn_l;
  for (i=0;i<H_PTS;i++)
  {
    z_0 = node_info[rank].h_pts[i];
    min_r = LARGE_POSITIVE_DOUBLE; 
    max_l = LARGE_NEGATIVE_DOUBLE;
    for (l=0;l<nparticles;l++)
    {
      x1  = particles[0].x[0][l];
      z1  = particles[0].x[2][l];
      h   = particles[0].h[l];
      d_l = sqrt((x_l-x1)*(x_l-x1) + (z_0-z1)*(z_0-z1));
      d_r = sqrt((x_r-x1)*(x_r-x1) + (z_0-z1)*(z_0-z1));
      if (d_l < KERNEL_WIDTH*h)
      {
        if (max_l <= x1+KERNEL_WIDTH*h)
        {
          node_info[rank].contains_burn_l[i] = l;
          max_l = x1+KERNEL_WIDTH*h;
        }
      }
      if (d_r < KERNEL_WIDTH*h)
      {
        if (min_r >= x1-KERNEL_WIDTH*h)
        {
          node_info[rank].contains_burn_r[i] = l;
          min_r = x1-KERNEL_WIDTH*h;
        }
      }
    }
  }
  node_info[rank].burn_r = min_r;
  node_info[rank].burn_l = max_l;


  exit_status = EXIT_SUCCESS;
  if (rank > 0)
  {
    if ( (node_info[rank].burn_l > start_burn_l + burn_delta_l/2.0) )
    {
      exit_status = BURN_TRIGGER_LEFT;
      printf(" rank: %i left exceeded \n",rank);
    }
  }

  if (rank < cluster_size)
  {
    if (node_info[rank].burn_r < start_burn_r - burn_delta_r/2.0) 
    {
      if (exit_status == BURN_TRIGGER_LEFT)
      {
        exit_status = BURN_TRIGGER_LEFT_AND_RIGHT;
      }
      else
      {
        exit_status = BURN_TRIGGER_RIGHT;
      }
      printf(" rank: %i right exceeded \n",rank);
    }
  }

  node_info[rank].burn_status = exit_status;
/*                                                                           */
/*                 burn_status                                                */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag10  = 10*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_status,1,MPI_INT,i_rank,tag10,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SetBurnMark(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag10 = 10*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_status,1,MPI_INT,i_rank,tag10,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SetBurnMark(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag10  = 10*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_status,1,MPI_INT,i_rank,tag10,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SetBurnMark(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }

  if (rank > 0)
  {
    if (
         (node_info[rank-1].burn_status == BURN_TRIGGER_RIGHT)
                                    ||
         (node_info[rank-1].burn_status == BURN_TRIGGER_LEFT_AND_RIGHT)
       )
    {
      node_info[rank].burn_status = BURN_TRIGGER_LEFT;
    }
  }
/*                                                                           */
/*                 burn_status                                                */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag11  = 11*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_status,1,MPI_INT,i_rank,tag11,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SetBurnMark(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag11 = 11*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_status,1,MPI_INT,i_rank,tag11,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SetBurnMark(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag11  = 11*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_status,1,MPI_INT,i_rank,tag11,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SetBurnMark(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  exit_status = node_info[rank].burn_status;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
