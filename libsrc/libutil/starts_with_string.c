/*---------------------------------------------------------------------------*\
|                                                                             |
| File:       starts_with_string.c                                            |
|                                                                             |
|                                                                             |
| Function:   logical StartsWithString(char *string1,char *string2)           |
|                                                                             |
|                                                                             |
| Call:       StartsWithString(string1,string2);                              |
|                                                                             |
| Purpose:    Determines if string1 starts with  string2                      |
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
|                                                                             |
|  David Brown 2015.
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

#include "starts_with_string.h"

logical StartsWithString(char *string1,char *string2, PARS *pars)
{
  char *string3                        = NULL;
  char   fname[]                       = "...StartWithString";

  int len_string1                      = 0;
  int len_string2                      = 0;
  int first                            = 0;
  int last                             = 0;
  int exit_status                      = EXIT_FAILURE;

  logical result = FALSE;

#include "pars_include.h"
  verbosity(1,fname,pars);

  string3     = (char *)calloc(MAX_CHARS,sizeof(char));
  len_string2 = strlen(string2);
  len_string1 = strlen(string1);

  if (len_string2 > len_string1)
  {
    first = 0;
    last = first + len_string2;
    memcpy((void *)string3,(void *)(string1+first),last-first);
    if (strcmp(string2,string3) == 0)
    {
      result = TRUE;
    }
  }
  exit_status = EXIT_SUCCESS;

RETURN: 
  verbosity(2,fname,pars);
  free(string3); string3 = NULL;

  return result;
}
