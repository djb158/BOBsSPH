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

#ifndef BOBSSPH_SPH_MAIN_H
#define BOBSSPH_SPH_MAIN_H

#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>
#include <math.h>
#include "sph_types.h"
#include "mpi.h"
#include "node_info.h"

#define BURN_TRIGGER_LEFT  ((EXIT_FAILURE + EXIT_SUCCESS)*100)
#define BURN_TRIGGER_RIGHT ((EXIT_FAILURE + EXIT_SUCCESS)*200)
#define BURN_TRIGGER_LEFT_AND_RIGHT ((EXIT_FAILURE + EXIT_SUCCESS)*300)
#define H_PTS              (100)
#define NEIGHBOUR_SEARCH_DEPTH (2)
#define NUMBER_OF_INTS  (7)
#define NUMBER_OF_DOUBLES  (17)

#define MAX_CHARS (1024)
#define MAX_TAGS  (100)
#define Free_sph(ptr) do \
                   { if (ptr) \
                     { (void)free((char *)(ptr));\
                       (ptr) = NULL;\
                     }\
                   } while (0)

typedef enum {FALSE,TRUE} logical;

#endif
