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

#include "integrate_particle_velocity_boundary.h"

int IntegrateParticleVelocity_BOUNDARY(double **x,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...IntegrateParticleVelocity_BOUNDARY";

  int l                                = 0;
  int exit_status                      = EXIT_FAILURE;
  int index                            = 0;
  int n_ghost                          = 0;
  int l_mirror                         = 0;
  int i_mirror_raw                     = 0;
  int nparticles                       = 0;
  int n_boundary                       = 0;
  int species                          = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  nparticles = node_info[rank].nparticles;
  n_boundary = node_info[rank].n_boundary;

  for (index=0;index<n_boundary;index++)
  {
    l = node_info[rank].boundary[index];
    species = node_info[rank].species[l];
    printf(" here 1000 species = %i \n",species);

    switch(species)
    {
      case 2049:
        x[0][l] = X0;
        break;
/*                                                                           */
      case 2050:
        x[0][l] = X1;
        break;
/*                                                                           */
      case 2051:
        x[2][l] = Z0;
        break;
/*                                                                           */
      case 2052:
        x[2][l] = Z1;
        break;
/*                                                                           */
      case 2053:
        x[1][l] = Y0;
        break;
/*                                                                           */
      case 2054:
        x[1][l] = Y1;
        break;
/*                                                                           */
      case 2055:
        x[0][l] = X0;
        x[2][l] = Z0;
        break;
/*                                                                           */
      case 2056:
        x[0][l] = X0;
        x[2][l] = Z1;
        break;
/*                                                                           */
      case 2057:
        x[0][l] = X1;
        x[2][l] = Z0;
        break;
/*                                                                           */
      case 2058:
        x[0][l] = X1;
        x[2][l] = Z1;
        break;
/*                                                                           */
      case 2059:
        x[0][l] = X1;
        x[1][l] = Y0;
        break;
/*                                                                           */
      case 2060:
        x[0][l] = X1;
        x[1][l] = Y0;
        break;
/*                                                                           */
      case 2061:
        x[0][l] = X0;
        x[1][l] = Y1;
        break;
/*                                                                           */
      case 2062:
        x[0][l] = X1;
        x[1][l] = Y1;
        break;
/*                                                                           */
      case 2063:
        x[1][l] = Y0;
        x[2][l] = Z0;
        break;
/*                                                                           */
      case 2064:
        x[1][l] = Z0;
        x[2][l] = Y1;
        break;
/*                                                                           */
      case 2065:
        x[1][l] = Z1;
        x[2][l] = Y0;
        break;
/*                                                                           */
      case 2066:
        x[1][l] = Z1;
        x[2][l] = Y1;
        break;
/*                                                                           */
      case 2067:
        x[0][l] = X0;
        x[1][l] = Y0;
        x[2][l] = Z0;
        break;
/*                                                                           */
      case 2068:
        x[0][l] = X1;
        x[1][l] = Y0;
        x[2][l] = Z0;
       break;
/*                                                                           */
      case 2069:
        x[0][l] = X0;
        x[1][l] = Y0;
        x[2][l] = Z1;
        break;
/*                                                                           */
      case 2070:
        x[0][l] = X1;
        x[1][l] = Y0;
        x[2][l] = Z1;
        break;
/*                                                                           */
      case 2071:
        x[0][l] = X0;
        x[1][l] = Y1;
        x[2][l] = Z0;
        break;
/*                                                                           */
      case 2072:
        x[0][l] = X0;
        x[1][l] = Y1;
        x[2][l] = Z1;
        break;
/*                                                                           */
      case 2073:
        x[0][l] = X1;
        x[1][l] = Y1;
        x[2][l] = Z0;
        break;
/*                                                                           */
      case 2074:
        x[0][l] = X1;
        x[1][l] = Y1;
        x[2][l] = Z1;
        break;
/*                                                                           */
      default:
      printf("Rank: %i %s(): boundary, this should never happen species = %i, -aborting()\n",rank,fname,species);
      exit_status = EXIT_FAILURE;
      goto RETURN;
        break;
    }
  }

  n_ghost = node_info[rank].n_ghost;
  for (index=0;index<n_ghost;index++)
  {
    l            = node_info[rank].ghost[index];
    species      = node_info[rank].species[l];
    i_mirror_raw = node_info[rank].ghost_mirror[index];
    l_mirror     = node_info[rank].inv_raw_index[i_mirror_raw];

    switch(species)
    {
/*                                                                           */
/*                 LHS boundary                                              */
/*                                                                           */
      case 1025:
        x[0][l]  =  X0 - (x[0][l_mirror] - X0);
        x[1][l]  =        x[1][l_mirror];
        x[2][l]  =        x[2][l_mirror];
        break;
/*                                                                           */
/*                 RHS boundary                                              */
/*                                                                           */
      case 1026:
        x[0][l]  =  X1 - (x[0][l_mirror] - X1);
        x[1][l]  =        x[1][l_mirror];
        x[2][l]  =        x[2][l_mirror];
        break;
/*                                                                           */
/*                 BOTTOM boundary                                           */
/*                                                                           */
      case 1027:
        x[0][l]  =        x[0][l_mirror];
        x[1][l]  =        x[1][l_mirror];
        x[2][l]  =  Z0 - (x[2][l_mirror] - Z0);
        break;
/*                                                                           */
/*                 TOP boundary                                              */
/*                                                                           */
      case 1028:
        x[0][l]  =        x[0][l_mirror];
        x[1][l]  =        x[1][l_mirror];
        x[2][l]  =  Z1 - (x[2][l_mirror] - Z1);
        break;
/*                                                                           */
/*                 FRONT boundary                                            */
/*                                                                           */
      case 1029:
        x[0][l]  =        x[0][l_mirror];
        x[1][l]  =  Y0 - (x[1][l_mirror] - Y0);
        x[2][l]  =        x[2][l_mirror];
        break;
/*                                                                           */
/*                 BACK boundary                                             */
/*                                                                           */
      case 1030:
        x[0][l]  =        x[0][l_mirror];
        x[1][l]  =  Y1 - (x[1][l_mirror] - Y1);
        x[2][l]  =        x[2][l_mirror];
        break;
    }
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
