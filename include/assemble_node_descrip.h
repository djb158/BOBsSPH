/*----------------------------------------------------------------------------|
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
#ifndef BOBSSPH_ASSEMBLE_NODE_DESCRIP_H
#define BOBSSPH_ASSEMBLE_NODE_DESCRIP_H

#include <string.h>
#include "sph_main.h"
#include "sph_types.h"
#include "pars.h"
#include "node_descrip.h"
#include "numeric_constants.h"

extern void verbosity(int k, char fname[],PARS *pars);

NODE_DESCRIP *Assemble_NODE_DESCRIP(PARS *pars,int cluster_size);

#endif 
