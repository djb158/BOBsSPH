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

#ifndef BOBSSPH_PARTICLE_H
#define BOBSSPH_PARTICLE_H

typedef struct
{
/*                                                                           */
/*                 Note: on some compilers the total struct length needs to  */
/*                 be divisible by 8 (by inclusion of u_int64_t type ?) so a */
/*                 char pad[x] may need to be introduced here.               */
/*                 May also be a result of D_FILE_OFFSET_BITS=64 requirement */
/*                 for large file support                                    */
/*                                                                           */
  u_int64_t     index;
  u_int32_t     species;
  u_int32_t     start_node;
  u_int32_t     end_node;
  u_int32_t     time_slice;
  float32_t     time;
  float32_t     x;
  float32_t     y;
  float32_t     z;
  float32_t     vx;
  float32_t     vy;
  float32_t     vz;
  float32_t     ax;
  float32_t     ay;
  float32_t     az;
  float32_t     vortx;
  float32_t     vorty;
  float32_t     vortz;
  float32_t     U;
  float32_t     dUdt;
  float32_t     h;
  float32_t     rho;
  float32_t     p;
  float32_t     m;
  char          pad[4];
}PARTICLE;

#endif /* BOBSSPH_PARTICLE_H */
