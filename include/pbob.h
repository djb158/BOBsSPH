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

#ifndef BOBSSPH_PBOB_H
#define BOBSSPH_PBOB_H

typedef struct
{
  char           ascii_header[3201];
  char           kernel_function[6401];
  char           short_title[81];
  char           endian_str[17];
  char           pbob_version[33];
  char           cluster_name[33];
  char           length_units[17];
  char           time_units[17];
  char           mass_units[17];
  char           internal_energy_units[17];
  char           sph_git_commit_hash[81];
  char           unused_str1[17];
  char           unused_str2[17];
  char           unused_str3[17];
  char           unused_str4[17];
  char           unused_str5[17];
  char           unused_str6[17];
  char           unused_str7[17];
  char           unused_str8[17];
  char           unused_str9[17];
  char           unused_str10[17];
/*                                                                           */
/*                 Need to pad to word boundary: if other variables are added*/
/*                 4 may need to change to 1,2,or, 3                         */
/*                                                                           */
  char           pad[4];

  u_int64_t      total_particles;
  u_int32_t      dimensions;
  u_int32_t      endian_int;
  u_int32_t      cluster_size;
  u_int32_t      number_of_time_slices;
  u_int32_t      first_particle_byte_offset;
  u_int32_t      particle_length_bytes;
  u_int32_t      nn_k;

  int32_t        unused_int1;
  int32_t        unused_int2;
  int32_t        unused_int3;
  int32_t        unused_int4;
  int32_t        unused_int5;
  int32_t        unused_int6;
  int32_t        unused_int7;
  int32_t        unused_int8;
  int32_t        unused_int9;
  int32_t        unused_int10;

  float32_t      time;
  float32_t      kernel_width;
  float32_t      gravity;
  float32_t      X0;
  float32_t      X1;
  float32_t      Y0;
  float32_t      Y1;
  float32_t      Z0;
  float32_t      Z1;
  float32_t      alpha;
  float32_t      beta;
  float32_t      gamma;
  float32_t      kappa;
  float32_t      epsilon;
  float32_t      eta;
  float32_t      g1;
  float32_t      g2;
  float32_t      unused_float1;
  float32_t      unused_float2;
  float32_t      unused_float3;
  float32_t      unused_float4;
  float32_t      unused_float5;
  float32_t      unused_float6;
  float32_t      unused_float7;
  float32_t      unused_float8;
  float32_t      unused_float9;
  float32_t      unused_float10;
/*                                                                           */
/*                 Note: on some compilers the total struct length needs to  */
/*                 be divisible by 8 (by inclusion of u_int64_t type) so a   */
/*                 a char pad[x] may need to be introduced here              */
/*                                                                           */
  char           pad1[8];
}PBOB;

#endif /* BOBSSPH_PBOB_H */
