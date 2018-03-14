/*---------------------------------------------------------------------------*\
|                                                                             |
| File:       copy_after_semicolon.c                                              |
|                                                                             |
|                                                                             |
| Function:   char *CopyAfterSemicolon(char *target,  char *source)               |
|                                                                             |
| Call:       ContainsString(string1,string1);                                |
|                                                                             |
| Purpose:    if source string contains a semicolon sign then return all      |
|             characters after the semicolon as a null-terminated string      |
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

char *CopyAfterSemicolon(char *target,  char *source)
{   
  extern FILE *logfile_ptr;

  if (source == NULL)printf("CopyAfterSemicolon(): NULL source string passed to CopyAfterSemicolon\n");

  while ( *source != '\0')
  {
    while (*source != ';')
    {
      source++;
    }
    source++; /* Skip ; */
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
