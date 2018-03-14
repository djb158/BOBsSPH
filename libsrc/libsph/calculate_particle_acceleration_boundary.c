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

#include "calculate_particle_acceleration_boundary.h"

int CalculateParticleAcceleration_BOUNDARY(double **a,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...CalculateParticleAcceleration_BOUNDARY";

  int exit_status                      = EXIT_FAILURE;
  int l                                = 0;
  int l_mirror                         = 0;
  int i_mirror_raw                     = 0;
  int q                                = 0;
  int b                                = 0;
  int c                                = 0;
  int n_boundary                       = 0;
  int n_ghost                          = LARGE_NEGATIVE_INT;
  int index                            = 0;
  int nparticles                       = 0;
  int species                          = 0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  nparticles = node_info[rank].nparticles;

  n_ghost = node_info[rank].n_ghost;
  for (index=0;index<n_ghost;index++)
  {
    l            = node_info[rank].ghost[index];
    species      = node_info[rank].species[l];
    i_mirror_raw = node_info[rank].ghost_mirror[index];
    l_mirror     = node_info[rank].inv_raw_index[i_mirror_raw];
/*                                                                           */
/*                 LHS + RHS boundary                                        */
/*                                                                           */
    switch(species)
    {
      case 1025: case 1026:
        a[0][l]  = -a[0][l_mirror];
        a[1][l]  =  a[1][l_mirror];
        a[2][l]  =  a[2][l_mirror];
        break;
/*                                                                           */
/*                 TOP + Bottom boundary                                     */
/*                                                                           */
      case 1027: case 1028:
        a[0][l]  =  a[0][l_mirror];
        a[1][l]  =  a[1][l_mirror];
        a[2][l]  = -a[2][l_mirror];
        break;
/*                                                                           */
/*                 front + back boundary                                     */
/*                                                                           */
      case 1029: case 1030:
        a[0][l]  =  a[0][l_mirror];
        a[1][l]  = -a[1][l_mirror];
        a[2][l]  =  a[2][l_mirror];
        break;
      default:
        printf("Rank: %i %s(): ghost, this should never happen species = %i, -aborting()\n",rank,fname,species);
        exit_status = EXIT_FAILURE;
        goto RETURN;
        break;
    }
  }

  n_boundary = node_info[rank].n_boundary;
  for (index=0;index<n_boundary;index++)
  {
    l       = node_info[rank].boundary[index];
    species = node_info[rank].species[l];
    switch (species)
    {
      case 2049: case 2050:
        a[0][l] = 0.0;
        break;
      case 2051: case 2052:
        a[2][l] = 0.0;
        break;
      case 2053: case 2054:
        a[1][l] = 0.0;
        break;
      case 2055: case 2056: case 2057: case 2058:
        a[0][l] = 0.0;
        a[2][l] = 0.0;
        break;
      case 2059: case 2060: case 2061: case 2062:
        a[0][l] = 0.0;
        a[1][l] = 0.0;
        break;
      case 2063: case 2064: case 2065: case 2066:
        a[1][l] = 0.0;
        a[2][l] = 0.0;
        break;
      case 2067: case 2068: case 2069: case 2070: case 2071: case 2072: case 2073: case 2074:
        a[0][l] = 0.0;
        a[1][l] = 0.0;
        a[2][l] = 0.0;
        break;
      default:
        printf("Rank: %i %s(): boundary, this should never happen species = %i, -aborting()\n",rank,fname,species);
        exit_status = EXIT_FAILURE;
        goto RETURN;
        break;
    }
  }
  exit_status  = EXIT_SUCCESS;

RETURN:
  
  verbosity(2,fname,pars);
  return exit_status;
}
