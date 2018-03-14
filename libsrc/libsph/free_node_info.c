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

#include "free_node_info.h"

int FreeNodeInfo(int cluster_size,PARS *pars)
{
  int exit_status                      = EXIT_FAILURE;
  extern NODE_INFO *node_info;

  char fname[]                         = "...FreeNodeInfo";

  int i_rank                           = 0;
  int i                                = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  if ( (node_info == NULL) )
  {
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

  for (i_rank=0;i_rank<cluster_size+1;i_rank++)  
  {
    Free_sph(node_info[i_rank].h_pts); 
    Free_sph(node_info[i_rank].marker); 
    Free_sph(node_info[i_rank].burn_F); 
    Free_sph(node_info[i_rank].burn_E); 
    Free_sph(node_info[i_rank].burn_B); 
    Free_sph(node_info[i_rank].burn_A); 
    Free_sph(node_info[i_rank].inv_raw_index); 
    Free_sph(node_info[i_rank].raw_index); 
    Free_sph(node_info[i_rank].ghost_z); 
    Free_sph(node_info[i_rank].ghost_y); 
    Free_sph(node_info[i_rank].ghost_x); 
    Free_sph(node_info[i_rank].ghost_mirror); 
    Free_sph(node_info[i_rank].ghost); 
    Free_sph(node_info[i_rank].interior_and_boundary); 
    Free_sph(node_info[i_rank].boundary); 
    Free_sph(node_info[i_rank].interior); 
    Free_sph(node_info[i_rank].species); 
    Free_sph(node_info[i_rank].contains_burn_r); 
    Free_sph(node_info[i_rank].contains_burn_l); 
  }
  Free_sph(node_info);
  exit_status = EXIT_SUCCESS; 

RETURN:

  verbosity(2,fname,pars);
  return exit_status;
}
