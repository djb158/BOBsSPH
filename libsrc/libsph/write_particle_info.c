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

#include "write_particle_info.h"

int WriteParticleInfo(PARTICLES *particles,PARS *pars,int particles_num,const char  *a_test)
{
  FILE *out_file_ptr                   = NULL;

  char fname[]                         = "...WriteParticleInfo";
  char *out_file_name                  = NULL;

  int exit_status                      = EXIT_FAILURE;
  int i                                = 0;
  int k                                = 0;

#include  "pars_include.h"
  verbosity(1,fname,pars);

  out_file_name = (char *)calloc(MAX_CHARS,sizeof(char));

  sprintf(out_file_name,"%s/particles_%i.%i",out_dir,particles_num,rank);
  if ((out_file_ptr=fopen(out_file_name,"wb"))==NULL)
  {
    printf(" %s() -unable to open %s for writing \n",fname,out_file_name);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }


  if ( (strcmp(a_test,"test")) != 0)
  {
    fwrite(&NPARTICLES,sizeof(int),1,out_file_ptr);
    fwrite(&TOTAL_PARTICLES,sizeof(int),1,out_file_ptr);
    fwrite(particles[0].m,        sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].h,        sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].p,        sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].rho,      sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].U,        sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].dUdt,     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].divV,     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].x[0],     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].x[1],     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].x[2],     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].v[0],     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].v[1],     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].v[2],     sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].dvdt[0],  sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].dvdt[1],  sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].dvdt[2],  sizeof(double),NPARTICLES,out_file_ptr);
    fwrite(particles[0].raw_index,sizeof(int),NPARTICLES,out_file_ptr);
    fwrite(particles[0].species,  sizeof(int),NPARTICLES,out_file_ptr);
    for (i=0;i<NPARTICLES;i++)
    {
      fwrite(particles[0].nn[i],sizeof(int),NN_K,out_file_ptr);
    }
    fwrite(&particles[0].number_of_doubles,sizeof(int),1,out_file_ptr);
    fwrite(&particles[0].number_of_ints,sizeof(int),1,out_file_ptr);
    fwrite(&particles[0].rank,sizeof(int),1,out_file_ptr);
    fwrite(&particles[0].step,sizeof(int),1,out_file_ptr);
    fwrite(&particles[0].t,sizeof(double),1,out_file_ptr);
  }
  fclose(out_file_ptr);

  exit_status = EXIT_SUCCESS;

RETURN:
  Free_sph(out_file_name);
  verbosity(2,fname,pars);
  return exit_status;
}
