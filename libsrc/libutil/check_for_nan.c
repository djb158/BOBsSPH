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

#include "check_for_nan.h"

int CheckForNaN(PARTICLES *particles,PARS *pars)
{
  extern NODE_INFO *node_info;

  char fname[]                         = "...CheckForNaN";

  int exit_status                      = EXIT_FAILURE;
  int l                                = 0;
  int nparticles                       = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  if ( (particles == NULL) || (node_info == NULL) )
  {
     exit_status = EXIT_FAILURE;
     goto RETURN;
  }
  nparticles = node_info[rank].nparticles;
  for (l=0;l<nparticles;l++)
  { 
    if (is_nan_or_inf(particles[0].m[l],(char *)"m",l) == EXIT_FAILURE)             goto RETURN;
    if (is_nan_or_inf(particles[0].h[l],(char *)"h",l) == EXIT_FAILURE)             goto RETURN;
    if (is_nan_or_inf(particles[0].x[0][l],(char *)"x[0]",l) == EXIT_FAILURE)       goto RETURN;
    if (is_nan_or_inf(particles[0].x[1][l],(char *)"x[1]",l) == EXIT_FAILURE)       goto RETURN;
    if (is_nan_or_inf(particles[0].x[2][l],(char *)"x[2]",l) == EXIT_FAILURE)       goto RETURN;
    if (is_nan_or_inf(particles[0].v[0][l],(char *)"v[0]",l) == EXIT_FAILURE)       goto RETURN;
    if (is_nan_or_inf(particles[0].v[1][l],(char *)"v[1]",l) == EXIT_FAILURE)       goto RETURN;
    if (is_nan_or_inf(particles[0].v[2][l],(char *)"v[2]",l) == EXIT_FAILURE)       goto RETURN;
    if (is_nan_or_inf(particles[0].dvdt[0][l],(char *)"dvdt[0]",l) == EXIT_FAILURE) goto RETURN;
    if (is_nan_or_inf(particles[0].dvdt[1][l],(char *)"dvdt[1]",l) == EXIT_FAILURE) goto RETURN;
    if (is_nan_or_inf(particles[0].dvdt[2][l],(char *)"dvdt[2]",l) == EXIT_FAILURE) goto RETURN;
    if (is_nan_or_inf(particles[0].p[l],(char *)"p",l) == EXIT_FAILURE)             goto RETURN;
    if (is_nan_or_inf(particles[0].rho[l],(char *)"rho",l) == EXIT_FAILURE)         goto RETURN;
    if (is_nan_or_inf(particles[0].U[l],(char *)"U",l) == EXIT_FAILURE)             goto RETURN;
    if (is_nan_or_inf(particles[0].dUdt[l],(char *)"dUdt",l) == EXIT_FAILURE)       goto RETURN;
    if (is_nan_or_inf(particles[0].divV[l],(char *)"divV",l) == EXIT_FAILURE)       goto RETURN;
  }
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);

  return exit_status;
}
