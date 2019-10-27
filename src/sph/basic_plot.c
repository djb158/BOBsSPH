/*---------------------------------------------------------------------------*\
|                                                                             |
|  File: read_pbob_file.c                                                     |
|                                                                             |
|  Function: int main(int argc, char *argv[])                                 |
|                                                                             |
|  Purpose:  test code to read in header + particle information from a .pbob  |
|            file                                                             |
|                                                                             |
|  Call:                                                                      |
|            read_pbob_file time_slice=<int> start_index=<int>                |
|                           N=<int> file_name=<FILE NAME>                     |
|                                                                             |
|  Input:   int time_slice      the timeslice to retrieve                     |
|           int start_index     start index of particle to begin retrieval    |
|           int N               number of particles to retrieve               |
|           char *file_name     absolute path .pbob file to read in           |
|                                                                             |
|  Output:  int exit_statuss    either EXIT_SUCCESS or EXIT_FAILURE           |
|                                                                             |
|  Global variables:  none                                                    |
|                                                                             |
|  Required resources:                                                        |
|                     ReadParticle()                                          |
|                     ReadPBOB()                                              |
|                     ReadNodeDescrip()                                       |
|                     CopyAfterEqual()                                        |
|                     ContainsString()                                        |
|                                                                             |
| Error:  return EXIT_FAILURE on error                                        |
|                                                                             |
|-----------------------------------------------------------------------------|
|                                                                             |
| David Brown 29-Jul-2015   initial version                                   | 
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>     /* offsetof */
#include <math.h> 
#include "sph_types.h"
#include "pbob.h"
#include "node_descrip.h"
#include "particle.h"
#include "sorting_functions.h"
#include "numeric_constants.h"

typedef enum {FALSE,TRUE} logical;
#define MAX_CHARS (1024)

extern PARTICLE *ReadParticle(char *file_name,int time_slice,int start_index,int N);
extern PBOB *ReadPBOB(char *file_name);
extern NODE_DESCRIP *ReadNodeDescrip(char *file_name,int cluster_size);
extern char *CopyAfterEqual(char *target,  char *source);
extern logical ContainsString(char *string1,char *string2);
extern void Hplots(FILE *plot_file,int condition);
extern void Plot(FILE *plot_file,float x, float y,int num);

