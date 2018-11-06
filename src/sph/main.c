/*---------------------------------------------------------------------------*\
|                                                                             |
|  File:                                                                      |
|                                                                             |
|  Function: int main(int argc, char *argv[])                                 |
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
|   Copyright (c) 2015,2016,2017,2018 David Brown                             |
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


#include "sph.h"
#include <unistd.h>

#define _GNU_SOURCE

extern int PrintHere(PARTICLES *particles,int i_here,int rank);

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);

  NODE_DESCRIP *node_descrip           = NULL;

  PARS *pars                           = NULL;

  PARTICLES *particles_1               = NULL;
  PARTICLES *particles_2               = NULL;
  PARTICLES *particles_3               = NULL;
  PARTICLES *particles_4               = NULL;
  PARTICLES *x_particles               = NULL;

  PARTICLE  *particle                  = NULL;

  PBOB *pbob                           = NULL;

  char   fname[]                       = "Main";
  char *rank_name                      = NULL;
  char *file_name                      = NULL;
  char *string1                        = NULL;
  char *restart_c                      = NULL;

  double time                          = 0.0;

  double *dUdt_1                       = NULL;
  double **x_1                         = NULL;
  double **a_1                         = NULL;

  double **v_2                         = NULL;
  double *U_2                          = NULL;

  double **x_3                         = NULL;
  double **v_3                         = NULL;
  double **a_3                         = NULL;
  double *U_3                          = NULL;
  double *dUdt_3                       = NULL;
  double **vorticity                   = NULL;

  double **v_4                         = NULL;
  double *U_4                          = NULL;
  double dt                            = 0.0003;
  double *X                            = NULL;
  double dist                          = 0.0;
  double delta                         = 0.0;

  int rank_0                           = 0;
  int raw                              = 0;
  int cluster_size_trial               = 0;
  int *Y                               = NULL;
  int status                           = 0;
  int exit_status                      = EXIT_FAILURE;
  int i_step                           = 0;
  int time_slice                       = 0;
  int write_step_interval              = 10;
  int k                                = 0;
  int i_rank                           = 0;
  int len                              = 0;
  int size                             = 0;
  int i                                = 0;
  int burn_status                      = 0;
  int i0                               = 0;
  int i_raw                            = 0;
  int y                                = 0;
  int l                                = 0;
  int j                                = 0;
  int nparticles                       = 0;
  int **nn                             = NULL;
  int unique_particles                 = LARGE_NEGATIVE_INT;
  int n_offnode_neighbours             = LARGE_NEGATIVE_INT;
  int action                           = LARGE_NEGATIVE_INT;
  int tag1                             = LARGE_NEGATIVE_INT;

  MPI_Group MPI_GROUP_WORLD;

  MPI_Comm_rank(MPI_COMM_WORLD,&rank_0);
  MPI_Comm_size(MPI_COMM_WORLD,&cluster_size);
  cluster_size--;
  rank_name = (char *)calloc(MAX_CHARS,sizeof(char));

  MPI_Get_processor_name(rank_name,&len);
  MPI_Type_size( MPI_DOUBLE,&size );

  feenableexcept(FE_INVALID   |
                 FE_DIVBYZERO |
                 FE_OVERFLOW  |
                 FE_UNDERFLOW); 

  pars = GetPars(argc,argv,rank_0);

#include "pars_include.h"
/*                                                                            */
/*                                                                            */
  MPI_Comm_group(MPI_COMM_WORLD,&MPI_GROUP_WORLD);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
