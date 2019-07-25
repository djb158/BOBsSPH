#include "synchronize_node_info.h"

int SynchroniseNodeInfo(PARS *pars) 
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  MPI_Status mpi_status;

  char   fname[]                       = "...SynchroniseNodeInfo";

  int exit_status                      = EXIT_FAILURE;
  int i_rank                           = 0;
  int tag1                             = 0;
  int tag2                             = 0;
  int tag3                             = 0;
  int tag4                             = 0;
  int tag5                             = 0;
  int tag6                             = 0;
  int tag7                             = 0;
  int tag8                             = 0;
  int tag9                             = 0;
  int tag10                            = 0;
  int tag11                            = 0;
  int tag12                            = 0;
  int tag13                            = 0;
  int tag14                            = 0;
  int tag15                            = 0;
  int tag16                            = 0;
  int tag17                            = 0;
  int tag18                            = 0;
  int tag19                            = 0;
  int tag20                            = 0;
  int tag21                            = 0;
  int tag22                            = 0;
  int tag23                            = 0;
  int tag24                            = 0;
  int tag25                            = 0;
  int tag26                            = 0;
  int tag27                            = 0;
  int tag28                            = 0;
  int tag29                            = 0;
  int tag30                            = 0;
  int tag31                            = 0;
  int tag32                            = 0;
  int tag33                            = 0;
  int tag34                            = 0;
  int tag35                            = 0;
  int tag36                            = 0;
  int tag37                            = 0;
  int tag38                            = 0;
  int tag39                            = 0;
  int tag40                            = 0;
  int tag41                            = 0;
  int tag42                            = 0;


#include "pars_include.h"
  verbosity(1,fname,pars);

  printf(" here 0 \n");
  if ( (MPI_Barrier(MPI_COMM_WORLD) == MPI_ERR_COMM) )
  {
    printf("%s(): -error return from MPI_Barrier\n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

/*                                                                           */
/*                 nparticles                                                */
/*                                                                           */
  printf(" here 1 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag42  = 42*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].nparticles,1,MPI_INT,i_rank,tag42,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag42 = 42*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].nparticles,1,MPI_INT,i_rank,tag42,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag42  = 42*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].nparticles,1,MPI_INT,i_rank,tag42,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 2 \n");
/*                                                                           */
/*                 offset                                                    */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag1  = 1*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].offset,1,MPI_INT,i_rank,tag1,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag1 = 1*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].offset,1,MPI_INT,i_rank,tag1,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag1  = 1*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].offset,1,MPI_INT,i_rank,tag1,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 3 \n");
/*                                                                           */
/*                 number_of_doubles                                         */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag2  = 2*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].number_of_doubles,1,MPI_INT,i_rank,tag2,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag2 = 2*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].number_of_doubles,1,MPI_INT,i_rank,tag2,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag2  = 2*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].number_of_doubles,1,MPI_INT,i_rank,tag2,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 4 \n");
/*                                                                           */
/*                 number_of_ints                                         */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag3  = 3*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].number_of_ints,1,MPI_INT,i_rank,tag3,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag3 = 3*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].number_of_ints,1,MPI_INT,i_rank,tag3,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag3  = 3*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].number_of_ints,1,MPI_INT,i_rank,tag3,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 5 \n");
/*                                                                           */
/*                 n_interior                                                */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag5  = 5*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_interior,1,MPI_INT,i_rank,tag5,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag5 = 5*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_interior,1,MPI_INT,i_rank,tag5,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag5  = 5*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_interior,1,MPI_INT,i_rank,tag5,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 6 \n");
/*                                                                           */
/*                 n_interior_and_boundary                                                */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag6  = 6*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_interior_and_boundary,1,MPI_INT,i_rank,tag6,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag6 = 6*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_interior_and_boundary,1,MPI_INT,i_rank,tag6,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag6  = 6*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_interior_and_boundary,1,MPI_INT,i_rank,tag6,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 n_boundary                                                */
/*                                                                           */
  printf(" here 7 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag7  = 7*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_boundary,1,MPI_INT,i_rank,tag7,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag7 = 7*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_boundary,1,MPI_INT,i_rank,tag7,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag7  = 7*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_boundary,1,MPI_INT,i_rank,tag7,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 8 \n");
