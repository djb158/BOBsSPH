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

#include "sph_main.h"
#include "pars.h"
#include "particles.h"
#include "numeric_constants.h"

void verbosity(int k, char fname[],PARS *pars)
{
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"

  switch (VERBOSITY)
  {
    case 0:
      break;
    case 1:
      if (k == 1)
      {
        printf(" Rank: %i entering %s \n",rank,fname);
      }
      if (k == 2)
      {
        printf(" Rank: %i leaving  %s \n\n",rank,fname);
      }
      break;
    case 2:
      if ( (k == 1) || (k == 3) )
      {
        printf(" Rank: %i entering %s \n",rank,fname);
      }
      if ( (k == 2) || (k == 4) )
      {
        printf(" Rank: %i leaving  %s \n\n",rank,fname);
      }
      break;
    default:
      break;
  }

RETURN:
  return;
}
