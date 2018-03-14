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

#ifndef BOBSSPH_PARS_INCLUDE_H
#define BOBSSPH_PARS_INCLUDE_H

  char out_dir[MAX_CHARS]              = "\0";
  char prefix[MAX_CHARS]               = "\0";
  char ascii_header[40][80];
  char short_title[80]                 = "\0";
  char length_units[16]                = "\0";
  char time_units[16]                  = "\0";
  char mass_units[16]                  = "\0";
  char internal_energy_units[17]       = "\0";
  char sph_git_commit_hash[41]         = "\0";

  int ii                               = 0;
  int ascii_header_error               = 0;
  int N_STEPS                          = LARGE_NEGATIVE_INT;
  int TIME_STEPS_TO_WRITE              = LARGE_NEGATIVE_INT;
  int ZERO                             = LARGE_NEGATIVE_INT;
  int ZERO_H                           = LARGE_NEGATIVE_INT;
  int NN_K                             = LARGE_NEGATIVE_INT;
  int KERNEL_ID                        = LARGE_NEGATIVE_INT;
  int DIMENSIONS                       = LARGE_NEGATIVE_INT;
  int PARTICLES_IN_X                   = LARGE_NEGATIVE_INT;
  int PARTICLES_IN_Y                   = LARGE_NEGATIVE_INT;
  int PARTICLES_IN_Z                   = LARGE_NEGATIVE_INT;
  int PARTICLES_IN_Z_H                 = LARGE_NEGATIVE_INT;
  int NPARTICLES                       = LARGE_NEGATIVE_INT;
  int NPARTICLES_EXTRA                 = LARGE_NEGATIVE_INT;
  int N_CENTRE                         = LARGE_NEGATIVE_INT;
  int args_defined                     = LARGE_NEGATIVE_INT;
  int RESTART                          = LARGE_NEGATIVE_INT;
  int CENTRE_POINT                     = LARGE_NEGATIVE_INT;
  int EXTRA                            = LARGE_NEGATIVE_INT;
  int rank                             = LARGE_NEGATIVE_INT;
  int TOTAL_PARTICLES                  = LARGE_NEGATIVE_INT;
  int VERBOSITY                        = LARGE_NEGATIVE_INT;
  int NEIGHBOUR_THREADS                = LARGE_NEGATIVE_INT;
  int COMPUTE_THREADS                  = LARGE_NEGATIVE_INT;
  int TOTAL_PARTICLES_GUESS            = LARGE_NEGATIVE_INT;

  double X0                            = LARGE_NEGATIVE_DOUBLE;
  double X1                            = LARGE_NEGATIVE_DOUBLE;
  double Y0                            = LARGE_NEGATIVE_DOUBLE;
  double Y1                            = LARGE_NEGATIVE_DOUBLE;
  double Z0                            = LARGE_NEGATIVE_DOUBLE;
  double Z1                            = LARGE_NEGATIVE_DOUBLE;
  double NN_EPS                        = LARGE_NEGATIVE_DOUBLE;
  double ALPHA                         = LARGE_NEGATIVE_DOUBLE;
  double GAMMA                         = LARGE_NEGATIVE_DOUBLE;
  double BETA                          = LARGE_NEGATIVE_DOUBLE;
  double ETA                           = LARGE_NEGATIVE_DOUBLE;
  double EPSILON                       = LARGE_NEGATIVE_DOUBLE;
  double G1                            = LARGE_NEGATIVE_DOUBLE;
  double G2                            = LARGE_NEGATIVE_DOUBLE;
  double KAPPA                         = LARGE_NEGATIVE_DOUBLE;
  double D                             = LARGE_NEGATIVE_DOUBLE;
  double H0                            = LARGE_NEGATIVE_DOUBLE;
  double PARTICLE_MASS                 = LARGE_NEGATIVE_DOUBLE; 
  double ACCURACY                      = LARGE_NEGATIVE_DOUBLE;
  double OFFSET                        = LARGE_NEGATIVE_DOUBLE;
  double KERNEL_WIDTH                  = LARGE_NEGATIVE_DOUBLE;
  double GRAVITY                       = LARGE_NEGATIVE_DOUBLE;

  if (pars == NULL)
  {
    goto RETURN;
  }
  TOTAL_PARTICLES       = pars[0].TOTAL_PARTICLES;
  NPARTICLES            = pars[0].NPARTICLES;
  TOTAL_PARTICLES_GUESS = pars[0].TOTAL_PARTICLES_GUESS;
  for (ii=0;ii<40;ii++)
  {
    strcpy(ascii_header[ii],(char *)"\0");
    if (pars[0].ascii_header[ii])
    {
      strncpy((char *)ascii_header[ii],(char *)pars[0].ascii_header[ii],80);
    }
    if (strcmp(ascii_header[ii],"\0")==0)
    {
      ascii_header_error = 1;
    }
  }

  if (pars[0].short_title)
  {
    strcpy((char *)short_title,(char *)pars[0].short_title);
  }
  if (pars[0].out_dir)
  {
    strcpy((char *)out_dir,(char *)pars[0].out_dir);
  }
  if (pars[0].prefix)
  {
    strcpy((char *)prefix,(char *)pars[0].prefix);
  }
  if (pars[0].length_units)
  {
    strncpy((char *)length_units,(char *)pars[0].length_units,16);
  }
  if (pars[0].time_units)
  {
    strncpy((char *)time_units,(char *)pars[0].time_units,16);
  }
  if (pars[0].mass_units)
  {
    strncpy((char *)mass_units,(char *)pars[0].mass_units,16);
  }
  if (pars[0].internal_energy_units)
  {
    strncpy((char *)internal_energy_units,(char *)pars[0].internal_energy_units,16);
  }
  if (pars[0].sph_git_commit_hash)
  {
    strncpy((char *)sph_git_commit_hash,(char *)pars[0].sph_git_commit_hash,40);
  }

  if ( (pars == NULL)
                              ||
       (((ALPHA=pars[0].ALPHA)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((GAMMA=pars[0].GAMMA)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((BETA=pars[0].BETA)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((ETA=pars[0].ETA)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((EPSILON=pars[0].EPSILON)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((G1=pars[0].G1)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((G2=pars[0].G2)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((D=pars[0].D)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((H0=pars[0].H0)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((NN_EPS=pars[0].NN_EPS)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((ACCURACY=pars[0].ACCURACY)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((X0=pars[0].X0)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((X1=pars[0].X1)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((Y0=pars[0].Y0)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((Y1=pars[0].Y1)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((Z0=pars[0].Z0)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((Z1=pars[0].Z1)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((KAPPA=pars[0].KAPPA)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((PARTICLE_MASS=pars[0].PARTICLE_MASS)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       (((GRAVITY=pars[0].GRAVITY)-LARGE_NEGATIVE_DOUBLE)<EPSILON_FLOAT)
                              ||
       ((KERNEL_ID=pars[0].KERNEL_ID)==LARGE_NEGATIVE_INT)
                              ||
       ((N_STEPS=pars[0].N_STEPS)==LARGE_NEGATIVE_INT)
                              ||
       ((TIME_STEPS_TO_WRITE=pars[0].TIME_STEPS_TO_WRITE)==LARGE_NEGATIVE_INT)
                              ||
       ((DIMENSIONS=pars[0].DIMENSIONS)==LARGE_NEGATIVE_INT)
                              ||
       ((PARTICLES_IN_X=pars[0].PARTICLES_IN_X)==LARGE_NEGATIVE_INT)
                              ||
       ((PARTICLES_IN_Y=pars[0].PARTICLES_IN_Y)==LARGE_NEGATIVE_INT)
                              ||
       ((PARTICLES_IN_Z=pars[0].PARTICLES_IN_Z)==LARGE_NEGATIVE_INT)
                              ||
       ((NN_K=pars[0].NN_K)==LARGE_NEGATIVE_INT)
                              ||
       ((ZERO=pars[0].ZERO)==LARGE_NEGATIVE_INT)
                              ||
       ((CENTRE_POINT=pars[0].CENTRE_POINT)==LARGE_NEGATIVE_INT)
                              ||
       ((EXTRA=pars[0].EXTRA)==LARGE_NEGATIVE_INT)
                              ||
       ((OFFSET=pars[0].OFFSET)==LARGE_NEGATIVE_DOUBLE)
                              ||
       ((KERNEL_WIDTH=pars[0].KERNEL_WIDTH)==LARGE_NEGATIVE_DOUBLE)
                              ||
       ((RESTART=pars[0].RESTART)==LARGE_NEGATIVE_INT)
                              ||
       ((args_defined=pars[0].args_defined)==LARGE_NEGATIVE_INT)
                              ||
       ((rank=pars[0].rank)==LARGE_NEGATIVE_INT)
                              ||
       ((PARTICLES_IN_Z_H=pars[0].PARTICLES_IN_Z_H)==LARGE_NEGATIVE_INT)
                              ||
       ((N_CENTRE=pars[0].N_CENTRE)==LARGE_NEGATIVE_INT)
                              ||
       ((VERBOSITY=pars[0].VERBOSITY)==LARGE_NEGATIVE_INT)
                              ||
       ((NEIGHBOUR_THREADS=pars[0].NEIGHBOUR_THREADS)==LARGE_NEGATIVE_INT)
                              ||
       ((COMPUTE_THREADS=pars[0].COMPUTE_THREADS)==LARGE_NEGATIVE_INT)
                              ||
       ((ZERO_H=pars[0].ZERO_H)==LARGE_NEGATIVE_INT)
                              ||
        (strcmp(out_dir,"\0")==0)
                              ||
        (strcmp(short_title,"\0")==0)
                              ||
        (strcmp(prefix,"\0")==0)
                              ||
        (strcmp(length_units,"\0")==0)
                              ||
        (strcmp(time_units,"\0")==0)
                              ||
        (strcmp(mass_units,"\0")==0)
                              ||
        (strcmp(internal_energy_units,"\0")==0)
                              ||
        (strcmp(sph_git_commit_hash,"\0")==0)
                              ||
        (ascii_header_error==1)
     )
  {
    printf(" %s(): -input parameters incorrectly formatted \n",fname);
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

#endif
