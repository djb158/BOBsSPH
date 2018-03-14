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

#include "update_neighbour_nodes.h"

int UpdateNeighbourNodes(PARS *pars)
{
  extern int cluster_size;
  int tag1                             = LARGE_NEGATIVE_INT;
  int tag2                             = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;

  MPI_Status mpi_status;

  char   fname[]                       = "...UpdateNeighbourNodes";

#include "pars_include.h"
  verbosity(1,fname,pars);
  if (rank == 0)
  {
    tag1  = 1*(MAX_TAGS)+rank;
    if ( (MPI_Send(&NPARTICLES,1,MPI_INT,cluster_size,tag1,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    tag2  = 2*(MAX_TAGS)+rank;
    if ( (MPI_Send(&TOTAL_PARTICLES,1,MPI_INT,cluster_size,tag2,MPI_COMM_WORLD)) != MPI_SUCCESS)
    {
      printf(" %s(): unable to send packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  if (rank == cluster_size)
  {
    tag1  = 1*(MAX_TAGS)+0;
    if ( (MPI_Recv(&NPARTICLES,1,MPI_INT,0,tag1,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    tag2  = 2*(MAX_TAGS)+0;
    if ( (MPI_Recv(&TOTAL_PARTICLES,1,MPI_INT,0,tag2,MPI_COMM_WORLD,&mpi_status)) !=MPI_SUCCESS)
    {
      printf(" %s(): unable to receive packet \n",fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    } 
    pars[0].NPARTICLES      = NPARTICLES;
    pars[0].TOTAL_PARTICLES = TOTAL_PARTICLES;
  }
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  return exit_status;
}
