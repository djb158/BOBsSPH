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

#ifndef BOBSSPH_PARS_H
#define BOBSSPH_PARS_H

typedef struct 
{
 char out_dir[MAX_CHARS];
 char prefix[MAX_CHARS];
 char ascii_header[40][80];
 char short_title[80];
 char length_units[17];
 char time_units[17];
 char mass_units[17];
 char internal_energy_units[17];
 char sph_git_commit_hash[41];
 double GRAVITY;
 double X0;
 double X1;
 double Y0;
 double Y1;
 double Z0;
 double Z1;
 double ACCURACY;
 double ALPHA;
 double GAMMA;
 double BETA;
 double ETA;
 double EPSILON;
 double G1;
 double G2;
 double D;
 double H0;
 double NN_EPS;
 double KAPPA;
 double PARTICLE_MASS;
 double OFFSET;
 double KERNEL_WIDTH;
 int    NEIGHBOUR_THREADS;
 int    COMPUTE_THREADS;
 int    N_STEPS;
 int    TIME_STEPS_TO_WRITE;
 int    RESTART;
 int    args_defined;
 int    KERNEL_ID;
 int    DIMENSIONS;
 int    PARTICLES_IN_X;
 int    PARTICLES_IN_Y;
 int    PARTICLES_IN_Z;
 int    PARTICLES_IN_Z_H;
 int    NPARTICLES;
 int    NPARTICLES_EXTRA;
 int    N_CENTRE;
 int    NN_K;
 int    ZERO;
 int    ZERO_H;
 int    CENTRE_POINT;
 int    EXTRA;
 int    rank;
 int    TOTAL_PARTICLES;
 int    TOTAL_PARTICLES_GUESS;
 int    VERBOSITY;
}PARS;

#endif
