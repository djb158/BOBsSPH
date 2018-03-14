/*---------------------------------------------------------------------------*\
|                                                                             |
|  File:     read_particle.c                                                  |
|                                                                             |
|  Function: PARTICLE *ReadParticle(char *file_name,int time_slice,           |
|                                   int start_indx,int N)                     |
|                                                                             |
|  Purpose:  read in particle information for a specified time slice from a   |
|            a .pbob file. A PARTICLE struct is filled and returned           |
|                                                                             |
|  Call:                                                                      |
|           particle = ReadParticle(file_name,time_slice,start_indx,N)        |
|                                                                             |
|  Input:   char * file_name    .pbob file_name                               |
|           int time_slice      time slice to read in data for                |
|           int start_indx      start index of particle to read in, must      |
|                               satisfy: 0 <= start_indx <  total_particles   |
|           int N               number of particles                           |
|                                                                             |
|                                                                             |
|  Output:  PARTICLE *particle  structure holding information for N particles |
|                                                                             |
|  Global variables:    none                                                  |
|                                                                             |
|  Required resources:  none                                                  |
|                                                                             |
|  Error:  return NULL ptr on error                                           |
|                                                                             |
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
#include "particle.h"

#define _FILE_OFFSET_BITS 64

PARTICLE *ReadParticle(char *file_name,int time_slice,int start_indx,int N)
{
  PBOB  pbob;
  PARTICLE *particle                   = NULL;

  FILE *file_ptr                       = NULL;

  char fname[]                         = "...ReadParticle";

  int cluster_size                     = LARGE_NEGATIVE_INT;
  int first_particle_byte_offset       = LARGE_NEGATIVE_INT;
  int particle_length_bytes            = LARGE_NEGATIVE_INT;
  int total_particles                  = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;
  int N_to_use                         = N;
  int i                                = 0;

  off_t indx_offset                    = 0;

  size_t nmemb                         = 0;
/*                                                                           */
/*                                                                           */
  if ( (file_ptr=fopen(file_name,"rb")) == NULL)
  {
    printf("%s(): -unable to open file: %s\n",fname,file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  fread(&pbob,sizeof(PBOB),1,file_ptr);
  total_particles            = (int)pbob.total_particles;
  if (start_indx < 0)
  {
    printf("%s -requested start_index has to be greater than or equal to 0 \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  if ( (start_indx+N) > total_particles)
  {
    N_to_use = total_particles - start_indx;
    printf("%s -requested particles exceeds total particle number, using %i \n",fname,N_to_use);
  }
  if (start_indx > total_particles)
  {
    printf("%s -start index greater than total particle number, -aborting \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  if (time_slice < 1)
  {
    printf("%s -time slice must be greater than 0, aborting \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  cluster_size               = (int)pbob.cluster_size;
  first_particle_byte_offset = (int)pbob.first_particle_byte_offset;
  particle_length_bytes      = (int)pbob.particle_length_bytes;
  indx_offset                = (off_t)first_particle_byte_offset
                             + (off_t)(time_slice-1)
                             * (off_t)total_particles
                             * (off_t)particle_length_bytes
                             + (off_t)start_indx 
                             * (off_t)particle_length_bytes;

  if (fseeko(file_ptr,indx_offset,SEEK_SET) != 0)
  {
    printf("%s -Error reading timeslice \n",fname);
    exit_status = EXIT_FAILURE;
    fclose(file_ptr);
    goto RETURN;
  }
  particle = (PARTICLE *)calloc((size_t)N_to_use,sizeof(PARTICLE));
  if ((nmemb=fread(particle,sizeof(PARTICLE),(size_t)N_to_use,file_ptr))!=((size_t)N_to_use))
  {
    if (particle)
    {
      printf("%s -Error reading timeslice, or attempting read past end of file \n",fname);
      free(particle);particle = NULL;
      exit_status = EXIT_FAILURE;
      fclose(file_ptr);
      goto RETURN;
    }
  }

  fclose(file_ptr);
  exit_status = EXIT_SUCCESS;

RETURN:
  return particle;
}
