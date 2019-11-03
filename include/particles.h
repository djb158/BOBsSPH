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

#ifndef BOBSSPH_PARTICLES_H
#define BOBSSPH_PARTICLES_H

#include "nn_index.h"

#define STEPS_TO_REINDEX  (2)
#define N_WIN             (2)

typedef struct
{
  double  **x;
  double  **v;
  double  **dvdt;
  double   *m;
  double   *h;
  double   *p;
  double   *rho;
  double   *U;
  double   *dUdt;
  double   *divV;
  double    t;
  int     **nn;
  int       n_offnode_neighbours;
  int      *nn_k;
  int      *raw_index;
  int      *species;
  int       rank;
  int       step;
  int       steps_to_reindex;
  int       number_of_doubles;
  int       number_of_ints;
  NN_INDEX *nn_index;
} PARTICLES;
/*
 *   variable             start byte              end byte     ptr offset
 *   x0                    0                      8*N-1            0
 *   x1                    8*N                   16*N-1            N
 *   x3                   16*N                   24*N-1          2*N
 *   v0                   24*N                   32*N-1          3*N
 *   v1                   32*N                   40*N-1          4*N
 *   v2                   40*N                   48*N-1          5*N
 *   dvdt0                48*N                   56*N-1          6*N
 *   dvdt1                56*N                   64*N-1          7*N
 *   dvdt2                64*N                   72*N-1          8*N
 *   m                    72*N                   80*N-1          9*N
 *   mu                   80*N                   88*N-1         10*N
 *   E                    88*N                   96*N-1         11*N
 *   h                    96*N                  104*N-1         12*N
 *   p                   104*N                  112*N-1         13*N
 *   rho                 112*N                  120*N-1         14*N
 *   U                   120*N                  128*N-1         15*N
 *   dUdt                128*N                  136*N-1         16*N
 *   divV                136*N                  144*N-1         17*N
 *   t                   144*N                  144*N+7         18*N
 */

#endif  /*  BOBSSPH_PARTICLES_H */