/*                                                                            */
/*                 initialize all particle structs                            */
/*                                                                            */
  if (rank < cluster_size)
  {
    if (DIMENSIONS == 1)
    {
      if ( (particles_1=SetInitialParticlesState1D(pars,1,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_2=SetInitialParticlesState1D(pars,2,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_3=SetInitialParticlesState1D(pars,3,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_4=SetInitialParticlesState1D(pars,4,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    if (DIMENSIONS == 2)
    {
      if ( (particles_1=SetInitialParticlesState2D(pars,1,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_2=SetInitialParticlesState2D(pars,2,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_3=SetInitialParticlesState2D(pars,3,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_4=SetInitialParticlesState2D(pars,4,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    if (DIMENSIONS == 3)
    {
      if ( (particles_1=SetInitialParticlesState3D(pars,1,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_2=SetInitialParticlesState3D(pars,2,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_3=SetInitialParticlesState3D(pars,3,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (particles_4=SetInitialParticlesState3D(pars,4,rank_name))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    NPARTICLES = pars[0].NPARTICLES;
  }
  if ( (rank == 0) || (rank == cluster_size) )
  {
    if ( (UpdateNeighbourNodes(pars))==EXIT_FAILURE )
    {
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */ 
/*                                                                           */
/*                                                                           */
  if (rank < cluster_size)
  {
    i_step = particles_1[0].step;
    time   = particles_1[0].t;
  }
  else
  {
    i_step = 0;
  }

  while (i_step < N_STEPS)
  {
    if (rank < cluster_size)
    {
      if ( (CopyH(particles_1,particles_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      i_step++;
      nparticles = node_info[rank].nparticles;
      printf("\n\n Rank: %i Step: %i  time = %20.10f nparticles = %i \n",rank,i_step,time,node_info[rank].nparticles);

      time                = time + dt;
      particles_3[0].t    = time;
      particles_4[0].t    = time+dt/2;
      particles_3[0].step = i_step;
/*                                                                           */
/*                 retrieve particle1 position                               */
/*                                                                           */
      if ((x_1=GetParticlePosition(particles_1,pars))==NULL)
      {
        printf(" %s() -error getting particle position \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*                                                                           */
/*                 retrieve particle2 velocity                               */
/*                                                                           */
      if ((v_2=GetParticleVelocity(particles_2,pars))==NULL)
      {
        printf(" %s() -error getting particle velocity \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*                                                                           */
/*                 retrieve particle2 energy                                 */
/*                                                                           */
      if ((U_2=GetParticleEnergy(particles_2,pars))==NULL)
      {
        printf(" %s() -error getting particle energy \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*                                                                           */
/*                 retrieve particle1 acceleration                           */
/*                                                                           */
      if ((a_1=GetParticleAcceleration(particles_1,pars))==NULL)
      {
        printf(" %s() -error getting particle acceleration\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                 retrieve particle1 energy deriv                           */
/*                                                                           */
      if ((dUdt_1=GetParticleEnergyDeriv(particles_1,pars))==NULL)
      {
        printf(" %s() -error getting particle energy deriv\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                 integrate particle velocity interior                      */
/*                                                                           */
/*
      printf(" here 102a x_1 = %20.10f v_2 = %20.10f\n",x_1[9195],v_2[9195]);
*/
      if ((x_3=IntegrateParticleVelocity_INTERIOR(x_1,v_2,dt,pars))==NULL)
      {
        printf(" %s() -error integrating particle velocity interior\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                 integrate particle velocity boundary                      */
/*                 -need to call twice                                       */
/*                                                                           */
/*
      printf(" here 102 x_3 = %20.10f v_2 = %20.10f\n",x_3[9195],v_2[9195]);
      if ( 
           ((IntegrateParticleVelocity_BOUNDARY(x_3,pars))==EXIT_FAILURE )
                                          ||
           ((IntegrateParticleVelocity_BOUNDARY(x_3,pars))==EXIT_FAILURE )
         )
      {
        printf(" %s() -error integrating particle velocity boundary\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
*/
/*                                                                           */
/*                 integrate particle acceleration interior                  */
/*                                                                           */
      printf(" here 102  a_1 = %20.10f v_2 = %20.10f\n",a_1[9195],v_2[9195]);
      printf(" here 102b x_3 = %20.10f v_3 = %20.10f\n",x_3[9195],v_2[9195]);
      if ((v_3=IntegrateParticleAcceleration_INTERIOR(v_2,a_1,dt/2.0,pars))==NULL)
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      printf(" here 101 x_3 = %20.10f v_3 = %20.10f\n",x_3[9195],v_3[9195]);
/*                                                                           */
/*                 integrate particle acceleration boundary                  */
/*                                                                           */
      if (
           ((IntegrateParticleAcceleration_BOUNDARY(v_3,pars))==EXIT_FAILURE) 
                                           ||
           ((IntegrateParticleAcceleration_BOUNDARY(v_3,pars))==EXIT_FAILURE) 
         )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      printf(" here 101a x_3 = %20.10f v_3 = %20.10f\n",x_3[9195],v_3[9195]);
/*                                                                           */
/*                 update particle_3 position                                */
/*                                                                           */
      if ((SetParticlePosition(particles_3,x_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      } 
/*                                                                           */
/*                 set particle velocity                                     */
/*                                                                           */
      if ( (SetParticleVelocity(particles_3,v_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*###########################################################################*/
/*                                                                           */
/*            BLOCK 1: PUSH_AND_PULL_N_AND_X :  START                        */
/*                                                                           */
/*                                                                           */
      if ((x_particles = Push_and_Pull_N_and_X(particles_3,pars)) == NULL)
      {
        printf(" %s() -error return from Push_and_Pull_N_and_X() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                               BLOCK 1: END                                */
/*                                                                           */
/*###########################################################################*/


/*###########################################################################*/
/*                                                                           */
/*            BLOCK 2: PUSH_AND_PULL_V :  START                              */
/*                                                                           */
      if (Push_and_Pull_V(particles_3,pars,x_particles) == EXIT_FAILURE)
      {
        printf(" %s() -error return from Push_and_pull_V() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                               BLOCK 2: END                                */
/*                                                                           */
/*###########################################################################*/

/*                                                                           */
/*                 integrate particle energy interior                        */
/*                                                                           */

/*
      printf(" here 100a U_2 = %20.10f dUdt_1 = %20.10f\n",U_2[9195],dUdt_1[9195]);
*/
      if ((U_3=IntegrateParticleEnergy_INTERIOR(U_2,dUdt_1,dt/2.0,pars))==NULL)
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                 integrate particle energy boundary                        */
/*                                                                           */
/*
      printf(" here 100 U_3 = %20.10f v_3 = %20.10f\n",U_3[9195],v_3[9195]);
*/

      if ( (IntegrateParticleEnergy_BOUNDARY(U_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                 particle energy                                           */
/*                                                                           */
      PrintHere(particles_3,10,rank);
      if ( (SetParticleEnergy(particles_3,U_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*###########################################################################*/
/*                                                                           */
/*            BLOCK 3: PUSH_AND_PULL_U :  START                              */
/*                                                                           */
      if (Push_and_Pull_U(particles_3,pars,x_particles) == EXIT_FAILURE)
      {
        printf(" %s() -error return from Push_and_Pull_U() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                               BLOCK 3: END                                */
/*                                                                           */
/*###########################################################################*/

/*                                                                           */
/*                 update kernel lengths                                     */
/*                                                                           */
      PrintHere(particles_3,9,rank);
      if ( (UpdateKernel(particles_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*###########################################################################*/
/*                                                                           */
/*            BLOCK 4: PUSH_AND_PULL_H :  START                              */
/*                                                                           */
      if (Push_and_Pull_H(particles_3,pars,x_particles) == EXIT_FAILURE)
      {
        printf(" %s() -error return from Push_N() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                               BLOCK 4: END                                */
/*                                                                           */
/*###########################################################################*/

      PrintHere(particles_3,8,rank);
      if ( (SetParticleDensity_INTERIOR_thread_wrapper(particles_3,x_particles,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if (
          ((SetParticleDensity_BOUNDARY(particles_3,pars))==EXIT_FAILURE )
                                       ||
          ((SetParticleDensity_BOUNDARY(particles_3,pars))==EXIT_FAILURE )
         )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*###########################################################################*/
/*                                                                           */
/*            BLOCK 5: PUSH_AND_PULL_RHO :  START                            */
/*                                                                           */
      if (Push_and_Pull_RHO(particles_3,pars,x_particles) == EXIT_FAILURE)
      {
        printf(" %s() -error return from Push_N() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                               BLOCK 5: END                                */
/*                                                                           */
/*###########################################################################*/
/*                                                                           */
/*                 pressure                                                  */
/*                                                                           */
      PrintHere(particles_3,7,rank);
      if ( (EquationOfState(particles_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*###########################################################################*/
/*                                                                           */
/*            BLOCK 6: PUSH_AND_PULL_P :  START                              */
/*                                                                           */
      if (Push_and_Pull_P(particles_3,pars,x_particles) == EXIT_FAILURE)
      {
        printf(" %s() -error return from Push_N() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                               BLOCK 6: END                                */
/*                                                                           */
/*###########################################################################*/

/*                                                                           */
/*                 divergence                                                */
/*                                                                           */
      PrintHere(particles_3,6,rank);
      if ( (CalculateDivergenceV_thread_wrapper(particles_3,x_particles,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

/*###########################################################################*/
/*                                                                           */
/*            BLOCK 7: PUSH_AND_PULL_divV :  START                            */
/*                                                                           */
      if (Push_and_Pull_divV(particles_3,pars,x_particles) == EXIT_FAILURE)
      {
        printf(" %s() -error return from Push_N() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
/*                                                                           */
/*                               BLOCK 7: END                                */
/*                                                                           */
/*###########################################################################*/

      PrintHere(particles_3,5,rank);
      if ((a_3=CalculateParticleAcceleration_INTERIOR_thread_wrapper(particles_3,x_particles,pars))==NULL)
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if (
           ((CalculateParticleAcceleration_BOUNDARY(a_3,pars))==EXIT_FAILURE )
                                             ||
           ((CalculateParticleAcceleration_BOUNDARY(a_3,pars))==EXIT_FAILURE )
         )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      PrintHere(particles_3,4,rank);
      if ((dUdt_3=CalculateParticleEnergyDeriv_INTERIOR_thread_wrapper(particles_3,x_particles,pars))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      if(
          ((CalculateParticleEnergyDeriv_BOUNDARY(dUdt_3,pars))==EXIT_FAILURE )
                                          ||
          ((CalculateParticleEnergyDeriv_BOUNDARY(dUdt_3,pars))==EXIT_FAILURE )
        )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      if ( (vorticity=CalculateParticleVorticity(particles_3,x_particles,pars))==NULL )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      n_offnode_neighbours = particles_3[0].n_offnode_neighbours;
      if (n_offnode_neighbours > 0)
      {
        if ( (FreeParticles(&x_particles,pars,n_offnode_neighbours))==EXIT_FAILURE )
        {
          printf("Rank: %i %s():x_particles -error return from FreeParticles()\n",rank,fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
      }
      if ((v_4=IntegrateParticleAcceleration_INTERIOR(v_2,a_3,dt,pars))==NULL)
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if (
          ((IntegrateParticleAcceleration_BOUNDARY(v_4,pars))==EXIT_FAILURE )
                                          ||
          ((IntegrateParticleAcceleration_BOUNDARY(v_4,pars))==EXIT_FAILURE )
         )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      if ((U_4=IntegrateParticleEnergy_INTERIOR(U_2,dUdt_3,dt,pars))==NULL)
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      if (
          ((IntegrateParticleEnergy_BOUNDARY(U_4,pars))==EXIT_FAILURE)
                                   ||
          ((IntegrateParticleEnergy_BOUNDARY(U_4,pars))==EXIT_FAILURE)
         )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      PrintHere(particles_3,3,rank);
      if ( (SetParticleAcceleration(particles_3,a_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      PrintHere(particles_3,2,rank);
      if ( (SetParticleEnergyDeriv(particles_3,dUdt_3,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (SetParticleVelocity(particles_4,v_4,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (SetParticleEnergy(particles_4,U_4,pars))==EXIT_FAILURE )
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if (VERBOSITY > 0)
      {
        if ( (CheckForNaN(particles_3,pars))==EXIT_FAILURE)
        {
          printf("Rank: %i %s():particles_3 -error return from CheckForNaN()\n",rank,fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
        if ( (CheckForNaN(particles_4,pars))==EXIT_FAILURE)
        {
          printf("Rank: %i %s():particles_4 -error return from CheckForNaN()\n",rank,fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
      }
      if ( (FreeParticles(&particles_1,pars,NPARTICLES))==EXIT_FAILURE )
      {
        printf("Rank: %i %s():particles_1 -error return from FreeParticles()\n",rank,fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ( (FreeParticles(&particles_2,pars,NPARTICLES))==EXIT_FAILURE )
      {
        printf("Rank: %i %s():particles_2 -error return from FreeParticles()\n",rank,fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }

      PrintHere(particles_3,1,rank);
      particles_1 = particles_3;
      particles_2 = particles_4;
      particles_3 = NULL;
      particles_4 = NULL;
      printf(" i_step = %i TIME_STEPS_TO_WRITE = %i \n",i_step,TIME_STEPS_TO_WRITE);
      if ( ((i_step%TIME_STEPS_TO_WRITE)==0)  )
      {
        time_slice++;
        if (rank == 0)
        {
          if ((node_descrip=Assemble_NODE_DESCRIP(pars,cluster_size)) == NULL)
          {
            printf("Rank: %i %s(): -error return from Assemble_NODE_DESCRIP()\n",rank,fname);
            exit_status = EXIT_FAILURE;
          goto RETURN;
          }
          if ((pbob=Assemble_PBOB(pars,time,cluster_size)) == NULL)
          {
            printf("Rank: %i %s(): -error return from Assemble_PBOB()\n",rank,fname);
            exit_status = EXIT_FAILURE;
            goto RETURN;
          }
          if ((WritePbobNodeDescrip(pbob,node_descrip,out_dir,rank,time_slice)) == EXIT_FAILURE) 
          {
            printf("Rank: %i %s(): -error return from WritePbobNodeDescrip()\n",rank,fname);
            exit_status = EXIT_FAILURE;
            goto RETURN;
          }
          Free_sph(pbob);
          Free_sph(node_descrip);
        }
    
        if ((particle=Assemble_PARTICLE(particles_1,pars,&unique_particles,time_slice,vorticity)) == NULL)
        {
          printf("Rank: %i %s(): -error return from Assemble_PARTICLE()\n",rank,fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
        if ((WriteParticle(particle,unique_particles,rank,out_dir,time_slice)) == EXIT_FAILURE) 
        {
          printf("Rank: %i %s(): -error return from WriteParticle()\n",rank,fname);
          exit_status = EXIT_FAILURE;
          goto RETURN;
        }
        Free_sph(particle);
      }
      FreeMatrix(vorticity,3,pars);
 
      if ((particles_3=CreateParticles(NPARTICLES,pars))==NULL)
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if ((particles_4=CreateParticles(NPARTICLES,pars))==NULL)
      {
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      x_1    = NULL;
      a_1    = NULL;
      dUdt_1 = NULL;
      v_2    = NULL;
      U_2    = NULL;
      x_3    = NULL;
      v_3    = NULL;
      a_3    = NULL;
      U_3    = NULL;
      dUdt_3 = NULL;
      v_4    = NULL;
      U_4    = NULL;
    }
    else
    {
      action=Set_N(pars);
      if (action == EXIT_FAILURE)
      {
        printf(" %s() -error return from Set_N() -aborting\n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
      if (action == LARGE_POSITIVE_INT)
      {
        goto RETURN;
      }
    }
  }

  if (rank < cluster_size)
  {
    if (rank == 0)
    {
      action = LARGE_POSITIVE_INT;
      tag1  = 1*(MAX_TAGS)+rank;
      if ( (MPI_Send(&action,1,MPI_INT,cluster_size,tag1,MPI_COMM_WORLD)) != MPI_SUCCESS)
      {
        printf(" %s(): unable to send tag1 packet \n",fname);
        exit_status = EXIT_FAILURE;
        goto RETURN;
      }
    }
    if ((WriteParticleInfo(particles_1,pars,1,"no-test")) == EXIT_FAILURE)
    {
      printf(" Rank: %i %s():particles_1 -error return from WriteParticleInfo\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if ((WriteParticleInfo(particles_2,pars,2,"no-test")) == EXIT_FAILURE)
    {
      printf(" Rank: %i %s():particles_2 -error return from WriteParticleInfo\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if ((WriteParticleInfo(particles_3,pars,3,"no-test")) == EXIT_FAILURE)
    {
      printf(" Rank: %i %s():particles_3 -error return from WriteParticleInfo\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if ((WriteParticleInfo(particles_4,pars,4,"no-test")) == EXIT_FAILURE)
    {
      printf(" Rank: %i %s():particles_4 -error return from WriteParticleInfo\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
    if ((WriteNodeInfo(pars)) == EXIT_FAILURE)
    {
      printf(" Rank: %i %s(): error return from WriteNodeInfo\n",rank,fname);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }

RETURN:
  if (rank < cluster_size)
  {
    if (VERBOSITY > 0)
    {
      if ( (CheckForNaN(particles_1,pars))==EXIT_FAILURE)
      {
        printf(" %s():particles_1 -error return from CheckForNaN()\n",fname);
        exit_status = EXIT_FAILURE;
      }
      if ( (CheckForNaN(particles_2,pars))==EXIT_FAILURE)
      {
        printf(" %s():particles_2 -error return from CheckForNaN()\n",fname);
        exit_status = EXIT_FAILURE;
      } 
    } 
  
    if (FreeNodeInfo(cluster_size,pars) == EXIT_FAILURE)
    {
      if (rank >= 0)
      {
        printf(" Rank: %i Main(): error return from FreeNodeInfo \n",rank);
      }
      else
      {
        printf(" Rank: <unkown>  Main(): error return from FreeNodeInfo \n");
      }
      exit_status = EXIT_FAILURE;
    }
    if (FreeParticles(&particles_1,pars,NPARTICLES) == EXIT_FAILURE)
    {
      printf("Rank: %i %s():particles_1 -error return from FreeParticles()\n",rank,fname);
      exit_status = EXIT_FAILURE;
    }
    if (FreeParticles(&particles_2,pars,NPARTICLES) == EXIT_FAILURE)
    {
      printf("Rank: %i %s():particles_2 -error return from FreeParticles()\n",rank,fname);
      exit_status = EXIT_FAILURE;
    }
    if (FreeParticles(&particles_3,pars,NPARTICLES) == EXIT_FAILURE)
    {
      printf("Rank: %i %s():particles_3 -error return from FreeParticles()\n",rank,fname);
      exit_status = EXIT_FAILURE;
    }
    if (FreeParticles(&particles_4,pars,NPARTICLES) == EXIT_FAILURE)
    {
      printf("Rank: %i %s():particles_4 -error return from FreeParticles()\n",rank,fname);
      exit_status = EXIT_FAILURE;
    }

    a_1    = NULL;
    v_2    = NULL;
    U_2    = NULL;
    U_3    = NULL;
    U_4    = NULL;
    dUdt_1 = NULL;
    dUdt_3 = NULL;
    if (X)
    {
      Free_sph(X);
    }
    if (Y)
    {
      Free_sph(Y);
    }
  } 

  Free_sph(pars);
  if (rank_name)
  {
    Free_sph(rank_name);
  }

  MPI_Finalize();

  return exit_status;
}

int PrintHere(PARTICLES *particles,int i_here,int rank)
{
  double x0                            = 0.0;
  double y0                            = 0.0;
  double z0                            = 0.0;
  double x1                            = 0.0;
  double y1                            = 0.0;
  double z1                            = 0.0;
  double d2                            = 0.0;
  double h                             = 0.0;
  double  x0l;
  double  x1l;
  double  x2l;
  double  v0l;
  double  v1l;
  double  v2l;
  double  a0l;
  double  a1l;
  double  a2l;
  double  Ul;
  double  dUl;
  double  x0j;
  double  x1j;
  double  x2j;
  double  v0j;
  double  v1j;
  double  v2j;
  double  a0j;
  double  a1j;
  double  a2j;
  double  Uj;
  double  dUj;
  double  rj;
  double  rl;
  int n_marker                         = 0;
  int i                                = 0;
  int j                                = 0;
  int k                                = 0;
  int l                                = 0;
  int raw                              = 0;
  int species                          = 0;
  int n_boundary                       = 0;
  int l0                               = LARGE_NEGATIVE_INT;
  int l1                               = LARGE_NEGATIVE_INT;
  int l2                               = LARGE_NEGATIVE_INT;
  int l4                               = LARGE_NEGATIVE_INT;
  int l5                               = LARGE_NEGATIVE_INT;
  int l6                               = LARGE_NEGATIVE_INT;
  int g                                = LARGE_NEGATIVE_INT;
 
  int node                             = LARGE_NEGATIVE_INT;
  int nn_ik                            = LARGE_NEGATIVE_INT; 
  int NPARTICLES                       = LARGE_NEGATIVE_INT;


  printf("############################# START %i #########################################\n",i_here);
  printf("# \n");
  printf("# \n");
  printf("\n\nRank:%i  \n",rank);
  for (l=9195 - 10;l<9195 + 10;l++)
  {
    printf("Rank: %i l=%i raw=%i h=%12.5f rho=%18.15f p=%9.5f U=%20.15f v = %20.15f x = %12.8f z = %12.8f\n",rank,l,raw,particles[0].h[l],particles[0].rho[l],particles[0].p[l],particles[0].U[l],particles[0].v[0][l],particles[0].x[0][l],particles[0].x[2][l]);
  }
  
/*
  n_marker = node_info[rank].n_marker;
  for (j=0;j<n_marker;j++)
  {
    l = node_info[rank].marker[j];
    raw = node_info[rank].raw_index[l];
    printf("Rank: %i l=%i raw=%i h=%12.5f rho=%18.15f p=%9.5f U=%20.15f v = %20.15f x = %12.8f z = %12.8f\n",rank,l,raw,particles[0].h[l],particles[0].rho[l],particles[0].p[l],particles[0].U[l],particles[0].v[0][l],particles[0].x[0][l],particles[0].x[2][l]);
  }  
*/

/*
  for (g=30;g<40;g++)
  {
    for (l=0;l<40;l++) 
    {
      l0  = l + g*835;
      printf("h=%13.10f l=%i s=%4i rho=%13.10f p=%9.5f U=%13.10f dU=%13.10f vx = %13.10f vz = %13.10f x = %12.8f z = %12.8f ax=%13.10f az=%15.12f\n",particles[0].h[l0],l0,particles[0].species[l0],particles[0].rho[l0],particles[0].p[l0],particles[0].U[l0],particles[0].dUdt[l0],particles[0].v[0][l0],particles[0].v[2][l0],particles[0].x[0][l0],particles[0].x[2][l0],particles[0].dvdt[0][l0],particles[0].dvdt[2][l0]);
    }
    printf("\n"); 
  }
*/

  
  
/*
  for (l=138786;l<139203;l++) 
  {
    for (g=-10;g<1;g++)
    {
      l0  = l + g*417;
      printf("Rank: %i l=%i s=%4i rho=%13.10f p=%9.5f U=%13.10f dU=%13.10f vx = %13.10f vz = %13.10f x = %12.8f z = %12.8f ax=%13.10f az=%15.12f\n",rank,l0,particles[0].species[l0],particles[0].rho[l0],particles[0].p[l0],particles[0].U[l0],particles[0].dUdt[l0],particles[0].v[0][l0],particles[0].v[2][l0],particles[0].x[0][l0],particles[0].x[2][l0],particles[0].dvdt[0][l0],particles[0].dvdt[2][l0]);
    }
    printf("\n"); 
  }
*/

/*
  NPARTICLES = 139203;
  for (k=0;k<51;k++)
  {
    l = l=137318;
    nn_ik  = particles[0].nn[l][k];
    node   = nn_ik/NPARTICLES;
    j      = nn_ik%NPARTICLES;
    printf(" k=%i  l=%i j=%i node=%i nn_ik=%i\n",k,l,j,node,nn_ik);
  }
*/

  printf("\n"); 
  printf("# \n");
  printf("# \n");
  printf("# \n");
  printf("# \n");
  printf("############################# END %i ##########################################\n",i_here);
  return EXIT_SUCCESS;
}
