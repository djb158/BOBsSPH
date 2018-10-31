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

#include "equation_of_state.h"

int EquationOfState(PARTICLES *particles,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...EquationOfState";

  int exit_status                      = EXIT_FAILURE;
  int i                                = 0;
  int nparticles                       = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  for (i=0;i<NPARTICLES;i++)
  {
    particles->p[i] = (GAMMA-1.0)*(particles->rho[i])*(particles->U[i]);
  }


  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
