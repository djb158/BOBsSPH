#include "copy_up_to_colon.h"

char *CopyUpToColon(char **arg, PARS *pars)
{
  char *string1                        = NULL;
  char *ptr                            = NULL;
  char *result                         = NULL;
  char   fname[]                       = "...CopyUpToColon";

  int i                                = 0;
  int exit_status                      = EXIT_FAILURE;

#include "pars_include.h"
  verbosity(1,fname,pars);

  string1 = (char *)calloc(MAX_CHARS,sizeof(char));
  if (arg == NULL)
  {
    exit_status = EXIT_FAILURE;
    printf(" Rank: %i %s(): unable to send tag21 packet \n",rank,fname);
    goto RETURN;
  }

  strcpy(string1,*arg);
  ptr = string1;
  i = 0;
  while ( (*string1+0 != 0x3b) && (*string1+1 != '\0') && (*string1 != '\0') )
  {
    string1++;
    i++;
  }
  if (*string1+1 == '\0')
  {
    *arg = NULL;
  }
  else
  {
    result  = (char *)calloc(MAX_CHARS,sizeof(char));
    strncpy(result,*arg,i);
    *arg = *arg + i + 2;
  }
  exit_status = EXIT_SUCCESS;
  
RETURN: 
  verbosity(2,fname,pars);
  free(ptr); ptr = NULL;

  return result;
}