/*                                                                           */
/*                 n_ghost                                                */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag8  = 8*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_ghost,1,MPI_INT,i_rank,tag8,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag8 = 8*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_ghost,1,MPI_INT,i_rank,tag8,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag8  = 8*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_ghost,1,MPI_INT,i_rank,tag8,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 9 \n");
/*                                                                           */
/*                 burn_status                                                */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag10  = 10*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_status,1,MPI_INT,i_rank,tag10,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
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
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
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
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 10 \n");
/*                                                                           */
/*                 n_A                                                       */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag11  = 11*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_A,1,MPI_INT,i_rank,tag11,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag11 = 11*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_A,1,MPI_INT,i_rank,tag11,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag11  = 11*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_A,1,MPI_INT,i_rank,tag11,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 11 \n");
/*                                                                           */
/*                 n_B                                                       */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag12  = 12*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_B,1,MPI_INT,i_rank,tag12,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag12 = 12*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_B,1,MPI_INT,i_rank,tag12,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag12  = 12*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_B,1,MPI_INT,i_rank,tag12,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 12 \n");
/*                                                                           */
/*                 n_E                                                       */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag13  = 13*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_E,1,MPI_INT,i_rank,tag13,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag13 = 13*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_E,1,MPI_INT,i_rank,tag13,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag13  = 13*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_E,1,MPI_INT,i_rank,tag13,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 13 \n");
/*                                                                           */
/*                 n_F                                                       */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag14  = 14*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_F,1,MPI_INT,i_rank,tag14,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag14 = 14*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].n_F,1,MPI_INT,i_rank,tag14,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag14  = 14*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].n_F,1,MPI_INT,i_rank,tag14,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  printf(" here 14 \n");
/*                                                                           */
/*                 burn_l                                                       */
/*                                                                           */
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag15  = 15*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l,1,MPI_DOUBLE,i_rank,tag15,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag15 = 15*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_l,1,MPI_DOUBLE,i_rank,tag15,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag15  = 15*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l,1,MPI_DOUBLE,i_rank,tag15,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_r                                                    */
/*                                                                           */
  printf(" here 15 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag16  = 16*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r,1,MPI_DOUBLE,i_rank,tag16,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag16 = 16*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_r,1,MPI_DOUBLE,i_rank,tag16,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag16  = 16*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r,1,MPI_DOUBLE,i_rank,tag16,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_delta_l                                                       */
/*                                                                           */
  printf(" here 16 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag17  = 17*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_delta_l,1,MPI_DOUBLE,i_rank,tag17,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag17 = 17*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_delta_l,1,MPI_DOUBLE,i_rank,tag17,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag17  = 17*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_delta_l,1,MPI_DOUBLE,i_rank,tag17,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_delta_r                                                       */
/*                                                                           */
  printf(" here 17 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag18  = 18*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_delta_r,1,MPI_DOUBLE,i_rank,tag18,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag18 = 18*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_delta_r,1,MPI_DOUBLE,i_rank,tag18,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag18  = 18*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_delta_r,1,MPI_DOUBLE,i_rank,tag18,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 start_burn_l                                                       */
/*                                                                           */
  printf(" here 18 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag19  = 19*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].start_burn_l,1,MPI_DOUBLE,i_rank,tag19,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag19 = 19*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].start_burn_l,1,MPI_DOUBLE,i_rank,tag19,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag19  = 19*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].start_burn_l,1,MPI_DOUBLE,i_rank,tag19,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 start_burn_r                                              */
/*                                                                           */
  printf(" here 19 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag20  = 20*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].start_burn_r,1,MPI_DOUBLE,i_rank,tag20,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag20 = 20*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].start_burn_r,1,MPI_DOUBLE,i_rank,tag20,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag20  = 20*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].start_burn_r,1,MPI_DOUBLE,i_rank,tag20,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_r0                                                       */
/*                                                                           */
  printf(" here 20 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag20  = 20*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r0,1,MPI_DOUBLE,i_rank,tag20,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag20 = 20*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_r0,1,MPI_DOUBLE,i_rank,tag20,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag20  = 20*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r0,1,MPI_DOUBLE,i_rank,tag20,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_r1                                                       */
/*                                                                           */
  printf(" here 21 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag21  = 21*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r1,1,MPI_DOUBLE,i_rank,tag21,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag21 = 21*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_r1,1,MPI_DOUBLE,i_rank,tag21,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag21  = 21*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r1,1,MPI_DOUBLE,i_rank,tag21,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_r2                                                       */
/*                                                                           */
  printf(" here 22 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag22  = 22*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r2,1,MPI_DOUBLE,i_rank,tag22,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag22 = 22*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_r2,1,MPI_DOUBLE,i_rank,tag22,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag22  = 22*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r2,1,MPI_DOUBLE,i_rank,tag22,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_r3                                                       */
/*                                                                           */
  printf(" here 23 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag23  = 23*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r3,1,MPI_DOUBLE,i_rank,tag23,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag23 = 23*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_r3,1,MPI_DOUBLE,i_rank,tag23,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag23  = 23*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_r3,1,MPI_DOUBLE,i_rank,tag23,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_l0                                                       */
/*                                                                           */
  printf(" here 24 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag24  = 24*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l0,1,MPI_DOUBLE,i_rank,tag24,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag24 = 24*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_l0,1,MPI_DOUBLE,i_rank,tag24,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag24  = 24*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l0,1,MPI_DOUBLE,i_rank,tag24,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_l1                                                       */
/*                                                                           */
  printf(" here 25 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag25  = 25*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l1,1,MPI_DOUBLE,i_rank,tag25,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag25 = 25*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_l1,1,MPI_DOUBLE,i_rank,tag25,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag25  = 25*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l1,1,MPI_DOUBLE,i_rank,tag25,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_l2                                                       */
/*                                                                           */
  printf(" here 26 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag26  = 26*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l2,1,MPI_DOUBLE,i_rank,tag26,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag26 = 26*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_l2,1,MPI_DOUBLE,i_rank,tag26,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag26  = 26*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l2,1,MPI_DOUBLE,i_rank,tag26,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 burn_l3                                                       */
/*                                                                           */
  printf(" here 27 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag27  = 27*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l3,1,MPI_DOUBLE,i_rank,tag27,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag27 = 27*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(&node_info[rank].burn_l3,1,MPI_DOUBLE,i_rank,tag27,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag27  = 27*(MAX_TAGS)+rank;
    if ( (MPI_Recv(&node_info[i_rank].burn_l3,1,MPI_DOUBLE,i_rank,tag27,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 species                                                       */
/*                                                                           */
  printf(" here 28 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag28  = 28*(MAX_TAGS)+rank;

    if ( (MPI_Recv(node_info[i_rank].species,NPARTICLES,MPI_INT,i_rank,tag28,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag28 = 28*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].species,NPARTICLES,MPI_INT,i_rank,tag28,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag28  = 28*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].species,NPARTICLES,MPI_INT,i_rank,tag28,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 interior                                                       */
/*                                                                           */
  printf(" here 29 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag29  = 29*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].interior,NPARTICLES,MPI_INT,i_rank,tag29,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag29 = 29*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].interior,NPARTICLES,MPI_INT,i_rank,tag29,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag29  = 29*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].interior,NPARTICLES,MPI_INT,i_rank,tag29,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 boundary                                                       */
/*                                                                           */
  printf(" here 30 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag30  = 30*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].boundary,NPARTICLES,MPI_INT,i_rank,tag30,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag30 = 30*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].boundary,NPARTICLES,MPI_INT,i_rank,tag30,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag30  = 30*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].boundary,NPARTICLES,MPI_INT,i_rank,tag30,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 interior_and_boundary                                                       */
/*                                                                           */
  printf(" here 31 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag31  = 31*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].interior_and_boundary,NPARTICLES,MPI_INT,i_rank,tag31,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag31 = 31*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].interior_and_boundary,NPARTICLES,MPI_INT,i_rank,tag31,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag31  = 31*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].interior_and_boundary,NPARTICLES,MPI_INT,i_rank,tag31,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 ghost                                                       */
/*                                                                           */
  printf(" here 32 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag32  = 32*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost,NPARTICLES,MPI_INT,i_rank,tag32,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag32 = 32*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].ghost,NPARTICLES,MPI_INT,i_rank,tag32,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag32  = 32*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost,NPARTICLES,MPI_INT,i_rank,tag32,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 ghost_x                                                       */
/*                                                                           */
  printf(" here 33 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag33  = 33*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost_x,NPARTICLES,MPI_INT,i_rank,tag33,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag33 = 33*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].ghost_x,NPARTICLES,MPI_INT,i_rank,tag33,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag33  = 33*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost_x,NPARTICLES,MPI_INT,i_rank,tag33,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 ghost_y                                                       */
/*                                                                           */
  printf(" here 34 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag34  = 34*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost_y,NPARTICLES,MPI_INT,i_rank,tag34,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag34 = 34*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].ghost_y,NPARTICLES,MPI_INT,i_rank,tag34,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag34  = 34*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost_y,NPARTICLES,MPI_INT,i_rank,tag34,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 ghost_z                                                       */
/*                                                                           */
  printf(" here 35 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag35  = 35*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost_z,NPARTICLES,MPI_INT,i_rank,tag35,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag35 = 35*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].ghost_z,NPARTICLES,MPI_INT,i_rank,tag35,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag35  = 35*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].ghost_z,NPARTICLES,MPI_INT,i_rank,tag35,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 raw_index                                                       */
/*                                                                           */
  printf(" here 36 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag36  = 36*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].raw_index,NPARTICLES,MPI_INT,i_rank,tag36,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag36 = 36*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].raw_index,NPARTICLES,MPI_INT,i_rank,tag36,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag36  = 36*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].raw_index,NPARTICLES,MPI_INT,i_rank,tag36,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                                                                           */
/*                 inv_raw_index                                             */
/*                                                                           */
  printf(" here 41 \n");
  for (i_rank=0;i_rank<rank;i_rank++)
  {
    tag41  = 41*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].inv_raw_index,TOTAL_PARTICLES,MPI_INT,i_rank,tag41,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  for (i_rank=0;i_rank<=cluster_size;i_rank++)
  {
    if (i_rank!=rank)
    {
      tag41 = 41*(MAX_TAGS)+i_rank;
      if ( (MPI_Send(node_info[rank].inv_raw_index,TOTAL_PARTICLES,MPI_INT,i_rank,tag41,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" SynchroniseNodeInfo(): unable to send packet \n");
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
  }
  for (i_rank=rank+1;i_rank<=cluster_size;i_rank++)
  {
    tag41  = 41*(MAX_TAGS)+rank;
    if ( (MPI_Recv(node_info[i_rank].inv_raw_index,TOTAL_PARTICLES,MPI_INT,i_rank,tag41,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" SynchroniseNodeInfo(): unable to receive packet \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);
  exit_status = EXIT_SUCCESS;

RETURN:

  verbosity(2,fname,pars);
  return exit_status;
}
