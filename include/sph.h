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

#ifndef BOBSSPH_SPH_H
#define BOBSSPH_SPH_H

#include "sph_main.h"
#include "pars.h"
#include "particles.h"
#include "particle.h"
#include "node_descrip.h"
#include "pbob.h"
#include "numeric_constants.h"

extern  int ForceBoundary(PARTICLES *particles_3,PARS *pars);
extern  int CheckBoundaryPenetration(double **x_3,double **v_3,PARS *pars);
extern  int WriteNodeInfo(PARS *pars);
extern  int WriteParticleInfo(PARTICLES *particles,PARS *pars,int particles_num,const char *a_test);
extern  int SetBurnMark(PARTICLES *particles,PARS *pars);
extern  void Sort(double a[],int b[], int n);
extern PARTICLES *SetInitialParticlesState1D(PARS *pars,int particles_num,char *rank_name);
extern PARTICLES *SetInitialParticlesState2D(PARS *pars,int particles_num,char *rank_name);
extern PARTICLES *SetInitialParticlesState3D(PARS *pars,int particles_num,char *rank_name);
extern  double **GetParticlePosition(PARTICLES *particles,PARS *pars);
extern  double **GetParticleAcceleration(PARTICLES *particles,PARS *pars);
extern  double *GetParticleEnergy(PARTICLES *particles,PARS *pars);
extern  double *GetParticleEnergyDeriv(PARTICLES *particles,PARS *pars);
extern  double **GetParticleVelocity(PARTICLES *particles,PARS *pars);
extern  double **IntegrateParticleVelocity_INTERIOR(double **x_0,double **v_0,double dt,PARS *pars);
extern  int IntegrateParticleVelocity_BOUNDARY(double **x_0,PARS *pars);
extern  double **IntegrateParticleAcceleration_INTERIOR(double **vel_x,double **accel_x,double dt,PARS *pars);
extern  int IntegrateParticleAcceleration_BOUNDARY(double **vel_x,PARS *pars);
extern  double *IntegrateParticleEnergy_INTERIOR(double *U_0,double *dUdt_0,double dt,PARS *pars);
extern  int IntegrateParticleEnergy_BOUNDARY(double *U_0,PARS *pars);
extern  int SetParticlePosition(PARTICLES *particles,double **x,PARS *pars);
extern  int SetParticleVelocity(PARTICLES *particles,double **v,PARS *pars);
extern  int SetParticleDensity_BOUNDARY(PARTICLES *particles,PARS *pars);
extern  int SetParticleEnergy(PARTICLES *particles,double *U,PARS *pars);
extern  int EquationOfState(PARTICLES *particles,PARS *pars);
extern  int SetParticleAcceleration(PARTICLES *particles,double **a,PARS *pars);
extern  int SetParticleEnergyDeriv(PARTICLES *particles,double *dUdt,PARS *pars);
extern  double **CalculateParticleAcceleration_INTERIOR_thread_wrapper(PARTICLES *particles,PARTICLES *x_particles,PARS *pars);
extern  int CalculateParticleAcceleration_BOUNDARY(double **a,PARS *pars);
extern  double *CalculateParticleEnergyDeriv_INTERIOR_thread_wrapper(PARTICLES *particles,PARTICLES *x_particles,PARS *pars);
extern  int SetParticleDensity_INTERIOR_thread_wrapper(PARTICLES *particles,PARTICLES *x_particles,PARS *pars);
extern  int CalculateParticleEnergyDeriv_BOUNDARY(double *dUdt,PARS *pars);
extern  void FreeMatrix(double **a, int N,PARS *pars);
extern  int FreeParticles(PARTICLES **particles,PARS *pars,int N);
extern  int CalculateDivergenceV_thread_wrapper(PARTICLES *particles,PARTICLES *x_particles,PARS *pars);
extern  int UpdateKernel(PARTICLES *particles,PARS *pars);
extern  int ReIndexDownSend(int burn_status,PARTICLES *particles_3, PARTICLES *particles_4,MPI_Comm *comm_down,PARS *pars);
extern  int ReIndexDownRecv(PARTICLES *particles_3, PARTICLES *particles_4,MPI_Comm *comm_down,PARS *pars);
extern  int SynchroniseRankInfo(PARS *pars);
extern  int CopyH(PARTICLES *particles_from,PARTICLES *particles_to,PARS *pars);
extern  logical ContainsString(char *string1,char *string2);
extern  char *CopyAfterEqual(char *target,  char *source);
extern  PARS *GetPars(int argc, char *argv[],int rank);
extern int UpdateRij(PARTICLES *particles,PARS *pars);
extern int CheckForNaN(PARTICLES *particles,PARS *pars);
extern int WriteParticle(PARTICLE *particle,int unique_particles,int rank,char *out_dir,int time_slice);
extern int FreeNodeInfo(int cluster_size,PARS *pars);
extern PARTICLE *Assemble_PARTICLE(PARTICLES *particles,PARS *pars,int *unique_particles,int time_slice,double **vorticity);
extern PBOB *Assemble_PBOB(PARS *pars,double time,int cluster_size);
extern NODE_DESCRIP *Assemble_NODE_DESCRIP(PARS *pars,int cluster_size);
extern int WritePbobNodeDescrip(PBOB *pbob,NODE_DESCRIP *node_descrip,char *out_dir,int rank,int time_slice);
extern PARTICLES *Push_and_Pull_N_and_X(PARTICLES *particles,PARS *pars);
extern int Push_and_Pull_divV(PARTICLES *particles,PARS *pars,PARTICLES *x_particles);
extern int Push_and_Pull_H(PARTICLES *particles,PARS *pars,PARTICLES *x_particles);
extern int Push_and_Pull_P(PARTICLES *particles,PARS *pars,PARTICLES *x_particles);
extern int Push_and_Pull_RHO(PARTICLES *particles,PARS *pars,PARTICLES *x_particles);
extern int Push_and_Pull_U(PARTICLES *particles,PARS *pars,PARTICLES *x_particles);
extern int Push_and_Pull_V(PARTICLES *particles,PARS *pars,PARTICLES *x_particles);
extern int Set_N(PARS *pars);
extern PARTICLES *CreateParticles(int N, PARS *pars);
extern int UpdateNeighbourNodes(PARS *pars);
extern int FreeParticlesNN(PARTICLES *particles,PARS *pars,int N);
extern double **CalculateParticleVorticity(PARTICLES *particles,PARTICLES *x_particles,PARS *pars);
extern int SynchroniseNodeInfo(PARS *pars);

NODE_INFO *node_info;
int cluster_size;

#endif /* BOBSSPH_SPH_H */
