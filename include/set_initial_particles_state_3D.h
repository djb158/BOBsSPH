/*----------------------------------------------------------------------------|
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

#ifndef BOBSSPH_SET_INITIAL_PARTICLE_STATE_3D_H
#define BOBSSPH_SET_INITIAL_PARTICLE_STATE_3D_H

#include "sph_main.h"
#include "pars.h"
#include "particles.h"
#include "numeric_constants.h"
#include "ids.h"
#include "mask_defs.h"

typedef struct
{
  double **x;
  double *rho;
  double *U;
  int *raw_index;
}RAW_PARTICLE;

extern double Minimum_double(double, double);
extern double Maximum_double(double, double);
extern int Maximum_int(int a, int b);
extern int UpdateKernel(PARTICLES *particles,PARS *pars);
extern PARTICLES *ReadParticleInfo(PARS *pars,int particles_num);
extern void verbosity(int k, char fname[],PARS *pars);
extern PARTICLES *CreateParticles(int N,PARS *pars);
extern int FreeParticles(PARTICLES **particles,PARS *pars,int N);
extern  int GetNodeInfoStruct(int cluster_size,char *rank_name,double delta,PARS *pars);
extern  int EquationOfState(PARTICLES *particles,PARS *pars);
extern IDS *SetParticleID_3D(PARS *pars, PARTICLES *particles, double x, double y, double z);

PARTICLES *SetInitialParticlesState3D(PARS *pars,int particles_num,char *rank_name);

#endif /* BOBSSPH_SET_INITIAL_PARTICLE_STATE_3D_H */
