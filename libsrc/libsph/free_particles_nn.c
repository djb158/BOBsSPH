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

#include "free_particles_nn.h"

int FreeParticlesNN(PARTICLES *particles,PARS *pars,int N)
{
  char   fname[]                       = "...FreeParticlesNN";

  int i                                = LARGE_NEGATIVE_INT;
  int num                              = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);

  if (particles)
  {
    for (i=0;i<N;i++)
    {
      num = particles[0].nn_index[i].num;
      if (num > 0)
      {
        Free_sph(particles[0].nn_index[i].node);                 particles[0].nn_index[i].node                 = NULL;
        Free_sph(particles[0].nn_index[i].n_offnode_neighbours); particles[0].nn_index[i].n_offnode_neighbours = NULL;
      }
    }
  }
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
