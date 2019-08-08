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

#include "assemble_pbob.h"

PBOB *Assemble_PBOB(PARS *pars,double time,int cluster_size)
{
  extern NODE_INFO *node_info;

  FILE *kernel_file_ptr                = NULL;
  FILE *configure_ac_file_ptr          = NULL;
  PBOB *pbob                           = NULL;

  char fname[]                         = "...Assemble_PBOB";
  char *cluster_name                   = NULL;
  char *kernel_file_name               = NULL;
  char *configure_ac_file_name         = NULL;
  char *kernel_function                = NULL;
  char line[MAX_CHARS]                 = "\0";
  char string[33]                      = "\0";
  char *s1                             = NULL;

  u_int32_t endian                     = LARGE_POSITIVE_INT;

  int i                                = LARGE_NEGATIVE_INT;
  int pad_lines                        = LARGE_NEGATIVE_INT;
  int pad_spaces                       = LARGE_NEGATIVE_INT;
  int len                              = LARGE_NEGATIVE_INT;
  int len_kf                           = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);
  if ((pbob=(PBOB *)calloc(1,sizeof(PBOB)))==NULL)
  {
    printf(" %s(): -unable to allocate memory for PBOB struct \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
/*                                                                           */
/*                 short_title                                               */
/*                                                                           */ 
  snprintf((char *)pbob[0].short_title,80,"%s",pars[0].short_title);
/*                                                                           */
/*                 ascii_header                                              */
/*                                                                           */ 
  strncpy((char *)pbob[0].ascii_header,(char *)pars[0].ascii_header[0],80);
  for (i=1;i<39;i++)
  {
    strncat((char *)pbob[0].ascii_header,(char *)pars[0].ascii_header[i],80); 
  }
  strncat((char *)pbob[0].ascii_header,(char *)"################### ",20);
  strncat((char *)pbob[0].ascii_header,(char *)sph_git_commit_hash,40);
  strncat((char *)pbob[0].ascii_header,(char *)" ###################",20);
/*                                                                           */
/*                 kernel_function                                           */
/*                                                                           */
  kernel_file_name  = (char *)calloc(MAX_CHARS,sizeof(char));
  kernel_function   = (char *)calloc(6401,sizeof(char));
  strncpy(kernel_function,(char *)"\n",1);
  strncat(kernel_function,(char *)"|************************ KERNEL C FUNCTION **********************************|\n",80);
  strncat(kernel_function,(char *)"                                                                               \n",80);
  if (DIMENSIONS == 1)
  {
    sprintf(kernel_file_name,"%s/libsrc/libsph/w1D.c",prefix);
  }
  if (DIMENSIONS == 2)
  {
    sprintf(kernel_file_name,"%s/libsrc/libsph/w2D.c",prefix);
  }
  if (DIMENSIONS == 3)
  {
    sprintf(kernel_file_name,"%s/libsrc/libsph/w3D.c",prefix);
  }
  

  
  if ((kernel_file_ptr=fopen(kernel_file_name,"r")) != NULL)
  {
    len = 0;
    while(fgets(line,MAX_CHARS,kernel_file_ptr) != NULL)
    {
      strncat(kernel_function,(char *)line,strlen(line));
      len = len + strlen(line);
      memset((char *)line,'\0',MAX_CHARS);
    }
    len_kf = strlen(kernel_function);
    strcpy((char *)kernel_function+len_kf-1,(char *)" ");
    pad_spaces = 80 - (len%80)-1;
    pad_lines = 65 - (3+len/80+1);
    for(i=0;i<pad_spaces;i++)
    {
      strncat(kernel_function,(char *)" ",1);
    }
    strncat(kernel_function,(char *)"\n",1);
    for(i=0;i<pad_lines;i++)
    {
      strncat(kernel_function,(char *)"|                                                                             |\n",80);
    }
    fclose(kernel_file_ptr);
  }
  else
  {
    strncat(kernel_function,(char *)"|                               UNAVAILABLE                                   |\n",80);
    for (i=0;i<61;i++)
    {
      strncat(kernel_function,(char *)"|                                                                             |\n",80);
    }
  }
  strncat(kernel_function,(char *)"\\*****************************************************************************/\n\0",81);

  snprintf((char *)pbob[0].kernel_function,6400,"%s",kernel_function); 
/*                                                                           */
/*                 endian_str                                                */
/*                                                                           */
  endian =  (u_int32_t)BigOrLittleEndian();
  if (endian == 1)
  {
    sprintf((char *)pbob[0].endian_str,"little endian   ");
  }
  else if  (endian == 0)
  {
    sprintf((char *)pbob[0].endian_str,"big endian      ");
  }
  else
  {
    printf(" %s(): -error return from BigOrLittleEndian \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
/*                                                                           */
/*                 pbob_version                                              */
/*                                                                           */

  configure_ac_file_name  = (char *)calloc(MAX_CHARS,sizeof(char));
  sprintf(configure_ac_file_name,"%s/../configure.ac",prefix);
  if ((configure_ac_file_ptr=fopen(configure_ac_file_name,"r")) != NULL)
  {
    s1 = (char *)calloc(MAX_CHARS,sizeof(char));
    fgets(line,MAX_CHARS,configure_ac_file_ptr);
    fgets(line,MAX_CHARS,configure_ac_file_ptr);
    CopyAfterEqual(s1,(char *)line);
    len = strlen(s1);
    if (len == 5)sprintf(string,"%5s                           ",s1);
    if (len == 6)sprintf(string,"%6s                          ",s1);
    if (len == 7)sprintf(string,"%7s                         ",s1);
    if (len == 8)sprintf(string,"%8s                        ",s1);
    if (len == 9)sprintf(string,"%9s                       ",s1);
    if (len ==10)sprintf(string,"%10s                      ",s1);
    if (len ==11)sprintf(string,"%11s                     ",s1);
    if (len ==12)sprintf(string,"%12s                    ",s1);
    if (len ==13)sprintf(string,"%13s                   ",s1);
    if (len ==14)sprintf(string,"%14s                  ",s1);
    if (len ==15)sprintf(string,"%15s                 ",s1);
    if (len ==16)sprintf(string,"%16s                ",s1);
    if (len ==17)sprintf(string,"%17s               ",s1);
    strncpy((char *)pbob[0].pbob_version,string,33);
    fclose(configure_ac_file_ptr);
    free(s1);
  }
  else
  {
    sprintf((char *)pbob[0].pbob_version,"-.-.-                           ");
  }
/*                                                                           */
/*                 cluster_name                                              */
/*                                                                           */
  cluster_name = getenv("CLUSTER_NAME");
  sprintf(string,"%31s\n",(char *)cluster_name);
  strncpy(pbob[0].cluster_name,string,32);
/*                                                                           */
/*                 endian_int                                                */
/*                                                                           */
  pbob[0].endian_int = endian;
/*                                                                           */
/*                 cluster_size                                              */
/*                                                                           */
  pbob[0].cluster_size = (u_int32_t)cluster_size+1;
/*                                                                           */
/*                 dimensions                                                */
/*                                                                           */
  pbob[0].dimensions = (u_int32_t)DIMENSIONS;
/*                                                                           */
/*                 first_particle_byte_offset                                */
/*                                                                           */

/*
  pbob[0].first_particle_byte_offset = 3201    // ascii_header
                                     + 6401    // kernel_function
                                     + 81      // short_title
                                     + 17      // endian_str
                                     + 33      // pbob_version 
                                     + 33      // cluster_name
                                     + 17      // length_units
                                     + 17      // time_units
                                     + 17      // mass_units
                                     + 17      // internal energy units
                                     + 81      // sph_git_commit_hash
                                     + (10*17) // 10 x unused 17-byte-char
                                     + 3       // pad to word boundary may need to set to 1,2,3 or 4


                                     + 8       // total_particles
                                     + 4       // dimensions
                                     + 4       // endian_int
                                     + 4       // cluster_size 
                                     + 4       // number_of_time_slices
                                     + 4       // first_particle_byte_offset
                                     + 4       // particle_length_bytes
                                     + 4       // nn_k

                                     + (10*4)  // 10 x unused ints

                                     + 4       // time
                                     + 4       // kernel_width
                                     + 4       //  acceleration  -g at sea level
                                     + 4       //  X0
                                     + 4       //  X1
                                     + 4       //  Y0
                                     + 4       //  Y1
                                     + 4       //  Z0
                                     + 4       //  Z1
                                     + 4       //  alpha
                                     + 4       //  beta
                                     + 4       //  gamma 
                                     + 4       //  kappa
                                     + 4       //  epsilon
                                     + 4       //  eta
                                     + 4       //  g1 
                                     + 4       //  g2 
                                     + (10*4)  // 10 x unused floats
                                     + 8;      // pad to 8-byte word boundary
  pbob[0].first_particle_byte_offset += (cluster_size+1)*(33 + 17 + 6);
*/
  pbob[0].first_particle_byte_offset = (int)sizeof(PBOB) + 
                                       (int)sizeof(NODE_DESCRIP)*(cluster_size+1);
/*                                                                           */
/*                 particle_length_bytes                                     */
/*                                                                           */
  pbob[0].particle_length_bytes     = 4       // 4-char pad
                                    + 8       // index
                                    + 4       // species
                                    + 4       // start_node
                                    + 4       // end_node
                                    + 4       // time_slice
                                    + 4       // time
                                    + 4       // x
                                    + 4       // y
                                    + 4       // z
                                    + 4       // vx
                                    + 4       // vy 
                                    + 4       // vz
                                    + 4       // ax 
                                    + 4       // ay 
                                    + 4       // az
                                    + 4       // vortx
                                    + 4       // vorty
                                    + 4       // vortz
                                    + 4       // U
                                    + 4       //dUdt 
                                    + 4       // h
                                    + 4       // rho
                                    + 4       // p
                                    + 4;      // m
/*                                                                           */
/*                 total particles                                           */
/*                                                                           */
  pbob[0].total_particles = (u_int64_t)pars[0].TOTAL_PARTICLES;
/*                                                                           */
/*                 nn_k                                                      */
/*                                                                           */
  pbob[0].nn_k = (u_int32_t)NN_K;
/*                                                                           */
/*                 10 x unused ints                                          */
/*                                                                           */
  pbob[0].unused_int1  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int2  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int3  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int4  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int5  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int6  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int7  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int8  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int9  = (int32_t)LARGE_NEGATIVE_INT;
  pbob[0].unused_int10 = (int32_t)LARGE_NEGATIVE_INT;
/*                                                                           */
/*                 length_units                                              */
/*                                                                           */
  sprintf((char *)pbob[0].length_units,"%16s",length_units);
/*                                                                           */
/*                 time_units                                                */
/*                                                                           */
  sprintf((char *)pbob[0].time_units,"%16s",time_units);
/*                                                                           */
/*                 mass_units                                                */
/*                                                                           */
  sprintf((char *)pbob[0].mass_units,"%16s",mass_units);
/*                                                                           */
/*                 internal_energy_units                                     */
/*                                                                           */
  sprintf((char *)pbob[0].internal_energy_units,"%16s",internal_energy_units);
/*                                                                           */
/*                 sph_git_commit_hash                                       */
/*                                                                           */
  sprintf((char *)pbob[0].sph_git_commit_hash,"%40s",sph_git_commit_hash);
/*                                                                           */
/*                 10 x unused chars                                         */
/*                                                                           */
  sprintf((char *)pbob[0].unused_str1,"          unused");
  sprintf((char *)pbob[0].unused_str2,"          unused");
  sprintf((char *)pbob[0].unused_str3,"          unused");
  sprintf((char *)pbob[0].unused_str4,"          unused");
  sprintf((char *)pbob[0].unused_str5,"          unused");
  sprintf((char *)pbob[0].unused_str6,"          unused");
  sprintf((char *)pbob[0].unused_str7,"          unused");
  sprintf((char *)pbob[0].unused_str8,"          unused");
  sprintf((char *)pbob[0].unused_str9,"          unused");
  sprintf((char *)pbob[0].unused_str10,"          unused");
  strncpy(pbob[0].pad,(char *)"\0",4);
/*                                                                           */
/*                 time                                                      */
/*                                                                           */
  pbob[0].time = (float32_t)time;
/*                                                                           */
/*                 kernel_width                                              */
/*                                                                           */
  pbob[0].kernel_width = (float32_t)KERNEL_WIDTH;
/*                                                                           */
/*                 gravity                                                    */
/*                                                                           */
  pbob[0].gravity = (float32_t)GRAVITY;
/*                                                                           */
/*                 X0                                                        */
/*                                                                           */
  pbob[0].X0 = (float32_t)X0;
/*                                                                           */
/*                 X1                                                        */
/*                                                                           */
  pbob[0].X1 = (float32_t)X1;
/*                                                                           */
/*                 Y0                                                        */
/*                                                                           */
  pbob[0].Y0 = (float32_t)Y0;
/*                                                                           */
/*                 Y1                                                        */
/*                                                                           */
  pbob[0].Y1 = (float32_t)Y1;
/*                                                                           */
/*                 Z0                                                        */
/*                                                                           */
  pbob[0].Z0 = (float32_t)Z0;
/*                                                                           */
/*                 Z1                                                        */
/*                                                                           */
  pbob[0].Z1 = (float32_t)Z1;
/*                                                                           */
/*                 ALPHA                                                     */
/*                                                                           */
  pbob[0].alpha = (float32_t)ALPHA;
/*                                                                           */
/*                 BETA                                                      */
/*                                                                           */
  pbob[0].beta = (float32_t)BETA;
/*                                                                           */
/*                 ETA                                                       */
/*                                                                           */
  pbob[0].eta = (float32_t)ETA;
/*                                                                           */
/*                 G1                                                        */
/*                                                                           */
  pbob[0].g1 = (float32_t)G1;
/*                                                                           */
/*                 G2                                                        */
/*                                                                           */
  pbob[0].g2 = (float32_t)G2;
/*                                                                           */
/*                 gamma                                                     */
/*                                                                           */
  pbob[0].gamma = (float32_t)GAMMA;
/*                                                                           */
/*                 KAPPA                                                     */
/*                                                                           */
  pbob[0].kappa = (float32_t)KAPPA;
/*                                                                           */
/*                 EPSILON                                                   */
/*                                                                           */
  pbob[0].epsilon = (float32_t)EPSILON;
/*                                                                           */
/*                 10 X floats                                               */
/*                                                                           */
  pbob[0].unused_float1  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float2  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float3  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float4  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float5  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float6  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float7  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float8  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float9  = (float32_t)LARGE_NEGATIVE_DOUBLE;
  pbob[0].unused_float10 = (float32_t)LARGE_NEGATIVE_DOUBLE;

  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);
  if (configure_ac_file_name)
  {
    free(configure_ac_file_name);
    configure_ac_file_name = NULL;
  }
  if (kernel_file_name)
  {
    free(kernel_file_name);
    kernel_file_name = NULL;
  }
  if (kernel_function)
  {
    free(kernel_function);
    kernel_function = NULL;
  }
  return pbob;
}
