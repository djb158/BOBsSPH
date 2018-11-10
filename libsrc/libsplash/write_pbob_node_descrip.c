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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stddef.h> 
#include "sph_types.h"
#include "numeric_constants.h"
#include "pbob.h"
#include "node_descrip.h"

#define MAX_CHARS   (1024)

int WritePbobNodeDescrip(PBOB *pbob,NODE_DESCRIP *node_descrip,char *out_dir,int rank,int time_slice)
{
  extern int cluster_size;

  FILE *file_ptr                       = NULL;

  char fname[]                         = "...WritePbobNodeDescrip";
  char *file_name                      = NULL;

  int token_r                          = LARGE_NEGATIVE_INT;
  int token_s                          = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;

/*                                                                           */
/*                 use receive/send tokens to control order of file          */
/*                 access in rank order.                                     */
/*                                                                           */

  file_name = (char *)calloc(MAX_CHARS,sizeof(char));

  if (time_slice >= 10000)
  {
    sprintf(file_name,"%s/output_%5i.pbob",out_dir,time_slice);
  }
  else if ( time_slice >= 1000)
  {
    sprintf(file_name,"%s/output_0%4i.pbob",out_dir,time_slice);
  }
  else if ( time_slice >= 100)
  {
    sprintf(file_name,"%s/output_00%3i.pbob",out_dir,time_slice);
  }
  else if ( time_slice >= 10)
  {
    sprintf(file_name,"%s/output_000%2i.pbob",out_dir,time_slice);
  }
  else if ( time_slice >= 1)
  {
    sprintf(file_name,"%s/output_0000%1i.pbob",out_dir,time_slice);
  }
  else
  {
    printf("Rank: %i %s(): -time slice %i must be > 0 \n",rank,fname,time_slice);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
/*                                                                           */
/*                                                                           */
/*                                                                           */
  printf(" file_name = >%s< \n",file_name);
  if ( (file_ptr = fopen(file_name,"wb")) == NULL)
  {
    printf("Rank: %i %s(): -unable to open file: %s()\n",rank,fname,file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

  fwrite(pbob,sizeof(PBOB),1,file_ptr);
  fwrite(node_descrip,sizeof(NODE_DESCRIP),cluster_size+1,file_ptr);
  fclose(file_ptr);
  exit_status = EXIT_SUCCESS;

RETURN:
  return exit_status;
}
