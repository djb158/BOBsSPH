#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "starts_with_string.h"
#include "copy_up_to_colon.h"
#include "initialize_pars.h"
#include "mpi.h"

extern char *CopyUpToColon(char **arg, PARS *pars);
extern logical StartsWithString(char *string1, char *string2, PARS *pars);
extern int InitializePars(PARS *pars);
extern void verbosity(int k, char fname[],PARS *pars);

int main (int argc, char* argv[])
{
  MPI_Status stat;
  PARS *pars                           = NULL;

  char *argv_string                    = NULL;
  char *argv_string_ptr                = NULL;
  char *string1                        = NULL;
  char *string2                        = NULL;
  char *rank_name                      = NULL;
  char   fname[]                       = "...Main";

  int exit_status                     = EXIT_FAILURE;
  int i                               = 0;
  int j                               = 0;
  int len                             = 0;
  int cluster_size                    = 0;
  int rank_0                          = 0;
  int node                            = 0;
  int VERBOSITY_0                     = 1;


  MPI_Init(&argc, &argv);
  MPI_Group MPI_GROUP_WORLD;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank_0);
  MPI_Comm_size(MPI_COMM_WORLD,&cluster_size);
  rank_name = (char *)calloc(MAX_CHARS,sizeof(char));
  MPI_Get_processor_name(rank_name,&len);
  string2           = (char *)calloc(MAX_CHARS,sizeof(char));
  pars              = (PARS *)calloc(1,sizeof(PARS));
  InitializePars(pars);
  pars[0].VERBOSITY = VERBOSITY_0;
  pars[0].rank      = rank_0;

#include <pars_include.h>
  verbosity(1,fname,pars);
  rank              = rank_0;

  if (rank == 0)
  {
    argv_string  = (char *)calloc(MAX_CHARS,sizeof(char));
    memset(string2,0x00,MAX_CHARS);
    strcpy(argv_string,argv[1]);
    for (i=2;i<argc;i++)
    {
      strcat(argv_string,(char *)" ");
      strcat(argv_string,argv[i]);
    }
    strcat(argv_string,(char *)"\0");
    argv_string_ptr = argv_string;

    system((char *)"rm -rf /tmp/pbobs.log"); 
    while (*argv_string != '\0')
    {
      if ((string1=CopyUpToColon(&argv_string,pars))!=NULL)
      {
        strcat(string2,string1);
        if (!StartsWithString(string1,"cd ",pars))
        {
          strcat(string2,(char *)" >  /tmp/pbobs.log 2>&1");
        }
        strcat(string2,(char *)" ;");
        free(string1); string1 = NULL;
      }
    }
    for (node=1;node<cluster_size;node++)
    {
      MPI_Send(string2,MAX_CHARS,MPI_CHAR,node,1,MPI_COMM_WORLD);
    }
    system(string2); 
    sleep (3);
  }
  else
  {
    MPI_Recv(string2,MAX_CHARS,MPI_CHAR,0,1,MPI_COMM_WORLD,&stat);
    system(string2); 
    sleep (3);
  }
  
  exit_status = EXIT_SUCCESS;

RETURN:
  verbosity(2,fname,pars);

  free(argv_string_ptr); argv_string_ptr  = NULL;
  free(string2);         string2          = NULL;
  free(pars);            pars             = NULL;
  free(rank_name);       rank_name        = NULL;

  return exit_status;
} 
