/*---------------------------------------------------------------------------*\
|                                                                             |
| File:                                                                       |
|             big_or_little_endian.c                                          |
|                                                                             |
| Function:                                                                   |
|             int BigOrLittleEndian()                                         |
|                                                                             |
| Call:                                                                       |
|             endian       = BigOrLittleEndian();                             |
|                                                                             |
| Purpose:                                                                    |
|             This function returns 1 if the local architecure is Little      |
|             Endian or 0 if the local architecture is Big Endian             | 
|                                                                             |
| Input:      None                                                            |
|                                                                             |
| Output:     None                                                            |
|                                                                             |
| Returned    int                                                             |
| Value:                                                                      |
|                                                                             |
| Global                                                                      |
| Variables:                                                                  |
|             None.                                                           |
|                                                                             |
| Required                                                                    |
| Resources:                                                                  |
|             None                                                            |
|                                                                             |
|-----------------------------------------------------------------------------|
| David Brown: Feb 2011                                                       |
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

int BigOrLittleEndian()
{
  char fname[]                         = "...BigOrLittleEndian";

  int i           = 1;
  int j           = 0;

  j = ((char *)&i)[0];

  return j;
}
