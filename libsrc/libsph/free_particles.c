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

#include "free_particles.h"
#include "assert.h"

void FreeDJB(void **x)
{
  assert(x);
  if (x != NULL)
  {
    free(*x);
    *x = NULL;
  }
}

int FreeParticles(PARTICLES **particles,PARS *pars,int N)
{
  char   fname[]                       = "...FreeParticles";

  int i                                = 0;
  int num                              = 0;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);
/*                                                                           */
/*                                                                           */
/*                                                                           */
  if (particles == NULL)
  {
    printf("Rank: %i %s(): **particles is NULL\n",rank,fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
/*                                                                           */
/*                                                                           */
/*                                                                           */
  if (*particles)
  {
  for (i=0;i<N;i++)
  {
    free((void *)(*particles)[0].nn[i]);  (*particles)[0].nn[i]      = NULL;
  }
  free((void *)(*particles)[0].nn_index);  (*particles)[0].nn_index  = NULL;
  free((void *)(*particles[0]).nn);        (*particles)[0].nn        = NULL; 
  free((void *)(*particles[0]).species);   (*particles)[0].species   = NULL;
  free((void *)(*particles[0]).raw_index); (*particles)[0].raw_index = NULL;
  free((void *)(*particles[0]).dvdt[2]);   (*particles)[0].dvdt[2]   = NULL;
  free((void *)(*particles[0]).dvdt[1]);   (*particles)[0].dvdt[1]   = NULL;
  free((void *)(*particles[0]).dvdt[0]);   (*particles)[0].dvdt[0]   = NULL;
  free((void *)(*particles[0]).v[2]);      (*particles)[0].v[2]      = NULL;
  free((void *)(*particles[0]).v[1]);      (*particles)[0].v[1]      = NULL;
  free((void *)(*particles[0]).v[0]);      (*particles)[0].v[0]      = NULL;
  free((void *)(*particles[0]).x[2]);      (*particles)[0].x[2]      = NULL;
  free((void *)(*particles[0]).x[1]);      (*particles)[0].x[1]      = NULL;
  free((void *)(*particles[0]).x[0]);      (*particles)[0].x[0]      = NULL;
  free((void *)(*particles[0]).divV);      (*particles)[0].divV      = NULL;
  free((void *)(*particles[0]).dUdt);      (*particles)[0].dUdt      = NULL;
  free((void *)(*particles[0]).U);         (*particles)[0].U         = NULL;
  free((void *)(*particles[0]).rho);       (*particles)[0].rho       = NULL;
  free((void *)(*particles[0]).p);         (*particles)[0].p         = NULL;
  free((void *)(*particles[0]).h);         (*particles)[0].h         = NULL;
  free((void *)(*particles[0]).m);         (*particles)[0].m         = NULL;
  free((void *)(*particles[0]).dvdt);      (*particles)[0].dvdt      = NULL;
  free((void *)(*particles[0]).v);         (*particles)[0].v         = NULL;
  free((void *)(*particles[0]).x);         (*particles)[0].x         = NULL;
  free((void *)*particles);                (*particles)              = NULL;
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
