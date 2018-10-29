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

#include "set_initial_particles_state_2D.h"

PARTICLES *SetInitialParticlesState2D(PARS *pars,int particles_num,char *rank_name)
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  FILE *out_ptr                        = NULL;

  PARTICLES *particles                 = NULL;
  RAW_PARTICLE *raw_particle           = NULL;
  IDS *ids                             = NULL;

  char   fname[]                       = "...SetInitialParticlesState2D";

  int indx                             = 0;
  int i                                = 0;
  int j                                = 0;
  int k                                = 0;
  int offset                           = 0;
  int exit_status                      = EXIT_FAILURE;
  int l0                               = 0;
  int l1                               = 0;
  int l2                               = 0;
  int l3                               = 0;
  int l4                               = 0;
  int l                                = 0;
  int m                                = 0;
  int m0                               = 0;
  int m1                               = 0;
  int raw_index                        = 0;
  int i_rank                           = 0;
  int i_off                            = 0;
  int i0                               = 0;
  int i1                               = 0;
  int i_raw                            = 0;
  int use_lhs                          = 0;
  int nparticles                       = 0;
  int total_particles                  = 0;
  int t                                = 0;
  int found                            = 0;
  int l_mirror                         = 0;
  int species                          = LARGE_NEGATIVE_INT;
  int species_basic                    = LARGE_NEGATIVE_INT;


  double d_l                           = 0.0;
  double d_r                           = 0.0;
  double min_r                         = 0.0;
  double max_l                         = 0.0;
  double x_l                           = 0.0;
  double x_r                           = 0.0;
  double z_0                           = 0.0;
  double dist                          = 0.0;
  double x                             = LARGE_NEGATIVE_DOUBLE;
  double y                             = LARGE_NEGATIVE_DOUBLE;
  double z                             = LARGE_NEGATIVE_DOUBLE;
  double x0                            = 0.0;
  double x1                            = 0.0;
  double x2                            = 0.0;
  double z0                            = 0.0;
  double z1                            = 0.0;
  double z2                            = 0.0;
  double z3                            = 0.0;
  double y0                            = 0.0;
  double y1                            = 0.0;
  double y2                            = 0.0;
  double d1                            = 0.0;
  double d2                            = 0.0;
  double h                             = 0.0;
  double dx                            = 0.0;
  double dx2                           = 0.0;
  double RHO_l                         = 0.0;
  double RHO_r                         = 0.0;
  double PRES_l                        = 0.0;
  double PRES_r                        = 0.0;
  double U_l                           = 0.0;
  double U_r                           = 0.0;
  double *X                            = NULL;
  double *Z                            = NULL;
  double d                             = 0.0;
  double KK                            = 2.0;
  double dz                            = 0.0;
  double dz2                           = 0.0;

