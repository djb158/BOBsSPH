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
|   Copyright (c) 2015,2016,2017,2018 David Brown                             |
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

#include "get_pars.h"

PARS *GetPars(int argc, char *argv[],int rank)
{
  extern int cluster_size;

  PARS *pars                           = NULL;

  FILE *par_ptr                        = NULL;

  char fname[]                         = "...GetPars";

  char *par_name                       = NULL;
  char *s1                             = NULL;
  char *string1                        = NULL;
  char line[MAX_CHARS]                 = "\0";
  char **ascii_header                  = NULL;

  int ZERO                             = LARGE_NEGATIVE_INT;
  int NN_K                             = LARGE_NEGATIVE_INT;
  int KERNEL_ID                        = LARGE_NEGATIVE_INT;
  int DIMENSIONS                       = LARGE_NEGATIVE_INT;
  int PARTICLES_IN_X                   = LARGE_NEGATIVE_INT;
  int PARTICLES_IN_Y                   = LARGE_NEGATIVE_INT;
  int PARTICLES_IN_Z                   = LARGE_NEGATIVE_INT;
  int args_defined                     = LARGE_NEGATIVE_INT;
  int RESTART                          = LARGE_NEGATIVE_INT;
  int CENTRE_POINT                     = LARGE_NEGATIVE_INT;
  int EXTRA                            = LARGE_NEGATIVE_INT;
  int i                                = LARGE_NEGATIVE_INT;
  int exit_status                      = EXIT_FAILURE;
  int N_STEPS                          = LARGE_NEGATIVE_INT;
  int TIME_STEPS_TO_WRITE              = LARGE_NEGATIVE_INT;
  int VERBOSITY                        = LARGE_NEGATIVE_INT;
  int NEIGHBOUR_THREADS                = LARGE_NEGATIVE_INT;
  int COMPUTE_THREADS                  = LARGE_NEGATIVE_INT;
  int len                              = LARGE_NEGATIVE_INT;
  int token_r                          = 0;
  int token_s                          = 0;

  double OFFSET                        = LARGE_NEGATIVE_DOUBLE;
  double KERNEL_WIDTH                  = LARGE_NEGATIVE_DOUBLE;
  double ACCURACY                      = LARGE_NEGATIVE_DOUBLE;
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
  double GRAVITY                       = LARGE_NEGATIVE_DOUBLE;

  if (rank != 0)
  {
    token_r = 1;
    MPI_Recv(&token_r,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    token_s = token_r;
    printf("Process %d received token %d from process %d\n",rank,token_s,rank-1);
  }
  else
  {
    token_s = -1;
  }

  pars = (PARS *)calloc(1,sizeof(PARS));

#ifdef SPH_GIT_COMMIT_HASH
  sprintf(pars[0].sph_git_commit_hash,"%40s",SPH_GIT_COMMIT_HASH);
  printf("Commit hash: %40s\n",SPH_GIT_COMMIT_HASH );
#else
  printf(" %s() unable to retrieve SPH_GIT_COMMIT_HASH, -aborting\n",fname);
  exit_status = EXIT_FAILURE;
  goto RETURN;
#endif

  par_name      = (char *)calloc(MAX_CHARS,sizeof(char));
  ascii_header  = (char **)calloc(40,sizeof(char *));
  for (i=0;i<40;i++)
  {
    ascii_header[i] = (char *)calloc(80,sizeof(char));
  }

  args_defined = 0;
  for (i=1;i<argc;i++)
  {
    if (ContainsString(argv[i],(char *)"par=")==TRUE)
    {
      string1       = (char *)calloc(MAX_CHARS,sizeof(char));
      memset(string1,'\0',MAX_CHARS);
      strcpy(string1,argv[i]);
      CopyAfterEqual(par_name,string1);
      args_defined++;
      Free_sph(string1);
    }
  }
  if (args_defined != 1)
  {
    printf(" Usage:  sph par=<filename>.par \n");
    exit_status = EXIT_FAILURE;
    if (pars)
    {
      Free_sph(pars);
      pars = NULL;
    }
    goto RETURN;
  }

  if ((par_ptr=fopen(par_name,"r")) == NULL)
  {
    printf(" %s():  -error opening %s \n",fname,par_name);
    exit_status = EXIT_FAILURE;
    if (pars)
    {
      Free_sph(pars);
      pars = NULL;
    }
    goto RETURN;
  }
/*                                                                           */
/*                 check if ascii header correctly formatted                 */
/*                                                                           */
  exit_status = EXIT_SUCCESS;
  i = 0;
  fgets(line,MAX_CHARS,par_ptr);
  strncpy(ascii_header[0],line,79);
  if (strncmp(ascii_header[0],(char *)"################################# ASCII HEADER#################################",79)!=0)
  {
    exit_status = EXIT_FAILURE;
  }
  for (i=1;i<39;i++)
  {
    fgets(line,MAX_CHARS,par_ptr);
    strncpy(ascii_header[i],line,80);
    if ( (strncmp(line,(char *)"#",1) != 0)
                     || 
        (strncmp((char *)line+78,(char *)"#\n",2) != 0) )
    {
      exit_status = EXIT_FAILURE;
    }
  }
  fgets(line,MAX_CHARS,par_ptr);
  strncpy(ascii_header[39],line,80);
  if (strncmp(ascii_header[39],(char *)"###############################################################################\n",80)!=0)
  {
    exit_status = EXIT_FAILURE;
  }
  if (exit_status == EXIT_FAILURE)
  {
    printf(" %s(): -par file %s ascii header incorrectly formatted \n",fname,par_name);
    if (pars)
    {
      Free_sph(pars);
      pars = NULL;
    }
    fclose(par_ptr);
    goto RETURN;
  }
  for (i=0;i<40;i++)
  {
    strncpy((char *)pars[0].ascii_header[i],(char *)ascii_header[i],80);
  }

  args_defined = 0;
  while(fgets(line,MAX_CHARS,par_ptr) != NULL)
  {
    s1 = (char *)calloc(MAX_CHARS,sizeof(char));
    sscanf(line,"%s",s1);
    string1 = (char *)calloc(MAX_CHARS,sizeof(char));
    memset(string1,'\0',MAX_CHARS);
    if(   (ContainsString(s1,(char *)"ALPHA=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      ALPHA = atof(string1);
      pars[0].ALPHA = ALPHA;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"GAMMA=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      GAMMA = atof(string1);
      pars[0].GAMMA = GAMMA;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"BETA=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      BETA = atof(string1);
      pars[0].BETA = BETA;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"ETA=")==TRUE)
                            &&
          (ContainsString(s1,(char *)"BETA=")==FALSE)
      )
    {
      CopyAfterEqual(string1,s1);
      ETA = atof(string1);
      pars[0].ETA = ETA;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"EPSILON=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      EPSILON = atof(string1);
      pars[0].EPSILON = EPSILON;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"G1=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      G1 = atof(string1);
      pars[0].G1 = G1;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"G2=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      G2 = atof(string1);
      pars[0].G2 = G2;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"D=")==TRUE)
                      &&
          (ContainsString(s1,(char *)"KERNEL_ID=")==FALSE) 
      )
    {
      CopyAfterEqual(string1,s1);
      D = atof(string1);
      pars[0].D = D;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"KERNEL_ID=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      KERNEL_ID = atoi(string1);
      pars[0].KERNEL_ID = KERNEL_ID;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"N_STEPS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      N_STEPS = atoi(string1);
      pars[0].N_STEPS = N_STEPS;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"TIME_STEPS_TO_WRITE=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      TIME_STEPS_TO_WRITE = atoi(string1);
      pars[0].TIME_STEPS_TO_WRITE = TIME_STEPS_TO_WRITE;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"H0=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      H0 = atof(string1);
      pars[0].H0 = H0;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"KAPPA=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      KAPPA = atof(string1);
      pars[0].KAPPA = KAPPA;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"PARTICLE_MASS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      PARTICLE_MASS = atof(string1);
      pars[0].PARTICLE_MASS = PARTICLE_MASS;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"GRAVITY=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      GRAVITY = atof(string1);
      pars[0].GRAVITY = GRAVITY;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"X0=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      X0 = atof(string1);
      pars[0].X0 = X0;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"X1=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      X1 = atof(string1);
      pars[0].X1 = X1;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"Y0=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      Y0 = atof(string1);
      pars[0].Y0 = Y0;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"Y1=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      Y1 = atof(string1);
      pars[0].Y1 = Y1;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"Z0=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      Z0 = atof(string1);
      pars[0].Z0 = Z0;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"Z1=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      Z1 = atof(string1);
      pars[0].Z1 = Z1;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"DIMENSIONS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      DIMENSIONS = atoi(string1);
      pars[0].DIMENSIONS = DIMENSIONS;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"VERBOSITY=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      VERBOSITY = atoi(string1);
      pars[0].VERBOSITY = VERBOSITY;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"NEIGHBOUR_THREADS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      NEIGHBOUR_THREADS = atoi(string1);
      pars[0].NEIGHBOUR_THREADS = NEIGHBOUR_THREADS;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"COMPUTE_THREADS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      COMPUTE_THREADS = atoi(string1);
      pars[0].COMPUTE_THREADS = COMPUTE_THREADS;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"PARTICLES_IN_X=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      PARTICLES_IN_X = atoi(string1);
      pars[0].PARTICLES_IN_X = PARTICLES_IN_X;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"PARTICLES_IN_Y=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      PARTICLES_IN_Y = atoi(string1);
      pars[0].PARTICLES_IN_Y = PARTICLES_IN_Y;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"PARTICLES_IN_Z=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      PARTICLES_IN_Z = atoi(string1);
      pars[0].PARTICLES_IN_Z = PARTICLES_IN_Z;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"NN_K=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      NN_K = atoi(string1);
      pars[0].NN_K = NN_K;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"ZERO=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      ZERO = atoi(string1);
      pars[0].ZERO = ZERO;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"CENTRE_POINT=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      CENTRE_POINT = atoi(string1);
      pars[0].CENTRE_POINT = CENTRE_POINT;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"EXTRA=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      EXTRA = atoi(string1);
      pars[0].EXTRA = EXTRA;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"NN_EPS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      NN_EPS = atof(string1);
      pars[0].NN_EPS = NN_EPS;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"ACCURACY=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      ACCURACY = atof(string1);
      pars[0].ACCURACY = ACCURACY;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"OFFSET=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      OFFSET = atof(string1);
      pars[0].OFFSET = OFFSET;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"KERNEL_WIDTH=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      KERNEL_WIDTH = atof(string1);
      pars[0].KERNEL_WIDTH = KERNEL_WIDTH;
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"out_dir=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      strcpy((char *)pars[0].out_dir,string1);
      pars[0].out_dir[MAX_CHARS-1] = '\0';
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"SHORT_TITLE=")==TRUE) )
    {
      CopyAfterEqual(string1,(char *)line);
      len = strlen(string1);
      string1[len-1] = '\0';
      snprintf(pars[0].short_title,79,"%s",string1);
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"prefix=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      strcpy((char *)pars[0].prefix,string1);
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"LENGTH_UNITS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      strncpy((char *)pars[0].length_units,string1,16);
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"TIME_UNITS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      strncpy((char *)pars[0].time_units,string1,16);
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"MASS_UNITS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      strncpy((char *)pars[0].mass_units,string1,16);
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"INTERNAL_ENERGY_UNITS=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      strncpy((char *)pars[0].internal_energy_units,string1,16);
      args_defined++;
    }
    if(   (ContainsString(s1,(char *)"RESTART=")==TRUE) )
    {
      CopyAfterEqual(string1,s1);
      RESTART = 0;
      if (  (strncmp(string1,(char *)"yes",3)==0) ||
            (strncmp(string1,(char *)"YES",3)==0) ||
            (strncmp(string1,(char *)"yES",3)==0) ||
            (strncmp(string1,(char *)"Yes",3)==0) )
      {
        RESTART = 1;
      }
      pars[0].RESTART = RESTART;
      args_defined++;
    }
    Free_sph(s1);
    Free_sph(string1);
  }
  if (args_defined != NUMBER_OF_ARGS)
  {
    printf(" %s(): -par file %s ascii header incorrectly formatted, incorrect number of arguments: have %i need %i \n",fname,par_name,args_defined,NUMBER_OF_ARGS);
    exit_status = EXIT_FAILURE;
    if (pars)
    {
      Free_sph(pars);
      pars = NULL;
    }
    fclose(par_ptr);
    
    goto RETURN;
  }
  pars[0].args_defined           = args_defined;
  pars[0].rank                   = rank;
  pars[0].PARTICLES_IN_Z_H       = pars[0].PARTICLES_IN_Z/2;
  pars[0].N_CENTRE               = ((pars[0].CENTRE_POINT+1)*pars[0].PARTICLES_IN_Z);
  pars[0].ZERO_H                 = pars[0].ZERO/2;
  pars[0].TOTAL_PARTICLES_GUESS  = pars[0].PARTICLES_IN_X*pars[0].PARTICLES_IN_Y*pars[0].PARTICLES_IN_Z;
  pars[0].NPARTICLES_EXTRA       = pars[0].NPARTICLES + pars[0].EXTRA;
  pars[0].TOTAL_PARTICLES        = LARGE_NEGATIVE_INT;
  pars[0].NPARTICLES             = LARGE_NEGATIVE_INT;

  fclose(par_ptr);
  exit_status = EXIT_SUCCESS;

RETURN:
  if (par_name)
  {
    Free_sph(par_name);
  }
  if (ascii_header)
  {
    for (i=0;i<40;i++)
    {
      Free_sph(ascii_header[i]);
    }
    Free_sph(ascii_header);
  }

  if (pars)
  {
    verbosity(2,fname,pars);
  }

  if (rank < cluster_size)
  {
    MPI_Send(&token_s,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
  }

  return pars;
}
