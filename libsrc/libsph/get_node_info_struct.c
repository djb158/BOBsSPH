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

#include "get_node_info_struct.h"

int GetNodeInfoStruct(int cluster_size,char *rank_name,double delta,PARS *pars)
{
  int exit_status                      = EXIT_FAILURE;
  extern NODE_INFO *node_info;

  char fname[]                         = "...GetNodeInfoStruct";

  int i_rank                           = 0;
  int i                                = 0;
  int k                                = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  node_info = (NODE_INFO *)calloc(cluster_size+1,sizeof(NODE_INFO));
  for (i_rank=0;i_rank<cluster_size+1;i_rank++)  
  {
    strcpy(node_info[i_rank].node_name,(char *)"                                                               \0");
    strcpy(node_info[i_rank].node_name,rank_name);
    node_info[i_rank].offset                        = LARGE_NEGATIVE_INT; 
    node_info[i_rank].number_of_doubles             = LARGE_NEGATIVE_INT;
    node_info[i_rank].number_of_ints                = LARGE_NEGATIVE_INT;
    node_info[i_rank].n_interior                    = 0;
    node_info[i_rank].n_interior_and_boundary       = 0;
    node_info[i_rank].n_boundary                    = 0;
    node_info[i_rank].n_ghost                       = 0;
    node_info[i_rank].y                             = 0;
    node_info[i_rank].burn_l                        = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_r                        = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_delta_l                  = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_delta_r                  = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_status                   = LARGE_NEGATIVE_INT;
    node_info[i_rank].start_burn_l                  = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].start_burn_r                  = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_r0                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_r1                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_r2                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_r3                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_l0                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_l1                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_l2                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].burn_l3                       = LARGE_NEGATIVE_DOUBLE;
    node_info[i_rank].n_A                           = LARGE_NEGATIVE_INT;
    node_info[i_rank].n_B                           = LARGE_NEGATIVE_INT;
    node_info[i_rank].n_E                           = LARGE_NEGATIVE_INT;
    node_info[i_rank].n_F                           = LARGE_NEGATIVE_INT;
    node_info[i_rank].total_particles               = LARGE_NEGATIVE_INT;
    node_info[i_rank].inv_raw_index_set             = LARGE_NEGATIVE_INT;
    node_info[i_rank].n_contains_burn_l             = H_PTS;
    node_info[i_rank].n_contains_burn_r             = H_PTS;
    node_info[i_rank].contains_burn_l               = (int *)calloc(H_PTS,sizeof(int));
    node_info[i_rank].contains_burn_r               = (int *)calloc(H_PTS,sizeof(int));
    node_info[i_rank].species                       = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].interior                      = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].boundary                      = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].interior_and_boundary         = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].ghost                         = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].ghost_mirror                  = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].ghost_x                       = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].ghost_y                       = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].ghost_z                       = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].raw_index                     = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].inv_raw_index                 = (int *)calloc(TOTAL_PARTICLES,sizeof(int));
    node_info[i_rank].burn_A                        = NULL;
    node_info[i_rank].burn_B                        = NULL;
    node_info[i_rank].burn_E                        = NULL;
    node_info[i_rank].burn_F                        = NULL;
    node_info[i_rank].marker                        = (int *)calloc(NPARTICLES,sizeof(int));
    node_info[i_rank].h_pts                         = (double *)calloc(H_PTS,sizeof(double));
    for (i=0;i<H_PTS;i++)
    {
      node_info[i_rank].h_pts[i] = Z0 + (Z1-Z0)*(double)i/(double)H_PTS;
    }
    for (k=0;k<NPARTICLES;k++)
    {
      node_info[i_rank].species[k]                  = LARGE_NEGATIVE_INT;
      node_info[i_rank].boundary[k]                 = LARGE_NEGATIVE_INT;
      node_info[i_rank].interior[k]                 = LARGE_NEGATIVE_INT;
      node_info[i_rank].interior_and_boundary[k]    = LARGE_NEGATIVE_INT;
      node_info[i_rank].ghost[k]                    = LARGE_NEGATIVE_INT;
      node_info[i_rank].ghost_mirror[k]             = LARGE_NEGATIVE_INT;
      node_info[i_rank].ghost_x[k]                  = LARGE_NEGATIVE_INT;
      node_info[i_rank].ghost_y[k]                  = LARGE_NEGATIVE_INT;
      node_info[i_rank].ghost_z[k]                  = LARGE_NEGATIVE_INT;
      node_info[i_rank].raw_index[k]                = LARGE_NEGATIVE_INT;
      node_info[i_rank].marker[k]                   = LARGE_NEGATIVE_INT;
    }
    for (k=0;k<TOTAL_PARTICLES;k++)
    {
      node_info[i_rank].inv_raw_index[k]            = LARGE_NEGATIVE_INT;
    }
    for (k=0;k<H_PTS;k++)
    {
      node_info[i_rank].contains_burn_l[k] = LARGE_NEGATIVE_INT;
      node_info[i_rank].contains_burn_r[k] = LARGE_NEGATIVE_INT;
    }
  }
  if (rank < cluster_size)
  {
/*  node_info[rank].start_burn_l = X0 + (double)rank*delta - EPSILON_DOUBLE;
    node_info[rank].start_burn_r = X0 + (double)(rank+1)*delta + OFFSET + EPSILON_DOUBLE; */

    node_info[rank].start_burn_l = X0 + (double)rank*delta;
    node_info[rank].start_burn_r = X0 + (double)rank*delta + delta + OFFSET;
  }
  else
  {
    node_info[rank].start_burn_l = X1 - delta - OFFSET;
    node_info[rank].start_burn_r = X1;
  }
  node_info[rank].burn_l = node_info[rank].start_burn_l;
  node_info[rank].burn_r = node_info[rank].start_burn_r;
  switch (RESTART)
  {
    case 0:
      break;
    case 1:
      ReadNodeInfo(pars); 
      break;
    default:
      exit_status = EXIT_FAILURE;
      printf(" Rank %i: restart not set correctly, has value %i \n",rank,RESTART);
      goto RETURN;
      break;
  }

  exit_status = EXIT_SUCCESS; 
RETURN:

  verbosity(2,fname,pars);
  return exit_status;
}