#include "pars_include.h"
  verbosity(1,fname,pars);

  switch (RESTART)
  {
    case 0:
  raw_particle               = (RAW_PARTICLE *)calloc(1,sizeof(RAW_PARTICLE));
  raw_particle[0].x          = (double **)calloc(3,sizeof(double *));
  raw_particle[0].x[0]       = (double *)calloc(TOTAL_PARTICLES_GUESS,sizeof(double));
  raw_particle[0].x[1]       = (double *)calloc(TOTAL_PARTICLES_GUESS,sizeof(double));
  raw_particle[0].x[2]       = (double *)calloc(TOTAL_PARTICLES_GUESS,sizeof(double));
  raw_particle[0].rho        = (double *)calloc(TOTAL_PARTICLES_GUESS,sizeof(double));
  raw_particle[0].U          = (double *)calloc(TOTAL_PARTICLES_GUESS,sizeof(double));
  raw_particle[0].raw_index  = (int *)calloc(TOTAL_PARTICLES_GUESS,sizeof(int));
  for (i=0;i<TOTAL_PARTICLES_GUESS;i++)
  {
    raw_particle[0].x[0][i]       = 0.0;
    raw_particle[0].x[1][i]       = 0.0;
    raw_particle[0].x[2][i]       = 0.0;
    raw_particle[0].rho[i]        = 0.0;
    raw_particle[0].U[i]          = 0.0;
    raw_particle[0].raw_index[i]  = LARGE_NEGATIVE_INT;
  }
/*                                                                            */
/*                 left state                                                 */
/*                                                                            */
  RHO_l       = 1.00;
  U_l         = 2.50;
  PRES_l      = (GAMMA-1.0)*RHO_l*U_l;
/*                                                                            */
/*                 right state                                                */
/*                                                                            */
  RHO_r       = 0.25;
  U_r         = 1.795;
  PRES_r      = (GAMMA-1.0)*RHO_r*U_r;
/*                                                                            */
/*                                                                            */
/*                                                                            */
  X   = (double *)calloc(PARTICLES_IN_X,sizeof(double));
  Z   = (double *)calloc(PARTICLES_IN_Z,sizeof(double));
  dz  = (Z1-Z0)/(double)(PARTICLES_IN_Z-2*ZERO-1);
  dx  = 1.0/(double)(CENTRE_POINT-ZERO);
  dx2 = 1.0/(double)(PARTICLES_IN_X-ZERO/2-CENTRE_POINT);
  dz2 = 2.0*dz;
  d   = dx2/2.0;
  raw_index = 0;
  printf("here 200 Z0 = %20.10f \n",Z0);
  for (i=0;i<PARTICLES_IN_X;i++)
  {
    if (i <= CENTRE_POINT)
    {
      x = X0*(1.0 - (double)(i-ZERO)*dx );
      if (i<CENTRE_POINT-20)
      {
        for (j=-ZERO;j<PARTICLES_IN_Z-ZERO;j++)
        {
          z =  Z0 + (double)j*dz;
          raw_particle[0].x[0][raw_index]       = x;
          raw_particle[0].x[1][raw_index]       = 0.0;
          raw_particle[0].x[2][raw_index]       = z;
          raw_particle[0].rho[raw_index]        = RHO_l;
          raw_particle[0].U[raw_index]          = U_l;
          raw_particle[0].raw_index[raw_index]  = raw_index;
          raw_index++;
        }
      }
      else
      {
        for (j=-ZERO;j<PARTICLES_IN_Z-ZERO;j++)
        {
          z =  Z0 + (double)j*dz;
          raw_particle[0].x[0][raw_index]       = x;
          raw_particle[0].x[1][raw_index]       = 0.0;
          raw_particle[0].x[2][raw_index]       = z;
          raw_particle[0].rho[raw_index]        = (RHO_l  + RHO_r*exp(x/d))/(1.0+exp(x/d));
          raw_particle[0].U[raw_index]          = (U_l    +   U_r*exp(x/d))/(1.0+exp(x/d));
          raw_particle[0].raw_index[raw_index]  = raw_index;
          raw_index++;
        }
      }
    }
    else
    {
      x = X1*((double)(i-CENTRE_POINT)*dx2);
      if (i>CENTRE_POINT+20)
      {
        for (j=-ZERO_H;j<PARTICLES_IN_Z_H-ZERO_H;j++)
        {
          z =  Z0 + (double)j*dz2;
          raw_particle[0].x[0][raw_index]       = x;
          raw_particle[0].x[1][raw_index]       = 0.0;
          raw_particle[0].x[2][raw_index]       = z;
          raw_particle[0].rho[raw_index]        = RHO_r;
          raw_particle[0].U[raw_index]          = U_r;
          raw_particle[0].raw_index[raw_index]  = raw_index;
          raw_index++;
        }
      }
      else
      {
        for (j=-ZERO_H;j<PARTICLES_IN_Z_H-ZERO_H;j++)
        {
          z =  Z0 + (double)j*dz2;
          raw_particle[0].x[0][raw_index]       = x;
          raw_particle[0].x[1][raw_index]       = 0.0;
          raw_particle[0].x[2][raw_index]       = z;
          raw_particle[0].rho[raw_index]        = (RHO_l + RHO_r*exp(x/d))/(1.0+exp(x/d));
          raw_particle[0].U[raw_index]          = (U_l   +   U_r*exp(x/d))/(1.0+exp(x/d));
          raw_particle[0].raw_index[raw_index]  = raw_index;
          raw_index++;
        }
      }
    }
  }
  TOTAL_PARTICLES = raw_index; 
  NPARTICLES = TOTAL_PARTICLES/cluster_size;
  pars[0].TOTAL_PARTICLES = TOTAL_PARTICLES;
  pars[0].NPARTICLES = NPARTICLES;
  printf(" NPARTICLES = %i cluster_size = %i \n",NPARTICLES,cluster_size);

  if ((particles=CreateParticles(NPARTICLES,pars))==NULL)
  {
    exit_status = EXIT_FAILURE;
    printf("Rank: %i %s(): -error return creating particle()\n",rank,fname);
    goto RETURN;
  }
/*                                                                            */
/*                 initialize NODE_INFO struct                                */
/*                                                                            */
  if (particles_num == 1)
  {
    if ( (exit_status=GetNodeInfoStruct(cluster_size,rank_name,0.0,pars))==EXIT_FAILURE)
    {
      printf("Rank: %i %s(): -error return getting node_info structure()\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  node_info[rank].total_particles = TOTAL_PARTICLES;
  nparticles = 0;
  for(t=0;t<TOTAL_PARTICLES;t++)
  {
    raw_index = raw_particle[0].raw_index[t];
    if ( (raw_index>=(rank+0)*NPARTICLES) && (raw_index<(rank+1)*NPARTICLES) )
    {
      particles[0].x[0][nparticles]             = raw_particle[0].x[0][t];
      particles[0].x[1][nparticles]             = raw_particle[0].x[1][t];
      particles[0].x[2][nparticles]             = raw_particle[0].x[2][t]; 
      
      if ( (nparticles < 1000) ) printf(" here 500 l = %i x = %20.10f z = %20.10f \n",nparticles,raw_particle[0].x[0][t],raw_particle[0].x[2][t]);
      if ( (nparticles > 139203 - 1000) ) printf(" here 501 l = %i x = %20.10f z = %20.10f \n",nparticles,raw_particle[0].x[0][t],raw_particle[0].x[2][t]);
      particles[0].rho[nparticles]              = raw_particle[0].rho[t];
      particles[0].U[nparticles]                = raw_particle[0].U[t]; 
      particles[0].raw_index[nparticles]        = raw_index;
      node_info[rank].raw_index[nparticles]     = raw_index;
      node_info[rank].inv_raw_index[raw_index]  = nparticles;
      nparticles++;
    }
  }

  if ( (EquationOfState(particles,pars))==EXIT_FAILURE )
  {
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

  if (nparticles != NPARTICLES)printf(" ######## WARNING nparticles not = NPARTICLES");
  node_info[rank].inv_raw_index_set         = 1;
  node_info[rank].raw_index_set             = 1;
  node_info[rank].species_set               = 1;
  node_info[rank].boundary_set              = 1;
  node_info[rank].interior_set              = 1;
  node_info[rank].interior_and_boundary_set = 1;
  node_info[rank].ghost_set                 = 1;
  node_info[rank].ghost_mirror_set          = 1;
  node_info[rank].ghost_x_set               = 1;
  node_info[rank].ghost_y_set               = 1;
  node_info[rank].ghost_z_set               = 1;
  node_info[rank].burn_A_set                = 1;
  node_info[rank].burn_B_set                = 1;
  node_info[rank].burn_E_set                = 1;
  node_info[rank].burn_F_set                = 1;
  l0 = 0;
  l1 = 0;
  l2 = 0;
  l3 = 0;
  l4 = 0;
  j  =  PARTICLES_IN_Z_H/2;
  z3 =  Z0 + (double)(j)*dz2;

  for(l=0;l<nparticles;l++)
  {
    i_raw = particles[0].raw_index[l];
    x = particles[0].x[0][l];
    y = particles[0].x[1][l];
    z = particles[0].x[2][l];
    if (fabs(z-z3)<EPSILON_DOUBLE ) 
    {
      node_info[rank].marker[l4] = l;
      l4++;
    }
    if (
          ((ids=SetParticleID_2D(pars,particles,x,y,z)) == NULL)
                            ||
          (ids->species == EXIT_FAILURE)
       )
    {
      printf("Rank: %i %s():particles -error return from SetParticleID_2D() -species = %i\n",rank,fname,ids->species);
      if (FreeParticles(&particles,pars,NPARTICLES) == EXIT_FAILURE)
      {
        printf("Rank: %i %s():particles -error return from FreeParticles()\n",rank,fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    species = ids[0].species;
    node_info[rank].species[l] = species;
    species_basic = (species&MASK_GHOST) + (species&MASK_BOUND) + (species&MASK_INTER);
    switch (species_basic)
    {
      case 512:
        node_info[rank].interior[l0] = l;
        node_info[rank].interior_and_boundary[l3] = l;
        l0++;
        l3++;
        break;
      case 1024:
        node_info[rank].ghost[l2]        = l;
        node_info[rank].ghost_mirror[l2] = ids[0].l_mirror;
        l2++;
        break;
      case 2048:
        node_info[rank].boundary[l1] = l;
        node_info[rank].interior_and_boundary[l3] = l;
        l1++;
        l3++;
        break;
      default:
        printf("Rank: %i %s(): -error in species type, should be one of 512, 1024 or 2048\n",rank,fname);
        exit_status = EXIT_FAILURE;
        if (FreeParticles(&particles,pars,NPARTICLES) == EXIT_FAILURE)
        {
          printf("Rank: %i %s():particles -error return from FreeParticles()\n",rank,fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
        goto RETURN;
        break;
    }
    free(ids); ids = NULL;
    particles[0].species[l] = node_info[rank].species[l];
  }

  node_info[rank].n_interior              = l0;
  node_info[rank].n_boundary              = l1;
  node_info[rank].n_ghost                 = l2;
  node_info[rank].n_interior_and_boundary = l3;
  node_info[rank].n_marker                = l4;
  node_info[rank].nparticles              = nparticles; 
/*                                                                            */
/*                                                                            */
/*                                                                            */
  node_info[rank].offset = offset;
  node_info[rank].number_of_doubles = NUMBER_OF_DOUBLES;
  node_info[rank].number_of_ints    = NUMBER_OF_INTS;
/*                                                                           */
/*                                                                           */
/*                                                                           */
  if ( (UpdateKernel(particles,pars) == EXIT_FAILURE) )
  {
    printf(" %s() -error return from UpdateKernel() \n",fname);
    exit_status = EXIT_FAILURE;
    if (FreeParticles(&particles,pars,NPARTICLES) == EXIT_FAILURE)
    {
      printf("Rank: %i %s():particles -error return from FreeParticles()\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    goto RETURN;
  } 
/*                                                                           */
/*                                                                           */
   break;
  case 1:
    if ((particles=ReadParticleInfo(pars,particles_num)) == NULL)
    {
      if (FreeParticles(&particles,pars,NPARTICLES) == EXIT_FAILURE)
      {
        printf("Rank: %i %s():particles -error return from FreeParticles()\n",rank,fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if (particles_num == 1)
    {
      if ( (exit_status=GetNodeInfoStruct(cluster_size,rank_name,0.0,pars))==EXIT_FAILURE)
      {
        printf("Rank: %i %s(): -error return getting node_info structure()\n",rank,fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    node_info[rank].total_particles = TOTAL_PARTICLES;
    break;
  default:
    printf(" rank %i: restart not set correctly, has value %i \n",rank,RESTART);
    if (FreeParticles(&particles,pars,NPARTICLES) == EXIT_FAILURE)
    {
      printf("Rank: %i %s():particles -error return from FreeParticles()\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    exit_status = EXIT_FAILURE;
    goto RETURN;
    break;
  }

  exit_status = EXIT_SUCCESS;

RETURN:
/*                                                                            */
/*                                                                            */
  if (X)
  {
    Free_sph(X);
  }
  if (Z)
  {
    Free_sph(Z);
  }
  if (raw_particle)
  {
    Free_sph(raw_particle[0].x[0]);
    Free_sph(raw_particle[0].x[1]);
    Free_sph(raw_particle[0].x[2]);
    Free_sph(raw_particle[0].x);
    Free_sph(raw_particle[0].rho);
    Free_sph(raw_particle[0].U);
    Free_sph(raw_particle[0].raw_index);
    Free_sph(raw_particle);
    raw_particle = NULL;
  }

  verbosity(2,fname,pars);
  exit(1);

  return particles;
}
