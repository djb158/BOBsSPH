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

#include "copy_h.h"

int CopyH(PARTICLES *particles_from,PARTICLES *particles_to,PARS *pars)
{
  char   fname[]                       = "...CopyH";

  int exit_status                      = EXIT_FAILURE;
  int l                                = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  for (l=0;l<NPARTICLES;l++)
  {
    particles_to[0].h[l]         = particles_from[0].h[l];
    particles_to[0].m[l]         = particles_from[0].m[l];
    particles_to[0].x[0][l]      = particles_from[0].x[0][l];
    particles_to[0].x[1][l]      = particles_from[0].x[1][l];
    particles_to[0].x[2][l]      = particles_from[0].x[2][l];
    particles_to[0].v[0][l]      = particles_from[0].v[0][l];
    particles_to[0].v[1][l]      = particles_from[0].v[1][l];
    particles_to[0].v[2][l]      = particles_from[0].v[2][l];
    particles_to[0].dvdt[0][l]   = particles_from[0].dvdt[0][l];
    particles_to[0].dvdt[1][l]   = particles_from[0].dvdt[1][l];
    particles_to[0].dvdt[2][l]   = particles_from[0].dvdt[2][l];
    particles_to[0].p[l]         = particles_from[0].p[l];
    particles_to[0].U[l]         = particles_from[0].U[l];
    particles_to[0].dUdt[l]      = particles_from[0].dUdt[l];
    particles_to[0].divV[l]      = particles_from[0].divV[l];
    particles_to[0].rho[l]       = particles_from[0].rho[l];
    particles_to[0].species[l]   = particles_from[0].species[l];
    particles_to[0].raw_index[l] = particles_from[0].raw_index[l];
  }

  exit_status = EXIT_SUCCESS;

RETURN:

  verbosity(2,fname,pars);
  return exit_status;
}
