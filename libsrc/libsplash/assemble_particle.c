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

#include "assemble_particle.h"

/*
#define MASK_INTER    (512)
#define MASK_GHOST    (1024)
#define MASK_BOUND    (2048)
*/

PARTICLE *Assemble_PARTICLE(PARTICLES *particles,PARS *pars,int *unique_particles,int time_slice,double **vorticity)
{
  extern NODE_INFO *node_info;

  PARTICLE *particle                   = NULL;

  int i                                = LARGE_NEGATIVE_INT;
  int j                                = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int rank_i                           = LARGE_NEGATIVE_INT;
  int raw_index                        = LARGE_NEGATIVE_INT;
  int found                            = LARGE_NEGATIVE_INT;
  int species_basic                    = LARGE_NEGATIVE_INT;
  int species                          = LARGE_NEGATIVE_INT; 
  int exit_status                      = EXIT_FAILURE;

  char fname[]                         = "...Assemble_PARTICLE";

#include "pars_include.h"
  verbosity(1,fname,pars);

  nparticles = node_info[rank].nparticles;

  j = 0;
  for (i=0;i<nparticles;i++)
  {
    raw_index = node_info[rank].raw_index[i];
    found = 0;
    for (rank_i=0;rank_i<rank;rank_i++)
    {
      if (node_info[rank_i].inv_raw_index[raw_index] > -1)
      {
         found = 1;
         break;
      }
    }
    if (found == 0)
    {
      j++;
    }
  }
  *unique_particles = j;

  particle = (PARTICLE *)calloc(*unique_particles,sizeof(PARTICLE));
  j = 0;
  for (i=0;i<nparticles;i++)
  {
    raw_index = node_info[rank].raw_index[i];
    found = 0;
    for (rank_i=0;rank_i<rank;rank_i++)
    {
      if (node_info[rank_i].inv_raw_index[raw_index] > -1)
      {
         found = 1;
         break;
      }
    }
    if (found == 0)
    {
      species                = particles[0].species[i];
      species_basic          = (species&MASK_GHOST) + (species&MASK_BOUND) + (species&MASK_INTER); // need parenthesis to prevent optimization

      particle[j].index      = (u_int64_t)particles[0].raw_index[i];

      particle[j].species    = (u_int32_t)species;
      particle[j].start_node = (u_int32_t)particles[0].rank;  // need to correct this
      particle[j].end_node   = (u_int32_t)particles[0].rank;
      particle[j].time_slice = (u_int32_t)time_slice;

      particle[j].time       = FLOAT32_T(particles[0].t);
      particle[j].x          = FLOAT32_T(particles[0].x[0][i]);
      particle[j].y          = FLOAT32_T(particles[0].x[1][i]);
      particle[j].z          = FLOAT32_T(particles[0].x[2][i]);
      particle[j].vx         = FLOAT32_T(particles[0].v[0][i]);
      particle[j].vy         = FLOAT32_T(particles[0].v[1][i]);
      particle[j].vz         = FLOAT32_T(particles[0].v[2][i]);
      particle[j].ax         = FLOAT32_T(particles[0].dvdt[0][i]);
      particle[j].ay         = FLOAT32_T(particles[0].dvdt[1][i]);
      particle[j].az         = FLOAT32_T(particles[0].dvdt[2][i]);

      particle[j].vortx      = FLOAT32_T(vorticity[0][i]);
      particle[j].vorty      = FLOAT32_T(vorticity[1][i]);
      particle[j].vortz      = FLOAT32_T(vorticity[2][i]);
      particle[j].U          = FLOAT32_T(particles[0].U[i]);
      particle[j].dUdt       = FLOAT32_T(particles[0].dUdt[i]);
      particle[j].h          = FLOAT32_T(particles[0].h[i]);
      particle[j].rho        = FLOAT32_T(particles[0].rho[i]);
      particle[j].p          = FLOAT32_T(particles[0].p[i]);
      particle[j].m          = FLOAT32_T(particles[0].m[i]);
      j++;
    }
  }

RETURN:
  verbosity(2,fname,pars);
  return particle;
}
