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

#include "integrate_particle_energy_boundary.h"

int IntegrateParticleEnergy_BOUNDARY(double *U,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...IntegrateParticleEnergy_BOUNDARY";

  int exit_status                      = EXIT_FAILURE;
  int l                                = LARGE_NEGATIVE_INT;
  int l_mirror                         = LARGE_NEGATIVE_INT;
  int i_mirror_raw                     = LARGE_NEGATIVE_INT;
  int n_ghost                          = LARGE_NEGATIVE_INT;
  int nparticles                       = LARGE_NEGATIVE_INT;
  int index                            = LARGE_NEGATIVE_INT;

#include "pars_include.h"
  verbosity(1,fname,pars);

  nparticles = node_info[rank].nparticles;
/*                                                                           */
/*                                                                           */
/*                                                                           */
  n_ghost = node_info[rank].n_ghost;
  for (index=0;index<n_ghost;index++)
  {
    l = node_info[rank].ghost[index];
    species      = node_info[rank].species[l];
    printf(" here 2000:  l = %i species = %i \n",l,species);
    i_mirror_raw = node_info[rank].ghost_mirror[index];
    if (i_mirror_raw > LARGE_NEGATIVE_INT)
    {
      l_mirror = node_info[rank].inv_raw_index[i_mirror_raw];
      printf(" l_mirror = %i \n",l_mirror);
      U[l] = U[l_mirror];
    }
  }
/*                                                                           */
/*                                                                           */
/*                                                                           */
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
