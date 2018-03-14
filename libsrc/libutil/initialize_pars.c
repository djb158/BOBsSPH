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

#include "initialize_pars.h"

int InitializePars(PARS *pars)
{
  char fname[]                         = "...InitiializePars";

  int exit_status                      = EXIT_FAILURE;

  memset(pars[0].out_dir,' ',MAX_CHARS-1);
  strcat(pars[0].out_dir,(const char *)"\0");

  memset(pars[0].prefix,' ',MAX_CHARS-1);
  strcat((char *)pars[0].prefix,(const char *)"\0");

  memset(pars[0].ascii_header,' ',3200-1);
  strcat((char *)pars[0].ascii_header,(const char *)"\0");

  memset(pars[0].short_title,' ',80-1);
  strcat((char *)pars[0].short_title,(const char *)"\0");

  memset(pars[0].length_units,' ',16);
  strcat((char *)pars[0].length_units,(const char *)"\0");

  memset(pars[0].time_units,' ',16);
  strcat((char *)pars[0].time_units,(const char *)"\0");

  memset(pars[0].mass_units,' ',16);
  strcat((char *)pars[0].mass_units,(const char *)"\0");

  memset(pars[0].internal_energy_units,' ',16);
  strcat((char *)pars[0].internal_energy_units,(const char *)"\0");

  memset(pars[0].sph_git_commit_hash,' ',40);
  strcat((char *)pars[0].sph_git_commit_hash,(const char *)"\0");

  pars[0].GRAVITY               = -1.0;
  pars[0].X0                    = -1.0;
  pars[0].X1                    = -1.0;
  pars[0].Y0                    = -1.0;
  pars[0].Y1                    = -1.0;
  pars[0].Z0                    = -1.0;
  pars[0].Z1                    = -1.0;
  pars[0].ACCURACY              = -1.0;
  pars[0].ALPHA                 = -1.0;
  pars[0].GAMMA                 = -1.0;
  pars[0].BETA                  = -1.0;
  pars[0].ETA                   = -1.0;
  pars[0].EPSILON               = -1.0;
  pars[0].G1                    = -1.0;
  pars[0].G2                    = -1.0;
  pars[0].D                     = -1.0;
  pars[0].H0                    = -1.0;
  pars[0].NN_EPS                = -1.0;
  pars[0].KAPPA                 = -1.0;
  pars[0].PARTICLE_MASS         = -1.0;
  pars[0].OFFSET                = -1.0;
  pars[0].KERNEL_WIDTH          = -1.0;
  pars[0].NEIGHBOUR_THREADS     = -1;
  pars[0].COMPUTE_THREADS       = -1;
  pars[0].N_STEPS               = -1;
  pars[0].TIME_STEPS_TO_WRITE   = -1;
  pars[0].RESTART               = -1;
  pars[0].args_defined          = -1;
  pars[0].KERNEL_ID             = -1;
  pars[0].DIMENSIONS            = -1;
  pars[0].PARTICLES_IN_X        = -1;
  pars[0].PARTICLES_IN_Y        = -1;
  pars[0].PARTICLES_IN_Z        = -1;
  pars[0].PARTICLES_IN_Z_H      = -1;
  pars[0].NPARTICLES            = -1;
  pars[0].NPARTICLES_EXTRA      = -1;
  pars[0].N_CENTRE              = -1;
  pars[0].NN_K                  = -1;
  pars[0].ZERO                  = -1;
  pars[0].ZERO_H                = -1;
  pars[0].CENTRE_POINT          = -1;
  pars[0].EXTRA                 = -1;
  pars[0].rank                  = -1;
  pars[0].TOTAL_PARTICLES       = -1;
  pars[0].TOTAL_PARTICLES_GUESS = -1;
  pars[0].VERBOSITY             = -1;

  exit_status = EXIT_SUCCESS;

RETURN:

  return  exit_status;
}
