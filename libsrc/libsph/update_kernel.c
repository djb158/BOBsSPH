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

#include "update_kernel.h"

int UpdateKernel(PARTICLES *particles, PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...UpdateKernel";

  double rho_i                         = 0.0;
  double m_i                           = 0.0;

  int exit_status                       = EXIT_FAILURE;
  int i                                = 0;
  int nparticles                       = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  nparticles = node_info[rank].nparticles;

  if (DIMENSIONS == 1)
  {
    for (i=0;i<nparticles;i++)
    {
      rho_i = particles[0].rho[i]; 
      m_i   = particles[0].m[i]; 
      particles[0].h[i] = KERNEL_SUPPORT*m_i/rho_i;
    }
  }
  if (DIMENSIONS == 2)
  {
    for (i=0;i<nparticles;i++)
    {
      rho_i = particles[0].rho[i]; 
      m_i   = particles[0].m[i]; 
      particles[0].h[i] = 1.00*sqrt((double)NN_K*PARTICLE_MASS/(KERNEL_SUPPORT_SQUARED*M_PI*particles[0].rho[i]));
    }
  }
  if (DIMENSIONS == 3)
  {
    for (i=0;i<nparticles;i++)
    {
      rho_i = particles[0].rho[i]; 
      m_i   = particles[0].m[i]; 
      particles[0].h[i] = 1.00*pow(3.0*(double)NN_K*PARTICLE_MASS/(FOUR_PI*KERNEL_SUPPORT_CUBED*particles[0].rho[i]),ONE_THIRD);
    }
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
