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
#include <unistd.h>
#include "sph_types.h"
#include "numeric_constants.h"
#include "particle.h"

#define MAX_CHARS   (1024)
#define _FILE_OFFSET_BITS 64

int WriteParticle(PARTICLE *particle,int nparticles,int rank,char *out_dir,int time_slice)
{
  extern int cluster_size;

  FILE *file_ptr                       = NULL;

  char fname[]                         = "...WriteParticle";
  char *file_name                      = NULL;

  int number_of_time_slices            = LARGE_NEGATIVE_INT;
  int token_r                          = LARGE_NEGATIVE_INT;
  int token_s                          = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;

  u_int32_t n_slices                   = 0;

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

  if (rank != 0)
  {
    token_r = 1;
    MPI_Recv(&token_r,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    token_s = token_r;
  }
  else
  {
    token_s = -1;
    sleep(1);
    /*
    if ( (file_ptr = fopen(file_name,"r+b")) == NULL)
    {
      printf("Rank: %i %s(): -unable to open file: %s()\n",rank,fname,file_name);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if (fseeko(file_ptr,10108,SEEK_SET) != 0)
    {
      printf("%s -Error seeking number_of_time_slices index \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    number_of_time_slices = 1;
    n_slices = (u_int32_t)number_of_time_slices;
    fwrite(&n_slices,sizeof(u_int32_t),1,file_ptr);
    if (fseeko(file_ptr,0,SEEK_END) != 0)
    {
      printf("%s -Error seeking EOF\n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    fclose(file_ptr);
*/
  }
/*                                                                           */
/*                 write particle info per node                              */
/*                                                                           */
  if ( (file_ptr = fopen(file_name,"ab")) == NULL)
  {
    printf("Rank: %i %s(): -unable to open file: %s()\n",rank,fname,file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  fwrite(particle,sizeof(PARTICLE),nparticles,file_ptr);
  fclose(file_ptr);
  if (rank < cluster_size)
  {
    MPI_Send(&token_s,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
  }
  exit_status = EXIT_SUCCESS;

RETURN:
  return exit_status;
}
