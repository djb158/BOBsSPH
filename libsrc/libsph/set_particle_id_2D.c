#include "set_particle_id_2D.h"

IDS *SetParticleID_2D(PARS *pars, PARTICLES *particles, double x, double y, double z)
{
  extern NODE_INFO *node_info;

  IDS *ids                             = NULL;

  double dist                          = LARGE_NEGATIVE_DOUBLE;
  double x0                            = LARGE_NEGATIVE_DOUBLE;
  double y0                            = LARGE_NEGATIVE_DOUBLE;
  double z0                            = LARGE_NEGATIVE_DOUBLE;

  int exit_status                      = EXIT_FAILURE;
  int species                          = EXIT_FAILURE;
  int i                                = LARGE_NEGATIVE_INT;
  int j                                = LARGE_NEGATIVE_INT;
  int l                                = LARGE_NEGATIVE_INT;
  int found                            = LARGE_NEGATIVE_INT;

  char   fname[]                       = "...SetParticleID_2D";

#include "pars_include.h"
/*
  verbosity(1,fname,pars);  Need to handle later
*/

  ids = (IDS *)calloc(1,sizeof(IDS));
  ids[0].species  = MASK_VOID;
  ids[0].l_mirror = LARGE_NEGATIVE_INT;
/*                                                                           */
/*                 interior particles: species = 512                         */
/*                                                                           */
  if (
       (x > X0 + EPSILON_DOUBLE)
               &&
       (x<X1-EPSILON_DOUBLE)
               &&
       (z>Z0+EPSILON_DOUBLE)
               &&
       (z<Z1-EPSILON_DOUBLE)
     )
  {
    ids[0].species = 512;
  }
/*                                                                           */
/*                 now do 4 boundary lines:                                  */
/*                 boundary particles are 2048+                              */
/*                                                                           */
/*                 x = X0                                                    */
/*                                                                           */
  else if (
            ( fabs(x - X0) < EPSILON_DOUBLE )
                 &&
            (z > Z0 + EPSILON_DOUBLE)
                 &&
            (z < Z1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2049;
  }
/*                                                                           */
/*                 x = X1                                                    */
/*                                                                           */
  else if (
            ( fabs(x - X1) < EPSILON_DOUBLE )
                 &&
            (z > Z0 + EPSILON_DOUBLE)
                 &&
            (z < Z1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2050;
  }
/*                                                                           */
/*                  z = Z0                                                   */
/*                                                                           */
  else if (
            ( fabs(z - Z0) < EPSILON_DOUBLE )
                 &&
            (x > X0 + EPSILON_DOUBLE)
                 &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2051;
  }
/*                                                                           */
/*                  z = Z1                                                   */
/*                                                                           */
  else if (
            ( fabs(z - Z1) < EPSILON_DOUBLE )
                 &&
            (x > X0 + EPSILON_DOUBLE)
                 &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2052;
  }
/*                                                                           */
/*                 now do 4 corner points                                    */
/*                                                                           */
  else if (
            ( fabs(x - X0) < EPSILON_DOUBLE )
                        &&
            ( fabs(z - Z0) < EPSILON_DOUBLE )
          )
  {
    ids[0].species = 2055;
  }
  else if (
            ( fabs(x - X0) < EPSILON_DOUBLE )
                        &&
            ( fabs(z - Z1) < EPSILON_DOUBLE )
          )
  {
    ids[0].species = 2056;
  }
  else if (
            ( fabs(x - X1) < EPSILON_DOUBLE )
                        &&
            ( fabs(z - Z0) < EPSILON_DOUBLE )
          )
  {
    ids[0].species = 2057;
  }
  else if (
            ( fabs(x - X1) < EPSILON_DOUBLE )
                        &&
            ( fabs(z - Z1) < EPSILON_DOUBLE )
          )
  {
    ids[0].species = 2058;
  }
/*                                                                           */
/*                 X0 face:  1025                                            */
/*                                                                           */
  else if ( ( (x < X0 - EPSILON_DOUBLE) && (x > LARGE_NEGATIVE_DOUBLE + 1.0) )
                    &&
            (z <= Z1 + EPSILON_DOUBLE)
                    &&
            (z >= Z0 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 1025;
    dist = fabs(X0-x);
    found = 0;
    for (j=0;j<NPARTICLES;j++)
    {
      x0 = particles[0].x[0][j];
      y0 = particles[0].x[1][j];
      z0 = particles[0].x[2][j];
      if ( (fabs(x0-dist-X0)<EPSILON_DOUBLE) && (fabs(y0-y)<EPSILON_DOUBLE) &&  (fabs(z0-z)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      printf(" here 0 \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 X1 face:  1026                                            */
/*                                                                           */
  else if ( (x > X1 + EPSILON_DOUBLE)
                    &&
            (z <= Z1 + EPSILON_DOUBLE)
                    &&
            (z >= Z0 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 1026;
    dist = fabs(X1-x);
    found = 0;
    for (j=0;j<NPARTICLES;j++)
    {
      x0 = particles[0].x[0][j];
      y0 = particles[0].x[1][j];
      z0 = particles[0].x[2][j];
      if ( (fabs(x0+dist-X1)<EPSILON_DOUBLE) && (fabs(y0-y)<EPSILON_DOUBLE) &&  (fabs(z0-z)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      printf(" here 1 \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                                                                           */
/*                 Z0 face:  1027                                            */
/*                                                                           */
  else if ( (z < Z0 - EPSILON_DOUBLE) && (z > LARGE_NEGATIVE_DOUBLE + 1.0) ) 
  {
    ids[0].species = 1027;
    dist = fabs(Z0-z);
    found = 0;
    for (j=0;j<NPARTICLES;j++)
    {
      x0 = particles[0].x[0][j];
      y0 = particles[0].x[1][j];
      z0 = particles[0].x[2][j];
      if ( (fabs(z0-dist-Z0)<EPSILON_DOUBLE) && (fabs(x0-x)<EPSILON_DOUBLE) &&  (fabs(y0-y)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      printf(" here 2 \n");
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 Z1 face:  1028                                            */
/*                                                                           */
  else if (z > Z1 + EPSILON_DOUBLE)
  {
    ids[0].species = 1028;
    dist = fabs(Z1-z);
    found = 0;
    for (j=0;j<NPARTICLES;j++)
    {
      x0 = particles[0].x[0][j];
      y0 = particles[0].x[1][j];
      z0 = particles[0].x[2][j];
      if ( (fabs(Z1-dist-z0)<EPSILON_DOUBLE) && (fabs(x0-x)<EPSILON_DOUBLE) &&  (fabs(y0-y)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      printf(" here 3 \n");
      printf(" x = %20.10f y = %20.10f z = %20.10f Z1 = %20.10f \n",x,y,z,Z1);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  return ids;
}
