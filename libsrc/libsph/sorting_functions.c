/*---------------------------------------------------------------------*\
| 									|
| File:                                                                 |
|              sorting_functions.3.2.c    			     	|
| 									|
| Function:                                                             |
|              void Sort(double a[],int b[], int n).		      	|
|              void Unsort(double a[],int b[], int n).       	     	|
| 									|
| Call:                                                                 |
|              Sort(a,b,n);						|
|              Unsort(a,b,n);						|
| 									|
| Purpose:                                                              |
|              These subroutines Sorts/Unsorts in ascending order a     |
|              vector a[n] of double values and stores the permutation  |
|              order in a vector b[n] of int type.                      | 
| 									|
| Input:                                                                |
|              a - vector of n-values of type double to be Sorted,      |
|              b - vector of n-values of type int representing initial  |
|                  order of values in a.                                |
|              n - number of elements in vectors a & b.                 |
| 									|
| Output:                          		  		        |
|              a - vector of n-values Sorted in ascending order.        | 
|              b - order after Sorting.                                 |
| 									|
| Global                                                                | 
| Variables:                                                            |
|              S - structure containing two elements, i.e value & index.|
| 									|
| Required                                                              |
| Routines:                                                             |
|              CompareOnValue()                                         |
| 									|
|_______________________________________________________________________|
|                                                                       |
| Copyright:                                                            |
|             August 2003                                               |
|             C.Tarlowski & D.Brown                                     |
|             Research School of Earth Sciences, ANU.                   |
|_______________________________________________________________________|
| 									|
\*---------------------------------------------------------------------*/

#include "sorting_functions.h"

void Sort(double a[],int b[], int n)
{
    int i           = 0;
    S *ptr_to_s;

    ptr_to_s = (S *)calloc(n,sizeof(S));
    for (i = 0; i < n; i++) {
       ptr_to_s[i].value = a[i];
       ptr_to_s[i].index = b[i];
    }
    qsort( ptr_to_s, n, sizeof(S), CompareOnValue);
    for (i = 0; i < n; i++) {
       a[i] = ptr_to_s[i].value;
       b[i] = ptr_to_s[i].index;
    }
    free(ptr_to_s);

} /* End of Sort() */


void Unsort(double a[],int b[], int n)
{

    int i                       = 0;

    S *ptr_to_s;

    ptr_to_s = (S *)calloc(n,sizeof(S));

    for (i = 0; i < n; i++)
    {
       ptr_to_s[i].value = a[i];
       ptr_to_s[i].index = b[i];
    }

    qsort(ptr_to_s,n,sizeof(S), CompareOnIndex);

    for (i = 0; i < n; i++)
    {
       a[i] = ptr_to_s[i].value;
       b[i] = ptr_to_s[i].index;
    }

    free(ptr_to_s);

} /* End of Unsort() */


int CompareOnValue(const void *p1, const void *p2)
{

     if ( (*((const S*)p1)).value > (*((const S*)p2)).value)
       return 1;
     else if ( (*((const S*)p1)).value < (*((const S*)p2)).value)
       return -1;
     else
       return 0;
} /*End CompareOnValue */ 

int CompareOnIndex(const void *p1, const void *p2)
{
     if((*((const S*)p1)).index > (* ((const S*)p2)).index)
       return 1;
     else if ((*((const S*)p1)).index < (*((const S*)p2)).index)
       return -1;
     else
       return 0;
} /* End CompareOnIndex */
