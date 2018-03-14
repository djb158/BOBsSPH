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

#include "calculate_particle_vorticity.h"

extern int is_nan_or_inf(double x,char *s,int l);

double **CalculateParticleVorticity(PARTICLES *particles,PARTICLES *x_particles,PARS *pars)
{
  extern NODE_INFO *node_info;

  char   fname[]                       = "...CalculateParticleVorticity";

  double **vort                        = NULL;
  double p                             = LARGE_NEGATIVE_DOUBLE;
  double sum0                          = LARGE_NEGATIVE_DOUBLE;
  double sum1                          = LARGE_NEGATIVE_DOUBLE;
  double sum2                          = LARGE_NEGATIVE_DOUBLE;
  double x_i                           = LARGE_NEGATIVE_DOUBLE;
  double y_i                           = LARGE_NEGATIVE_DOUBLE;
  double z_i                           = LARGE_NEGATIVE_DOUBLE;
  double h_i                           = LARGE_NEGATIVE_DOUBLE;
  double x_j                           = LARGE_NEGATIVE_DOUBLE;
  double y_j                           = LARGE_NEGATIVE_DOUBLE;
  double z_j                           = LARGE_NEGATIVE_DOUBLE;
  double h_j                           = LARGE_NEGATIVE_DOUBLE;
  double rho_j                         = LARGE_NEGATIVE_DOUBLE;
  double vx_j                          = LARGE_NEGATIVE_DOUBLE;
  double vy_j                          = LARGE_NEGATIVE_DOUBLE;
  double vz_j                          = LARGE_NEGATIVE_DOUBLE;
  double h_ij                          = LARGE_NEGATIVE_DOUBLE;
  double r_ij                          = LARGE_NEGATIVE_DOUBLE;
  double m_j                           = LARGE_NEGATIVE_DOUBLE;
  double fact0                         = LARGE_NEGATIVE_DOUBLE;
  double fact1                         = LARGE_NEGATIVE_DOUBLE;
  double fact2                         = LARGE_NEGATIVE_DOUBLE;

  int i                                = LARGE_NEGATIVE_INT;
  int j                                = LARGE_NEGATIVE_INT;
  int k                                = LARGE_NEGATIVE_INT;
  int l                                = LARGE_NEGATIVE_INT;
  int index                            = LARGE_NEGATIVE_INT;
  int nn_ik                            = LARGE_NEGATIVE_INT;
  int node                             = LARGE_NEGATIVE_INT;
  int num                              = LARGE_NEGATIVE_INT;
  int found                            = LARGE_NEGATIVE_INT;
  int n                                = LARGE_NEGATIVE_INT;
  int dim                              = LARGE_NEGATIVE_INT;
  int n_interior_and_boundary          = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);

  if ((vort=(double **)calloc(3,sizeof(double *)))==NULL)
  {
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  vort[0] = (double *)calloc(NPARTICLES,sizeof(double));
  vort[1] = (double *)calloc(NPARTICLES,sizeof(double));
  vort[2] = (double *)calloc(NPARTICLES,sizeof(double));
  for (i=0;i<NPARTICLES;i++)
  {
    vort[0][i] = LARGE_NEGATIVE_DOUBLE;
    vort[1][i] = LARGE_NEGATIVE_DOUBLE;
    vort[2][i] = LARGE_NEGATIVE_DOUBLE;
  }

  if (DIMENSIONS == 1)
  {
    vort[0][i] = 0.0;
    vort[1][i] = 0.0;
    vort[2][i] = 0.0;
  }
  if (DIMENSIONS == 2)
  {
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      i      = node_info[rank].interior_and_boundary[index];
      x_i    = particles[0].x[0][i];
      z_i    = particles[0].x[2][i];
      h_i    = particles[0].h[i];
      sum1   = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          rho_j  = particles[0].rho[j];
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
          rho_j  = x_particles[0].rho[l];
          x_j    = x_particles[0].x[0][l];
          z_j    = x_particles[0].x[2][l];
          vx_j   = x_particles[0].v[0][l];
          vz_j   = x_particles[0].v[2][l];
          h_j    = x_particles[0].h[l];
          m_j    = x_particles[0].m[l];
        }
        h_ij  = 0.5*(h_i+h_j);
        r_ij  = sqrt((x_i-x_j)*(x_i-x_j)
              +      (z_i-z_j)*(z_i-z_j) );
        p     = m_j*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH);
        fact1 = p*vx_j/rho_j;
        fact2 = p*vz_j/rho_j;
        sum1  = sum1 - fact1*dfdz(z_i,z_j,r_ij*h_ij) + fact2*dfdx(x_i,x_j,r_ij*h_ij);
      }
      vort[0][i] = 0.0;
      vort[1][i] = sum1;
      vort[2][i] = 0.0;
      if (is_nan_or_inf(sum1,(char *)"vort0",i) == EXIT_FAILURE) goto RETURN;
    }
  }
  if (DIMENSIONS == 3)
  {
    n_interior_and_boundary = node_info[rank].n_interior_and_boundary;
    for (index=0;index<n_interior_and_boundary;index++)
    {
      i      = node_info[rank].interior_and_boundary[index];
      x_i    = particles[0].x[0][i];
      y_i    = particles[0].x[1][i];
      z_i    = particles[0].x[2][i];
      h_i    = particles[0].h[i];
      sum0   = 0.0;
      sum1   = 0.0;
      sum2   = 0.0;
      for (k=0;k<NN_K;k++)
      {
        nn_ik  = particles[0].nn[i][k];
        node   = nn_ik/NPARTICLES;
        j      = nn_ik%NPARTICLES;
        if (node == rank)
        {
          rho_j  = particles[0].rho[j];
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
          rho_j  = x_particles[0].rho[l];
          x_j    = x_particles[0].x[0][l];
          y_j    = x_particles[0].x[1][l];
          z_j    = x_particles[0].x[2][l];
          vx_j   = x_particles[0].v[0][l];
          vy_j   = x_particles[0].v[1][l];
          vz_j   = x_particles[0].v[2][l];
          h_j    = x_particles[0].h[l];
          m_j    = x_particles[0].m[l];
        }
        h_ij  = 0.5*(h_i+h_j);
        r_ij  = sqrt((x_i-x_j)*(x_i-x_j)
              +      (y_i-y_j)*(y_i-y_j)
              +      (z_i-z_j)*(z_i-z_j));
        p     = m_j*dWdf(r_ij/h_ij,h_ij,dim,KERNEL_WIDTH);
        fact0 = p*vx_j/rho_j;
        fact1 = p*vy_j/rho_j;
        fact2 = p*vz_j/rho_j;
        sum0  = sum0 + fact1*dfdz(z_i,z_j,r_ij*h_ij) - fact2*dfdy(x_i,x_j,r_ij*h_ij);
        sum1  = sum1 - fact0*dfdz(z_i,z_j,r_ij*h_ij) + fact2*dfdx(x_i,x_j,r_ij*h_ij);
        sum2  = sum2 + fact0*dfdy(z_i,z_j,r_ij*h_ij) - fact1*dfdx(x_i,x_j,r_ij*h_ij);
      }
      vort[0][i] = sum0;
      vort[1][i] = sum1;
      vort[2][i] = sum2;
      if (is_nan_or_inf(sum0,(char *)"vort0",i) == EXIT_FAILURE) goto RETURN;
      if (is_nan_or_inf(sum1,(char *)"vort1",i) == EXIT_FAILURE) goto RETURN;
      if (is_nan_or_inf(sum2,(char *)"vort2",i) == EXIT_FAILURE) goto RETURN;
    }
  }

RETURN:
  verbosity(2,fname,pars);
  return vort;
}
