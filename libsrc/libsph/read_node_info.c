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

#include "read_node_info.h"

int ReadNodeInfo(PARS *pars)
{
  extern NODE_INFO *node_info;

  FILE *in_file_ptr                    = NULL;

  char fname[]                         = "...ReadNodeInfo";
  char *in_file_name                   = NULL;

  int exit_status                      = EXIT_FAILURE;
  int i                                = 0;

#include  "pars_include.h"
  if (pars != NULL)
  {
    verbosity(1,fname,pars);
  }

  in_file_name = (char *)calloc(MAX_CHARS,sizeof(char));

  sprintf(in_file_name,"%s/node.%i",out_dir,rank);
  if ((in_file_ptr=fopen(in_file_name,"rb"))==NULL)
  {
    printf(" %s() -unable to open %s for reading \n",fname,in_file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  fread(node_info[rank].node_name,sizeof(char),64,in_file_ptr);
  fread(node_info[rank].species,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].interior,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].boundary,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].interior_and_boundary,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].ghost,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].ghost_mirror,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].ghost_x,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].ghost_y,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].ghost_z,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].raw_index,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].marker,sizeof(int),NPARTICLES,in_file_ptr);
  fread(node_info[rank].inv_raw_index,sizeof(int),TOTAL_PARTICLES,in_file_ptr);
  fread(node_info[rank].h_pts,sizeof(double),H_PTS,in_file_ptr);
  fread(&node_info[rank].inv_raw_index_set,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].number_of_doubles,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].number_of_ints,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].n_interior,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].n_interior_and_boundary,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].n_boundary,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].n_ghost,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].total_particles,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].n_marker,sizeof(int),1,in_file_ptr);
  fread(&node_info[rank].nparticles,sizeof(int),1,in_file_ptr);
  fclose(in_file_ptr);

  exit_status = EXIT_SUCCESS;

RETURN:
  Free_sph(in_file_name);

  if (pars != NULL)
  {
    verbosity(2,fname,pars);
  }
  return exit_status;
}
