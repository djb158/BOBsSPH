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

#include "write_particles.h"

int WriteParticles(PARTICLES *particles,PARS *pars, char *file_name)
{
  extern int cluster_size;

  FILE *file_ptr                       = NULL;

  char *header                         = NULL;
  char fname[]                         = "...WriteParticles";

  int i                                = 0;
  int exit_status                      = EXIT_FAILURE;
  int endian                           = 0;
  int i_dummy                          = 0;
  int number_of_nodes                  = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  number_of_nodes = cluster_size-1;
  if ( (file_ptr = fopen(file_name,"wb")) == NULL)
  {
    printf(" WriteParticles(): -unable to open file %s"
           " for writing\n",file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

  header = (char *)calloc(2000,sizeof(char));
  strcpy(header,(char *)
 "|*****************************************************************************|\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                           THIS IS A TEST                                    |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|                                                                             |\n"
 "|*****************************************************************************|");
  endian =  BigOrLittleEndian();
  fwrite(header,2000,1,file_ptr);
  fwrite(&endian,4,1,file_ptr);
  fwrite(&PARTICLES_IN_X,4,1,file_ptr);
  fwrite(&PARTICLES_IN_Y,4,1,file_ptr);
  fwrite(&PARTICLES_IN_Z,4,1,file_ptr);
  fwrite(&KERNEL_ID,4,1,file_ptr);
  fwrite(&number_of_nodes,4,1,file_ptr);
  for (i=0;i<10;i++)
  {
    fwrite(&i_dummy,4,1,file_ptr);
  }
  fclose(file_ptr);
  Free_sph(header);

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
