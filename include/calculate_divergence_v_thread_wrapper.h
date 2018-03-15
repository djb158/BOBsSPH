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

#ifndef BOBSSPH_CALCULATE_DIVERGENCE_V_THREAD_WRAPPER_H
#define BOBSSPH_CALCULATE_DIVERGENCE_V_THREAD_WRAPPER_H

#include "sph_main.h"
#include <pthread.h>
#include "pars.h"
#include "particles.h"
#include "numeric_constants.h"
#include "thread_data.h"

extern void verbosity(int k, char fname[],PARS *pars);
extern void *CalculateDivergenceV(void *dtd);

int CalculateDivergenceV_thread_wrapper(PARTICLES *particles,PARTICLES *x_particles,PARS *pars);

#endif
