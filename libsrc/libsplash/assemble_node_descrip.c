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

#include "assemble_node_descrip.h"

NODE_DESCRIP *Assemble_NODE_DESCRIP(PARS *pars,int cluster_size)
{
  extern NODE_INFO *node_info;

  char fname[]                         = "...Assemble_NODE_DESCRIP";

  int exit_status                      = EXIT_FAILURE;
  int i                                = LARGE_NEGATIVE_INT;

  NODE_DESCRIP *node_descrip           = NULL;

#include "pars_include.h"
  verbosity(1,fname,pars);

  node_descrip = (NODE_DESCRIP *)calloc(cluster_size+1,sizeof(NODE_DESCRIP));

  for (i=0;i<cluster_size+1;i++)
  {
    sprintf((char *)node_descrip[i].node_name,"%32s",node_info[i].node_name);
    sprintf((char *)node_descrip[i].node_number,"%4i            ",i);
  }

RETURN:
  verbosity(2,fname,pars);
  return node_descrip;
}
