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

#include "calculate_divergence_v.h"

void *CalculateDivergenceV(void *v_td)
{
  extern NODE_INFO *node_info;
  extern int cluster_size;

  THREAD_DATA *td                      = NULL;
  PARTICLES *particles                 = NULL;
  PARTICLES *x_particles               = NULL;
  PARS *pars                           = NULL;

  char   fname[]                       = "...CalculateDivergenceV";

  double sum                           = 0.0;
  double r_ij                          = 0.0;
  double m_j                           = 0.0;
  double x_i                           = 0.0;
  double y_i                           = 0.0;
  double z_i                           = 0.0;
  double x_j                           = 0.0;
  double y_j                           = 0.0;
  double z_j                           = 0.0;
  double rho_i                         = 0.0;
  double vx_i                          = 0.0;
  double vy_i                          = 0.0;
  double vz_i                          = 0.0;
  double vx_j                          = 0.0;
  double vy_j                          = 0.0;
  double vz_j                          = 0.0;
  double h_i                           = 0.0;
  double h_j                           = 0.0;
  double h_ij                          = 1.0;

  int found                            = 0;
  int i                                = 0;
  int j                                = 0;
  int k                                = 0;
  int l                                = 0;
  int n                                = 0;
  int num                              = 0;
  int exit_status                      = EXIT_FAILURE;
  int dim                              = 0;
  int start                            = LARGE_NEGATIVE_INT;
  int stop                             = LARGE_NEGATIVE_INT; 
  int node                             = LARGE_NEGATIVE_INT;
  int nn_ik                            = LARGE_NEGATIVE_INT;

  td = (THREAD_DATA *)v_td;
  pars = td->pars;
#include "pars_include.h"

  verbosity(1,fname,pars);

  dim         = DIMENSIONS;
  start       = td->start;
  stop        = td->stop;
  particles   = td->particles;
  x_particles = td->x_particles;

  if (DIMENSIONS == 1)
  {
    for (i=start;i<stop;i++)
    {
      rho_i  = particles[0].rho[i];
      x_i    = particles[0].x[0][i];
      vz_i   = particles[0].v[2][i];
      h_i    = particles[0].h[i];
      sum    = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          x_j    = particles[0].x[0][j];
          vz_j   = particles[0].v[2][j];
          h_j    = particles[0].h[j];
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
          x_j    = x_particles[0].x[0][l];
          vx_j   = x_particles[0].v[0][l];
          h_j    = x_particles[0].h[l];
        }
        h_ij = 0.5*(h_i+h_j);
        r_ij = sqrt( (x_i-x_j)*(x_i-x_j) );
        m_j  = PARTICLE_MASS;
        if (fabs(h_ij > 0.0))
        {
          sum = sum + m_j*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)*(vx_j-vx_i)*dfdx(x_i,x_j,r_ij*h_ij);
        }
      }
      td->particles[0].divV[i] = sum/rho_i;
    }
  }

  if (DIMENSIONS == 2)
  {
    for (i=start;i<stop;i++)
    {
      rho_i  = particles[0].rho[i];
      x_i    = particles[0].x[0][i];
      z_i    = particles[0].x[2][i];
      vx_i   = particles[0].v[0][i];
      vz_i   = particles[0].v[2][i];
      h_i    = particles[0].h[i];
      sum    = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          x_j    = particles[0].x[0][j];
          z_j    = particles[0].x[2][j];
          vx_j   = particles[0].v[0][j];
          vz_j   = particles[0].v[2][j];
          h_j    = particles[0].h[j];
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
          x_j    = x_particles[0].x[0][l];
          z_j    = x_particles[0].x[2][l];
          vx_j   = x_particles[0].v[0][l];
          vz_j   = x_particles[0].v[2][l];
          h_j    = x_particles[0].h[l];
        }
        h_ij = 0.5*(h_i+h_j);
        r_ij = sqrt( (x_i-x_j)*(x_i-x_j)
                   + (z_i-z_j)*(z_i-z_j) );
        m_j  = PARTICLE_MASS;
        if (fabs(h_ij > 0.0))
        {
          sum = sum + m_j*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
              *( (vx_j-vx_i)*dfdx(x_i,x_j,r_ij*h_ij)
              +  (vz_j-vz_i)*dfdz(z_i,z_j,r_ij*h_ij) );
        }
      }
      td->particles[0].divV[i] = sum/rho_i;
    }
  }

  if (DIMENSIONS == 3)
  {
    for (i=start;i<stop;i++)
    {
      rho_i  = particles[0].rho[i];
      x_i    = particles[0].x[0][i];
      y_i    = particles[0].x[1][i];
      z_i    = particles[0].x[2][i];
      vx_i   = particles[0].v[0][i];
      vy_i   = particles[0].v[1][i];
      vz_i   = particles[0].v[2][i];
      h_i    = particles[0].h[i];
      sum    = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          x_j    = particles[0].x[0][j];
          y_j    = particles[0].x[1][j];
          z_j    = particles[0].x[2][j];
          vx_j   = particles[0].v[0][j];
          vy_j   = particles[0].v[1][j];
          vz_j   = particles[0].v[2][j];
          h_j    = particles[0].h[j];
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
          x_j    = x_particles[0].x[0][l];
          y_j    = x_particles[0].x[1][l];
          z_j    = x_particles[0].x[2][l];
          vx_j   = x_particles[0].v[0][l];
          vy_j   = x_particles[0].v[1][l];
          vz_j   = x_particles[0].v[2][l];
          h_j    = x_particles[0].h[l];
        }
        h_ij = 0.5*(h_i+h_j);
        r_ij = sqrt( (x_i-x_j)*(x_i-x_j)
                   + (y_i-y_j)*(y_i-y_j)
                   + (z_i-z_j)*(z_i-z_j) );
        m_j  = PARTICLE_MASS;
        if (fabs(h_ij > 0.0))
        {
          sum = sum + m_j*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH)
              *( (vx_j-vx_i)*dfdx(x_i,x_j,r_ij*h_ij)
              +  (vy_j-vy_i)*dfdy(y_i,y_j,r_ij*h_ij)
              +  (vz_j-vz_i)*dfdz(z_i,z_j,r_ij*h_ij) );
        }
      }
      td->particles[0].divV[i] = sum/rho_i;
    }
  }
   
  exit_status     = EXIT_SUCCESS;
  td->exit_status = &exit_status;

RETURN:
  verbosity(2,fname,pars);
  return NULL;
}
