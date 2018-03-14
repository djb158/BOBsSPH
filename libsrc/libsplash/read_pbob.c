/*---------------------------------------------------------------------------*\
|                                                                             |
|  File: read_pbob.c                                                          |
|                                                                             |
|  Function: PBOB ReadPBOB(char *file_name)                                   |
|                                                                             |
|  Purpose:  read in .pbob binary header and store in PBOB struct             |
|                                                                             |
|  Call:                                                                      |
|           pbob = readPBOB(file_name)                                        |
|                                                                             |
|  Input:   char * file_name    .pbob file_name                               |
|                                                                             |
|                                                                             |
|  Output:  PBOB *pbob    A PBOB binary header struct                         |
|                                                                             |
|  Global variables:  none                                                    |
|                                                                             |
|  Required resources:                                                        |
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

PBOB *ReadPBOB(char *file_name)
{
  PBOB  *pbob                          = NULL;

  FILE *file_ptr                       = NULL;

  char fname[]                         = "...ReadPBOB";

  int exit_status                      = EXIT_FAILURE;
  int i                                = 0;
  int nmemb                            = 0;

/*                                                                           */
/*                                                                           */
  if ( (file_ptr=fopen(file_name,"rb")) == NULL)
  {
    printf("%s(): -unable to open file: %s\n",fname,file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  pbob = (PBOB *)calloc(1,sizeof(PBOB));
  if ((nmemb=fread(pbob,sizeof(PBOB),1,file_ptr))!=((size_t)1))
  {
    printf("%s -Error reading PBOB struct \n",fname);
    if (pbob)
    {
      free(pbob); pbob = NULL;
      exit_status = EXIT_FAILURE;
      fclose(file_ptr);
      goto RETURN;
    }
  }

  pbob[0].endian_int = 999;

  fclose(file_ptr);
  exit_status = EXIT_SUCCESS;

RETURN:
  return pbob;
}
