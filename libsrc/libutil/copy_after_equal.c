/*---------------------------------------------------------------------------*\
|                                                                             |
| File:       copy_after_equal.c                                              |
|                                                                             |
|                                                                             |
| Function:   char *CopyAfterEqual(char *target,  char *source)               |
|                                                                             |
| Call:       ContainsString(string1,string1);                                |
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
| David Brown, CTBTO/IDC: Feb 2011                                            |
|                                                                             |
\*---------------------------------------------------------------------------*/
#include "sph_main.h"

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
