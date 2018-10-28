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

#include "calculate_particle_energy_deriv_interior.h"

void *CalculateParticleEnergyDeriv_INTERIOR(void *v_td)
{
  extern int cluster_size;
  extern NODE_INFO *node_info;

  THREAD_DATA *td                      = NULL;
  PARS *pars                           = NULL;
  PARTICLES *particles                 = NULL;
  PARTICLES *x_particles               = NULL;


  char   fname[]                       = "...CalculateParticleEnergyDeriv_INTERIOR";

  int found                            = 0;
  int i                                = 0;
  int j                                = 0;
  int k                                = 0;
  int l                                = 0;
  int n                                = 0;
  int num                              = 0;
  int index                            = 0;
  int n_interior_and_boundary          = 0;
  int exit_status                      = EXIT_FAILURE;
  int dim                              = 0;
  int start                            = LARGE_NEGATIVE_INT;
  int stop                             = LARGE_NEGATIVE_INT;
  int node                             = LARGE_NEGATIVE_INT;
  int nn_ik                            = LARGE_NEGATIVE_INT;

  double sum                           = 0.0;
  double sum_v                         = 0.0;
  double r_ij                          = 0.0;
  double r2_ij                         = 0.0;
  double PII_ij                        = 0.0;
  double H_ij                          = 0.0;
  double rho_i                         = 0.0;
  double rho2_i                        = 0.0;
  double rho2_j                        = 0.0;
  double rho_j                         = 0.0;
  double rho_ij                        = 0.0;
  double m_j                           = 0.0;
  double c_i                           = 0.0;
  double c_ij                          = 0.0;
  double d_i                           = 0.0;
  double d_j                           = 0.0;
  double h_i                           = 0.0;
  double h_ij                          = 0.0;
  double h2_ij                         = 0.0;
  double A                             = 0.0;
  double B                             = 0.0;
  double h2_i                          = 0.0;
  double h2_j                          = 0.0;
  double h_j                           = 0.0;
  double a_i                           = 0.0;
  double a_j                           = 0.0;
  double a_ij                          = 0.0;
  double U_i                           = 0.0;
  double U_j                           = 0.0;
  double c_j                           = 0.0;
  double p_i                           = 0.0;
  double p_j                           = 0.0;
  double fact_h0                       = 0.0;
  double fact_h1                       = 0.0;
  double fact_h2                       = 0.0;
  double fact_v                        = 0.0;
  double vx_j                          = 0.0;
  double vy_j                          = 0.0;
  double vz_j                          = 0.0;
  double vx_i                          = 0.0;
  double vy_i                          = 0.0;
  double vz_i                          = 0.0;
  double x_i                           = 0.0;
  double y_i                           = 0.0;
  double z_i                           = 0.0;
  double x_j                           = 0.0;
  double y_j                           = 0.0;
  double z_j                           = 0.0;
  double mu_ij                         = 0.0;
  double mu2_ij                        = 0.0;
  double eta2                          = 0.0;
  double *energy_deriv                 = NULL;
  double MU_en                         = 0.000001;
  double rhom_ij                       = 0.0;
  double f                             = 0.0;

  td = (THREAD_DATA *)v_td;
  pars = td->pars;

#include "pars_include.h"
  verbosity(1,fname,pars);

  eta2 = td->pars[0].ETA*td->pars[0].ETA;
  dim  = td->pars[0].DIMENSIONS;

  start       = td->start;
  stop        = td->stop;
  particles   = td->particles;
  x_particles = td->x_particles;

  if (DIMENSIONS == 1)
  {
    for (index=start;index<stop;index++)
    {
      i      = node_info[rank].interior_and_boundary[index];
      x_i    = particles[0].x[0][i];
      p_i    = particles[0].p[i];
      rho_i  = particles[0].rho[i];
      rho2_i = rho_i*rho_i;
      c_i    = sqrt(GAMMA*p_i/rho_i);
      d_i    = particles[0].divV[i];
      vx_i   = particles[0].v[0][i];
      h_i    = particles[0].h[i];
      U_i    = particles[0].U[i];
      h2_i   = h_i*h_i;
      a_i    = G1*h_i*c_i + G2*h2_i*(fabs(d_i)-d_i);
      sum    = 0.0;
      sum_v  = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          p_j    = particles[0].p[j];
          d_j    = particles[0].divV[j];
          rho_j  = particles[0].rho[j];
          x_j    = particles[0].x[0][j];
          vx_j   = particles[0].v[0][j];
          h_j    = particles[0].h[j];
          U_j    = particles[0].U[j];
          m_j    = particles[0].m[j];
        }
        else
        {
          num = particles[0].nn_index[j].num;
          if (num == 0)
          {
            printf(" ERROR 0\n");
            exit(1);
          }
          else if (num == 1)
          {
            l = particles[0].nn_index[j].n_offnode_neighbours[0];
          }
          else
          {
            found = 0;
            for (n=0;n<num;n++)
            {
               if ( (node ==particles[0].nn_index[j].node[n]) ) 
               { 
                 l = particles[0].nn_index[j].n_offnode_neighbours[n];
                 found = 1;
                 break;
               }
            }
            if (found == 0)
            {
              printf(" ERROR 1\n");
              exit(1);
            }
          }
          p_j    = x_particles[0].p[l]; 
          d_j    = x_particles[0].divV[l];
          rho_j  = x_particles[0].rho[l];
          x_j    = x_particles[0].x[0][l];
          vx_j   = x_particles[0].v[0][l];
          h_j    = x_particles[0].h[l];
          U_j    = x_particles[0].U[l];
          m_j    = x_particles[0].m[l];
        }
        rho2_j = rho_j*rho_j;
        rho_ij = 0.5*(rho_i+rho_j);
        rhom_ij = rho_i*rho_j;
        c_j    = sqrt(GAMMA*p_j/rho_j);
        c_ij   = 0.5*(c_i+c_j);
        h2_j   = h_j*h_j;
        a_j    = G1*h_j*c_j + G2*h2_j*(fabs(d_j)-d_j);
        a_ij   = 0.5*(a_i + a_j);
        h_ij   = 0.5*(h_i+h_j);
        h2_ij  = h_ij*h_ij;
        r_ij   = sqrt(
                      (x_i-x_j)*(x_i-x_j)
                     );
        r2_ij  = r_ij*r_ij;
        A      = 0.0;
        if (
             (fabs(vx_i) > EPSILON_DOUBLE) 
                        && 
             (fabs(vx_j) > EPSILON_DOUBLE) 
                       &&
             (fabs(x_i)  > EPSILON_DOUBLE)
                       && 
             (fabs(x_j)  > EPSILON_DOUBLE)
           )
        {
          A = (vx_i-vx_j)*(x_i-x_j);
        }
        if (A < 0.0)
        {
          B      = (r2_ij/h2_ij+eta2);
          mu_ij  = A/(h_ij*B);
          mu2_ij = mu_ij*mu_ij;
          PII_ij = (-ALPHA*c_ij*mu_ij+BETA*mu2_ij)/rho_ij;
          H_ij   = 2.0*a_ij*(U_i-U_j)
                 /(rho_ij*h2_ij*B);
        }
        else
        {
          PII_ij = 0.0;
          H_ij   = 0.0;
        }
        fact_h0  = m_j*((p_i/rho2_i + p_j/rho2_j+PII_ij)*(vx_j-vx_i) + 2.0*H_ij*(x_j-x_i));
        fact_v   = m_j*MU_en*(U_j-U_i)/rhom_ij;
        f        = r_ij/h_ij;
        f        = r_ij;
        if (fabs(f) < EPSILON_DOUBLE)
        {
          f = 1.0;
        }
        sum = sum - 0.5*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
                   *(
                      fact_h0*dfdx(x_i,x_j,r_ij*h_ij)
                    );
        sum_v  = sum_v + fact_v*(d2Wdf2(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
                              *(dfdx(x_i,x_j,r_ij*h_ij)*dfdx(x_i,x_j,r_ij*h_ij))
                              + dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)/f);
      }
      td->vector[i] = sum + sum_v;
    }
  }

  if (DIMENSIONS == 2)
  {
    for (index=start;index<stop;index++)
    {
      i      = node_info[rank].interior_and_boundary[index];
      x_i    = particles[0].x[0][i];
      z_i    = particles[0].x[2][i];
      p_i    = particles[0].p[i];
      rho_i  = particles[0].rho[i];
      rho2_i = rho_i*rho_i;
      c_i    = sqrt(GAMMA*p_i/rho_i);
      d_i    = particles[0].divV[i];
      vx_i   = particles[0].v[0][i];
      vz_i   = particles[0].v[2][i];
      h_i    = particles[0].h[i];
      U_i    = particles[0].U[i];
      h2_i   = h_i*h_i;
      a_i    = G1*h_i*c_i + G2*h2_i*(fabs(d_i)-d_i);
      sum    = 0.0;
      sum_v  = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          p_j    = particles[0].p[j];
          d_j    = particles[0].divV[j];
          rho_j  = particles[0].rho[j];
          x_j    = particles[0].x[0][j];
          z_j    = particles[0].x[2][j];
          vx_j   = particles[0].v[0][j];
          vz_j   = particles[0].v[2][j];
          h_j    = particles[0].h[j];
          U_j    = particles[0].U[j];
          m_j    = particles[0].m[j];
        }
        else
        {
          num = particles[0].nn_index[j].num;
          if (num == 0)
          {
            printf(" ERROR 0\n");
            exit(1);
          }
          else if (num == 1)
          {
            l = particles[0].nn_index[j].n_offnode_neighbours[0];
          }
          else
          {
            found = 0;
            for (n=0;n<num;n++)
            {
               if ( (node ==particles[0].nn_index[j].node[n]) ) 
               { 
                 l = particles[0].nn_index[j].n_offnode_neighbours[n];
                 found = 1;
                 break;
               }
            }
            if (found == 0)
            {
              printf(" ERROR 1\n");
              exit(1);
            }
          }
          p_j    = x_particles[0].p[l]; 
          d_j    = x_particles[0].divV[l];
          rho_j  = x_particles[0].rho[l];
          x_j    = x_particles[0].x[0][l];
          z_j    = x_particles[0].x[2][l];
          vx_j   = x_particles[0].v[0][l];
          vz_j   = x_particles[0].v[2][l];
          h_j    = x_particles[0].h[l];
          U_j    = x_particles[0].U[l];
          m_j    = x_particles[0].m[l];
        }
        rho2_j = rho_j*rho_j;
        rho_ij = 0.5*(rho_i+rho_j);
        rhom_ij = rho_i*rho_j;
        c_j    = sqrt(GAMMA*p_j/rho_j);
        c_ij   = 0.5*(c_i+c_j);
        h2_j   = h_j*h_j;
        a_j    = G1*h_j*c_j + G2*h2_j*(fabs(d_j)-d_j);
        a_ij   = 0.5*(a_i + a_j);
        h_ij   = 0.5*(h_i+h_j);
        h2_ij  = h_ij*h_ij;
        r_ij   = sqrt(
                      (x_i-x_j)*(x_i-x_j)
                    + (z_i-z_j)*(z_i-z_j)
                     );
        r2_ij  = r_ij*r_ij;
        A      = 0.0;
        if (
             (fabs(vx_i) > EPSILON_DOUBLE) 
                        && 
             (fabs(vx_j) > EPSILON_DOUBLE) 
                       &&
             (fabs(x_i)  > EPSILON_DOUBLE)
                       && 
             (fabs(x_j)  > EPSILON_DOUBLE)
                       &&
             (fabs(vz_i) > EPSILON_DOUBLE) 
                        && 
             (fabs(vz_j) > EPSILON_DOUBLE) 
                       &&
             (fabs(z_i)  > EPSILON_DOUBLE)
                       && 
             (fabs(z_j)  > EPSILON_DOUBLE)
           )
        {
          A = (vx_i-vx_j)*(x_i-x_j)
            + (vz_i-vz_j)*(z_i-z_j);
        }
        if (A < 0.0)
        {
          B      = (r2_ij/h2_ij+eta2);
          mu_ij  = A/(h_ij*B);
          mu2_ij = mu_ij*mu_ij;
          PII_ij = (-ALPHA*c_ij*mu_ij+BETA*mu2_ij)/rho_ij;
          H_ij   = 2.0*a_ij*(U_i-U_j)
                 /(rho_ij*h2_ij*B);
        }
        else
        {
          PII_ij = 0.0;
          H_ij   = 0.0;
        }
        fact_h0  = m_j*((p_i/rho2_i + p_j/rho2_j+PII_ij)*(vx_j-vx_i) + 2.0*H_ij*(x_j-x_i));
        fact_h2  = m_j*((p_i/rho2_i + p_j/rho2_j+PII_ij)*(vz_j-vz_i) + 2.0*H_ij*(z_j-z_i));
        fact_v   = m_j*MU_en*(U_j-U_i)/rhom_ij;
/*  djb start */
      if (rank ==2)
      {
        if ( (i=470)  && (j = 474) )
        {
          printf("here 21:   i = %i j = %i fact_h0 = %20.10f m_j = %20.10f p_i = %20.10f p_j = %20.10f rho2_i = %20.10f rho2_j = %20.10f PI_ij = %20.10f \n",i,j,fact_h0,m_j,p_i,p_j,rho2_i,rho2_j,PI_ij);
        }
      }
/* djb end */

        f        = r_ij/h_ij;
        f        = r_ij;
        if (fabs(f) < EPSILON_DOUBLE)
        {
          f = 1.0;
        }
        sum = sum - 0.5*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
                   *(
                      fact_h0*dfdx(x_i,x_j,r_ij*h_ij)
                   +  fact_h2*dfdz(z_i,z_j,r_ij*h_ij) 
                    );
        sum_v  = sum_v + fact_v*(d2Wdf2(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
                              *(dfdx(x_i,x_j,r_ij*h_ij)*dfdx(x_i,x_j,r_ij*h_ij) 
                              + dfdz(z_i,z_j,r_ij*h_ij)*dfdz(z_i,z_j,r_ij*h_ij))
                              + dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)/f);
      }

      td->vector[i] = sum + sum_v;
      




    }

  }

  if (DIMENSIONS == 3)
  {
    for (index=start;index<stop;index++)
    {
      i      = node_info[rank].interior_and_boundary[index];
      x_i    = particles[0].x[0][i];
      y_i    = particles[0].x[1][i];
      z_i    = particles[0].x[2][i];
      p_i    = particles[0].p[i];
      rho_i  = particles[0].rho[i];
      rho2_i = rho_i*rho_i;
      c_i    = sqrt(GAMMA*p_i/rho_i);
      d_i    = particles[0].divV[i];
      vx_i   = particles[0].v[0][i];
      vy_i   = particles[0].v[1][i];
      vz_i   = particles[0].v[2][i];
      h_i    = particles[0].h[i];
      U_i    = particles[0].U[i];
      h2_i   = h_i*h_i;
      a_i    = G1*h_i*c_i + G2*h2_i*(fabs(d_i)-d_i);
      sum    = 0.0;
      sum_v  = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          p_j    = particles[0].p[j];
          d_j    = particles[0].divV[j];
          rho_j  = particles[0].rho[j];
          x_j    = particles[0].x[0][j];
          y_j    = particles[0].x[1][j];
          z_j    = particles[0].x[2][j];
          vx_j   = particles[0].v[0][j];
          vy_j   = particles[0].v[1][j];
          vz_j   = particles[0].v[2][j];
          h_j    = particles[0].h[j];
          U_j    = particles[0].U[j];
          m_j    = particles[0].m[j];
        }
        else
        {
          num = particles[0].nn_index[j].num;
          if (num == 0)
          {
            printf(" ERROR 0\n");
            exit(1);
          }
          else if (num == 1)
          {
            l = particles[0].nn_index[j].n_offnode_neighbours[0];
          }
          else
          {
            found = 0;
            for (n=0;n<num;n++)
            {
               if ( (node ==particles[0].nn_index[j].node[n]) ) 
               { 
                 l = particles[0].nn_index[j].n_offnode_neighbours[n];
                 found = 1;
                 break;
               }
            }
            if (found == 0)
            {
              printf(" ERROR 1\n");
              exit(1);
            }
          }
          p_j    = x_particles[0].p[l]; 
          d_j    = x_particles[0].divV[l];
          rho_j  = x_particles[0].rho[l];
          x_j    = x_particles[0].x[0][l];
          y_j    = x_particles[0].x[1][l];
          z_j    = x_particles[0].x[2][l];
          vx_j   = x_particles[0].v[0][l];
          vy_j   = x_particles[0].v[1][l];
          vz_j   = x_particles[0].v[2][l];
          h_j    = x_particles[0].h[l];
          U_j    = x_particles[0].U[l];
          m_j    = x_particles[0].m[l];
        }
        rho2_j = rho_j*rho_j;
        rho_ij = 0.5*(rho_i+rho_j);
        rhom_ij = rho_i*rho_j;
        c_j    = sqrt(GAMMA*p_j/rho_j);
        c_ij   = 0.5*(c_i+c_j);
        h2_j   = h_j*h_j;
        a_j    = G1*h_j*c_j + G2*h2_j*(fabs(d_j)-d_j);
        a_ij   = 0.5*(a_i + a_j);
        h_ij   = 0.5*(h_i+h_j);
        h2_ij  = h_ij*h_ij;
        r_ij   = sqrt(
                      (x_i-x_j)*(x_i-x_j)
                    + (y_i-y_j)*(y_i-y_j)
                    + (z_i-z_j)*(z_i-z_j)
                     );
        r2_ij  = r_ij*r_ij;
        A      = 0.0;
        if (
             (fabs(vx_i) > EPSILON_DOUBLE) 
                        && 
             (fabs(vx_j) > EPSILON_DOUBLE) 
                       &&
             (fabs(x_i)  > EPSILON_DOUBLE)
                       && 
             (fabs(x_j)  > EPSILON_DOUBLE)
                       &&
             (fabs(vy_i) > EPSILON_DOUBLE) 
                        && 
             (fabs(vy_j) > EPSILON_DOUBLE) 
                       &&
             (fabs(y_i)  > EPSILON_DOUBLE)
                       && 
             (fabs(y_j)  > EPSILON_DOUBLE)
                       &&
             (fabs(vz_i) > EPSILON_DOUBLE) 
                        && 
             (fabs(vz_j) > EPSILON_DOUBLE) 
                       &&
             (fabs(z_i)  > EPSILON_DOUBLE)
                       && 
             (fabs(z_j)  > EPSILON_DOUBLE)
           )
        {
          A = (vx_i-vx_j)*(x_i-x_j)
            + (vy_i-vy_j)*(y_i-y_j)
            + (vz_i-vz_j)*(z_i-z_j);
        }
        if (A < 0.0)
        {
          B      = (r2_ij/h2_ij+eta2);
          mu_ij  = A/(h_ij*B);
          mu2_ij = mu_ij*mu_ij;
          PII_ij = (-ALPHA*c_ij*mu_ij+BETA*mu2_ij)/rho_ij;
          H_ij   = 2.0*a_ij*(U_i-U_j)
                 /(rho_ij*h2_ij*B);
        }
        else
        {
          PII_ij = 0.0;
          H_ij   = 0.0;
        }
        fact_h0  = m_j*((p_i/rho2_i + p_j/rho2_j+PII_ij)*(vx_j-vx_i) + 2.0*H_ij*(x_j-x_i));
        fact_h1  = m_j*((p_i/rho2_i + p_j/rho2_j+PII_ij)*(vy_j-vy_i) + 2.0*H_ij*(y_j-y_i));
        fact_h2  = m_j*((p_i/rho2_i + p_j/rho2_j+PII_ij)*(vz_j-vz_i) + 2.0*H_ij*(z_j-z_i));
        fact_v   = m_j*MU_en*(U_j-U_i)/rhom_ij;
        f        = r_ij/h_ij;
        f        = r_ij;
        if (fabs(f) < EPSILON_DOUBLE)
        {
          f = 1.0;
        }
        sum = sum - 0.5*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
                   *(
                      fact_h0*dfdx(x_i,x_j,r_ij*h_ij)
                   +  fact_h1*dfdy(y_i,y_j,r_ij*h_ij)
                   +  fact_h2*dfdz(z_i,z_j,r_ij*h_ij) 
                    );
        sum_v  = sum_v + fact_v*(d2Wdf2(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
                              *(dfdx(x_i,x_j,r_ij*h_ij)*dfdx(x_i,x_j,r_ij*h_ij) 
                              + dfdy(y_i,y_j,r_ij*h_ij)*dfdy(y_i,y_j,r_ij*h_ij)
                              + dfdz(z_i,z_j,r_ij*h_ij)*dfdz(z_i,z_j,r_ij*h_ij))
                              + dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)/f);
      }
      td->vector[i] = sum + sum_v;
    }
  }

  exit_status     = EXIT_SUCCESS;
  td->exit_status = &exit_status;
RETURN:

  verbosity(2,fname,pars);
  return NULL;
}