int main(int argc, char *argv[])
{
  FILE *plot_ptr                       = NULL;

  PARTICLE *particle                   = NULL;
  NODE_DESCRIP *node_descrip           = NULL;
  PBOB *pbob                           = NULL;

  
  char *file_name                      = NULL;
  char *string1                        = NULL;

  float XOR                            = 0.0;
  float YOR                            = 0.0;
  float xpt                            = 0.0;
  float ypt                            = 0.0;
  float PL                             = 0.0;
  float PH                             = 0.0;

  double v_min                         = 0.0;
  double v_max                         = 0.0;
  double x_min                         = 0.0;
  double x_max                         = 0.0;
  double x0                            = 0.0;
  double x1                            = 0.0;
  double v                             = 0.0;
  double *av                           = NULL;
  double *xv                           = NULL;
  double *x                            = NULL;

  int i                                = -9999999;
  int j                                = -9999999;
  int k                                = -9999999;
  int k_max                            = -9999999;
  int iv                               = -9999999;
  int cluster_size                     = -9999999;
  int total_particles                  = -9999999;
  int start_index                      = -9999999;
  int N                                = -9999999;
  int time_slice                       = 1;
  int args_defined                     = -9999999;
  int exit_status                      = EXIT_FAILURE;
  int *x_index                         = NULL;

  file_name = (char *)calloc(MAX_CHARS,sizeof(char));
  args_defined = 0;
  i = 0;
  while(i<argc)
  {
    string1 = (char *)calloc(MAX_CHARS,sizeof(char));
    if(   (ContainsString(argv[i],(char *)"file_name=")==TRUE) )
    {
      CopyAfterEqual(string1,argv[i]);
      sprintf(file_name,"%s",string1);
      args_defined++;
    }
    free(string1); string1 = NULL;
    i++;
  }
  if (args_defined != 1)
  {
    printf(" Usage: basic_plot  file_name=<FILE NAME>\n");
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

  if ( (pbob=ReadPBOB(file_name))==NULL)
  {
    printf(" -unable to read PBOB struct, -aborting \n");
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  if (pbob->endian_int == 2)
  {
    goto RETURN;
  }
  cluster_size = pbob->cluster_size;
  printf(" cluster_size = %i \n",cluster_size);
  if ((node_descrip=ReadNodeDescrip(file_name,cluster_size))==NULL)
  {
    printf(" -unable to read NODE_DESCRIP struct, -aborting \n");
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }
  
  total_particles = (int)pbob->total_particles;

  start_index = 0;
  N = total_particles;
  printf(" total_particles = %i \n",total_particles);
  if ((particle=ReadParticle(file_name,time_slice,start_index,N))==NULL)
  {
    printf(" -unable to read PARTICLE struct, -aborting \n");
    exit_status = EXIT_FAILURE;
    goto RETURN;
  }

  plot_ptr = fopen("/home/bobs/plot.ps","w+");
  Hplots(plot_ptr,1);
  XOR =  4.0;
  YOR =  4.0;
  PL  = 15.0;
  PH  =  4.0;
   
 
  v_min = LARGE_POSITIVE_DOUBLE;
  v_max = LARGE_NEGATIVE_DOUBLE;
  x_min = LARGE_POSITIVE_DOUBLE;
  x_max = LARGE_NEGATIVE_DOUBLE;

  x       = (double *)calloc(N,sizeof(double));
  x_index = (int *)calloc(N,sizeof(int));
  for (i=0;i<N;i++)
  {
    x[i] = (double)(particle[i].x);
    x_index[i] = i;
  }
  Sort(x,x_index,N);

  iv = 0;
  av = (double *)calloc(N,sizeof(double));
  xv = (double *)calloc(N,sizeof(double));
  for (i=0;i<N;i++)
  {
    av[i] = 0.0;
    xv[i] = 0.0;
  }
  
  x0 = x[0];
  k = 0;
  for (i=0;i<N;i++)
  {
    x1 = x[i];
    j  = x_index[i];
    v  = (double)(particle[j].vx);
    av[k] = v + av[k];
    if (fabs(x1-x0) > 0.000001)
    {
      av[k] = av[k]/(double)iv;
      xv[k] = x1;
      printf(" x = %20.10f v  = %20.10f \n",xv[k],av[k]);
      if (av[k] > v_max)v_max = av[k];
      if (av[k] > v_max)v_max = av[k];
      if (xv[k] < x_min)x_min = xv[k];
      if (xv[k] > x_max)x_max = xv[k];
      iv = 0;
      k++;
    }
    iv++;
    x0 = x1;
  }
  k_max = k;

  xpt = XOR;
  ypt = YOR;
  Plot(plot_ptr,xpt,ypt,3);
  Plot(plot_ptr,xpt+PL,ypt,2);
  Plot(plot_ptr,xpt+PL,ypt+PH,2);
  Plot(plot_ptr,xpt,ypt+PH,2);
  Plot(plot_ptr,xpt,ypt,2);
  k = 0;
  xpt = XOR + PL*(xv[k]-x_min)/(x_max-x_min);
  ypt = YOR + PH*(av[k]-v_min)/(v_max-v_min);
  Plot(plot_ptr,xpt,ypt,3);
  for (k=0;k<k_max;k++)
  {
    xpt = XOR + PL*(xv[k]-x_min)/(x_max-x_min);
    ypt = YOR + PH*(av[k]-v_min)/(v_max-v_min);
    Plot(plot_ptr,xpt,ypt,2);
  }

  Hplots(plot_ptr,0);
  fclose(plot_ptr);

  exit_status = EXIT_SUCCESS;
RETURN:
  free(file_name);file_name = NULL;

  return 0;
}
/*---------------------------------------------------------------------------*\
|                                                                             |
| File:       contains_string.c                                               |
|                                                                             |
|                                                                             |
| Function:   logical ContainsString(char *string1,char *string2)             |
|                                                                             |
|                                                                             |
| Call:       ContainsString(string1,string1);                                |
|                                                                             |
| Purpose:    Determines if string1 contains string2                          |
|                                                                             |
|                                                                             |
| Input:      char *string1:  first string                                    |
|             char *string2:  second string                                   |
|                                                                             |
| Output:     None:                                                           |
|                                                                             |
| Returned    logical                                                         |
| Value:                                                                      |
|                                                                             |
| Global                                                                      |
| Variables:                                                                  |
|             None.                                                           |
|                                                                             |
| Required                                                                    |
| Resources:  Free_sph                                                        |
|                                                                             |
|-----------------------------------------------------------------------------|
| David Brown, : Feb 2011                                                     |
|                                                                             |
\*---------------------------------------------------------------------------*/

logical ContainsString(char *string1,char *string2)
{
  char *string3;

  int len_string1 = 0;
  int len_string2 = 0;
  int first = 0;
  int last = 0;

  logical result = FALSE;

  string3 = (char *)calloc(MAX_CHARS,sizeof(char));
  len_string2 = strlen(string2);
  len_string1 = strlen(string1);
  if (len_string1 < len_string2)
  {
    result = FALSE;
  }
  else
  {
    first = 0;
    last = first + len_string2;
    while(last <= len_string1)
    {
      memcpy((void *)string3,(void *)(string1+first),last-first);
      if (strcmp(string2,string3) == 0)
      {
        result = TRUE;
      }
      first++;
      last = first + len_string2;
    }
  }

  free(string3); string3 = NULL;
  return result;
}
/*---------------------------------------------------------------------------*\
|                                                                             |
| File:       copy_after_equal.c                                              |
|                                                                             |
|                                                                             |
| Function:   char *CopyAfterEqual(char *target,  char *source)               |
|                                                                             |
| Call:       CopyAfterEqual(string1,string1);                                |
|                                                                             |
| Purpose:    if source string contains an equal sign then return all         |
|             characters after the equal as a null-terminated string          |
|             will terminate at a \n                                          |
|                                                                             |
| Input:      char *target:  output string                                    |
|             char *source:  input string                                     |
|                                                                             |
| Output:     None:                                                           |
|                                                                             |
| Returned    char *target                                                    |
| Value:                                                                      |
|                                                                             |
| Global                                                                      |
| Variables:                                                                  |
|             None.                                                           |
|                                                                             |
| Required                                                                    |
| Resources:  Free_sph                                                        |
|                                                                             |
|-----------------------------------------------------------------------------|
| David Brown, : Feb 2011                                                     |
|                                                                             |
\*---------------------------------------------------------------------------*/

char *CopyAfterEqual(char *target,  char *source)
{   
  extern FILE *logfile_ptr;

  if (source == NULL)printf("CopyAfterEqual(): NULL source string passed to CopyAfterEqual\n");

  while ( *source != '\0')
  {
    while (*source != '=')
    {
      source++;
    }
    source++; /* Skip = */
    while(*source !='\0') 
    {
      *target = *source;
      target++;
      source++;
    }
  } 
  *target = '\0';
  return target;
}
