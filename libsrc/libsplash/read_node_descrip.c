/*---------------------------------------------------------------------------*\
|                                                                             |
|  File: read_node_descrip.c                                                  |
|                                                                             |
|  Function: NODE_DESCRIP *ReadNodeDescrip(char *file_name,int cluster_size)  |
|                                                                             |
|  Purpose:  read node description information from a .pbob file and store in |
|            a NODE_DESCRIP struct                                            |
|                                                                             |
|  Call:                                                                      |
|           node_descrip = ReadNodeDescrip(file_name,cluster_size)            |
|                                                                             |
|  Input:   char * file_name    .pbob file_name                               |
|           int cluster_size    number of compute nodes in the MPI cluster    |
|                                                                             |
|                                                                             |
|  Output:  NODE_DESCRIP *node_descrip    A NODE_DESCRIP node descriptor      |
|                                         struct                              |
|                                                                             |
|  Global variables:  none                                                    |
|                                                                             |
|  Required resources:  none                                                  |
|                                                                             |
|  Error:  return NULL on error                                               |
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
#include "sph_types.h"
#include "numeric_constants.h"
#include "pbob.h"
#include "node_descrip.h"

NODE_DESCRIP *ReadNodeDescrip(char *file_name,int cluster_size)
{
  PBOB  pbob;
  NODE_DESCRIP *node_descrip           = NULL;

  FILE *file_ptr                       = NULL;

  char fname[]                         = "...ReadNodeDescrip";

  int exit_status                      = EXIT_FAILURE;
  int i                                = 0;
/*                                                                           */
/*                                                                           */
  if ( (file_ptr=fopen(file_name,"rb")) == NULL)
  {
    printf("%s(): -unable to open file: %s\n",fname,file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  fread(&pbob,sizeof(PBOB),1,file_ptr);
  cluster_size = (int)pbob.cluster_size;

  node_descrip = (NODE_DESCRIP *)calloc(cluster_size,sizeof(NODE_DESCRIP));
  fread(node_descrip,sizeof(NODE_DESCRIP),cluster_size,file_ptr);

  fclose(file_ptr);
  exit_status = EXIT_SUCCESS;

RETURN:
  free(node_descrip);
  return node_descrip;
}
