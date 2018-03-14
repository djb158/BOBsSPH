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

#include "write_node_info.h"

int WriteNodeInfo(PARS *pars)
{
  extern NODE_INFO *node_info;

  FILE *out_file_ptr                   = NULL;

  char fname[]                         = "...WriteNodeInfo";
  char *out_file_name                  = NULL;

  int exit_status                      = EXIT_FAILURE;

  printf(" gere 00 \n");

#include  "pars_include.h"
  printf(" gere 01 \n");
  verbosity(1,fname,pars);
  printf(" gere 02 \n");

  out_file_name = (char *)calloc(MAX_CHARS,sizeof(char));
  printf(" gere 03 \n");

  sprintf(out_file_name,"%s/node.%i",out_dir,rank);
  printf(" gere 04 \n");
  if ((out_file_ptr=fopen(out_file_name,"wb"))==NULL)
  {
    printf(" %s() -unable to open %s for writing \n",fname,out_file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  printf(" gere 05 \n");

  fwrite(node_info[rank].node_name,sizeof(char),64,out_file_ptr);
  fwrite(node_info[rank].species,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].interior,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].boundary,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].interior_and_boundary,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].ghost,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].ghost_mirror,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].ghost_x,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].ghost_y,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].ghost_z,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].raw_index,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].marker,sizeof(int),NPARTICLES,out_file_ptr);
  fwrite(node_info[rank].inv_raw_index,sizeof(int),TOTAL_PARTICLES,out_file_ptr);
  fwrite(node_info[rank].h_pts,sizeof(double),H_PTS,out_file_ptr);
  fwrite(&node_info[rank].inv_raw_index_set,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].number_of_doubles,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].number_of_ints,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].n_interior,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].n_interior_and_boundary,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].n_boundary,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].n_ghost,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].total_particles,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].n_marker,sizeof(int),1,out_file_ptr);
  fwrite(&node_info[rank].nparticles,sizeof(int),1,out_file_ptr);
  fclose(out_file_ptr);

  exit_status = EXIT_SUCCESS;

RETURN:
  Free_sph(out_file_name);
  verbosity(2,fname,pars);
  return exit_status;
}
