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

#ifndef BOBSSPH_NODE_INFO_H
#define BOBSSPH_NODE_INFO_H

typedef struct
{
  char   node_name[64];
  double burn_r;
  double burn_l;
  double start_burn_r;
  double start_burn_l;
  double burn_delta_l;
  double burn_delta_r;
  double burn_r0;
  double burn_r1;
  double burn_r2;
  double burn_r3;
  double burn_l0;
  double burn_l1;
  double burn_l2;
  double burn_l3;
  double *h_pts;
  int    nparticles;
  int    burn_status;
  int    offset;
  int    number_of_doubles;
  int    number_of_ints;
  int    n_interior;
  int    n_boundary;
  int    n_ghost;
  int    n_marker;
  int    y;
  int    n_interior_and_boundary;
  int    inv_raw_index_set;
  int    raw_index_set;
  int    species_set;
  int    boundary_set;
  int    interior_set;
  int    interior_and_boundary_set;
  int    ghost_set;
  int    ghost_mirror_set;
  int    ghost_x_set;
  int    ghost_y_set;
  int    ghost_z_set;
  int    burn_A_set;
  int    burn_B_set;
  int    burn_E_set;
  int    burn_F_set;
  int   *raw_index;
  int   *inv_raw_index;
  int   *species;
  int   *boundary;
  int   *interior;
  int   *interior_and_boundary;
  int   *ghost;
  int   *ghost_mirror;
  int   *ghost_x;
  int   *ghost_y;
  int   *ghost_z;
  int    n_A;
  int    n_B;
  int    n_E;
  int    n_F;
  int   *burn_A;
  int   *burn_B;
  int   *burn_E;
  int   *burn_F;
  int   *contains_burn_l;
  int   *contains_burn_r;
  int   *marker;
  int   n_contains_burn_l;
  int   n_contains_burn_r;
  int   total_particles;
}NODE_INFO;

#endif /* BOBSSPH_NODE_INFO_H */
