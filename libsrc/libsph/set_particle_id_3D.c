#include "set_particle_id_3D.h"

IDS *SetParticleID_3D(PARS *pars, PARTICLES *particles, double x, double y, double z)
{
  extern NODE_INFO *node_info;

  IDS *ids                             = NULL;

  double dist                          = LARGE_NEGATIVE_DOUBLE;
  double x0                            = LARGE_NEGATIVE_DOUBLE;
  double y0                            = LARGE_NEGATIVE_DOUBLE;
  double z0                            = LARGE_NEGATIVE_DOUBLE;

  int exit_status                      = EXIT_FAILURE;
  int species                          = EXIT_FAILURE;
  int j                                = LARGE_NEGATIVE_INT;
  int l                                = LARGE_NEGATIVE_INT;
  int found                            = LARGE_NEGATIVE_INT;

  char   fname[]                       = "...SetParticleID_3D";

#include "pars_include.h"
/*
  verbosity(1,fname,pars);
*/

  ids = (IDS *)calloc(1,sizeof(IDS));
  ids[0].species   = LARGE_NEGATIVE_INT;
  ids[0].l_mirror  = LARGE_NEGATIVE_INT;
/*                                                                           */
/*                 interior particles: species = 512                              */
/*                                                                           */
  if (
       (x > X0 + EPSILON_DOUBLE)
               &&
       (x<X1-EPSILON_DOUBLE)
               &&
       (y>Y0+EPSILON_DOUBLE)
               &&
       (y<Y1-EPSILON_DOUBLE)
               &&
       (z>Z0+EPSILON_DOUBLE)
               &&
       (z<Z1-EPSILON_DOUBLE)
     )
  {
    ids[0].species = 512;
  }
/*                                                                           */
/*                 now do 6 boundary faces:                                  */
/*                 boundary particles are 2048+                              */
/*                                                                           */
/*                 x = X0                                                    */
/*                                                                           */
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                 &&
            (z > Z0 + EPSILON_DOUBLE)
                 &&
            (z < Z1 - EPSILON_DOUBLE)
                 &&
            (y > Y0 + EPSILON_DOUBLE)
                 &&
            (y < Y1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2049;
  }
/*                                                                           */
/*                 x = X1                                                    */
/*                                                                           */
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                 &&
            (z > Z0 + EPSILON_DOUBLE)
                 &&
            (z < Z1 - EPSILON_DOUBLE)
                 &&
            (y > Y0 + EPSILON_DOUBLE)
                 &&
            (y < Y1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2050;
  }
/*                                                                           */
/*                  z = Z0                                                   */
/*                                                                           */
  else if (
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
                 &&
            (y > Y0 + EPSILON_DOUBLE)
                 &&
            (y < Y1 - EPSILON_DOUBLE)
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
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
                 &&
            (y > Y0 + EPSILON_DOUBLE)
                 &&
            (y < Y1 - EPSILON_DOUBLE)
                 &&
            (x > X0 + EPSILON_DOUBLE)
                 &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2052;
  }
/*                                                                           */
/*                  y = Y0                                                   */
/*                                                                           */
  else if (
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                 &&
            (z > Z0 + EPSILON_DOUBLE)
                 &&
            (z < Z1 - EPSILON_DOUBLE)
                 &&
            (x > X0 + EPSILON_DOUBLE)
                 &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2053;
  }
/*                                                                           */
/*                  y = Y1                                                   */
/*                                                                           */
  else if (
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                 &&
            (z > Z0 + EPSILON_DOUBLE)
                 &&
            (z < Z1 - EPSILON_DOUBLE)
                 &&
            (x > X0 + EPSILON_DOUBLE)
                 &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2054;
  }
/*                                                                           */
/*                 now do 12 wire frames                                      */
/*                                                                           */
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
                        &&
            (y > Y0 + EPSILON_DOUBLE)
                        &&
            (y < Y1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2055;
  }
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
                        &&
            (y > Y0 + EPSILON_DOUBLE)
                        &&
            (y < Y1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2056;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
                        &&
            (y > Y0 + EPSILON_DOUBLE)
                        &&
            (y < Y1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2057;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
                        &&
            (y > Y0 + EPSILON_DOUBLE)
                        &&
            (y < Y1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2058;
  }
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            (z > Z0 + EPSILON_DOUBLE)
                        &&
            (z < Z1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2059;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            (z > Z0 + EPSILON_DOUBLE)
                        &&
            (z < Z1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2060;
  }
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            (z > Z0 + EPSILON_DOUBLE)
                        &&
            (z < Z1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2061;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            (z > Z0 + EPSILON_DOUBLE)
                        &&
            (z < Z1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2062;
  }
  else if (
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            (x > X0 + EPSILON_DOUBLE)
                        &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2063;
  }
  else if (
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            (x > X0 + EPSILON_DOUBLE)
                        &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2064;
  }
  else if (
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            (x > X0 + EPSILON_DOUBLE)
                        &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2065;
  }
  else if (
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            (x > X0 + EPSILON_DOUBLE)
                        &&
            (x < X1 - EPSILON_DOUBLE)
          )
  {
    ids[0].species = 2066;
  }
/*                                                                           */
/*                 now do 8 corner points                                    */
/*                                                                           */
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2067;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2068;
  }
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2069;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2070;
  }
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2071;
  }
  else if (
            ( (x - X0) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2072;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z0) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2073;
  }
  else if (
            ( (x - X1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (y - Y1) < fabs(EPSILON_DOUBLE) )
                        &&
            ( (z - Z1) < fabs(EPSILON_DOUBLE) )
          )
  {
    ids[0].species = 2074;
  }
/*                                                                           */
/*                 X0 face:  1025                                            */
/*                                                                           */
  else if ( (x < X0 - EPSILON_DOUBLE)
                    &&
            (y >= Y0 - EPSILON_DOUBLE)
                    &&
            (z <= Z1 + EPSILON_DOUBLE)
                    &&
            (y <= Y1 + EPSILON_DOUBLE)
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
      if ( (fabs(x0-X0-dist)<EPSILON_DOUBLE) && (fabs(y0-y)<EPSILON_DOUBLE) &&  (fabs(z0-z)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 X1 face:  1026                                            */
/*                                                                           */
  else if ( (x > X1 + EPSILON_DOUBLE)
                    &&
            (y >= Y0 - EPSILON_DOUBLE)
                    &&
            (z <= Z1 + EPSILON_DOUBLE)
                    &&
            (y <= Y1 + EPSILON_DOUBLE)
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
      if ( (fabs(x0-X1-dist)<EPSILON_DOUBLE) && (fabs(y0-y)<EPSILON_DOUBLE) &&  (fabs(z0-z)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 Z0 face:  1027                                            */
/*                                                                           */
  else if (z < Z0 - EPSILON_DOUBLE)
  {
    ids[0].species = 1027;
    dist = fabs(Z0-z);
    found = 0;
    for (j=0;j<NPARTICLES;j++)
    {
      x0 = particles[0].x[0][j];
      y0 = particles[0].x[1][j];
      z0 = particles[0].x[2][j];
      if ( (fabs(z0-Z0-dist)<EPSILON_DOUBLE) && (fabs(x0-x)<EPSILON_DOUBLE) &&  (fabs(y0-y)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
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
      if ( (fabs(z0-Z1-dist)<EPSILON_DOUBLE) && (fabs(x0-x)<EPSILON_DOUBLE) &&  (fabs(y0-y)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 Y0 face:  1029                                            */
/*                                                                           */
  else if (y < Y0 - EPSILON_DOUBLE)
  {
    ids[0].species = 1029;
    dist = fabs(Y0-y);
    found = 0;
    for (j=0;j<NPARTICLES;j++)
    {
      x0 = particles[0].x[0][j];
      y0 = particles[0].x[1][j];
      z0 = particles[0].x[2][j];
      if ( (fabs(y0-Y0-dist)<EPSILON_DOUBLE) && (fabs(x0-x)<EPSILON_DOUBLE) &&  (fabs(z0-z)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
/*                                                                           */
/*                 Y1 face:  1030                                            */
/*                                                                           */
  else if (y > Y1 + EPSILON_DOUBLE)
  {
    ids[0].species = 1030;
    dist = fabs(Y1-y);
    found = 0;
    for (j=0;j<NPARTICLES;j++)
    {
      x0 = particles[0].x[0][j];
      y0 = particles[0].x[1][j];
      z0 = particles[0].x[2][j];
      if ( (fabs(y0-Y1-dist)<EPSILON_DOUBLE) && (fabs(x0-x)<EPSILON_DOUBLE) &&  (fabs(z0-z)<EPSILON_DOUBLE) )
      {
        ids[0].l_mirror = node_info[rank].raw_index[j];
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      printf("Rank: %i %s(): l = %i mirror not found\n",rank,fname,l);
      exit_status = EXIT_FAILURE;
      goto RETURN;
    }
  }
  else
  {
    printf(" Rank: %i  %s():  x = %20.10f y = %20.10f z = %20.10f -not defined \n",rank,fname,x,y,z);
    exit_status = EXIT_FAILURE;
    species = EXIT_FAILURE;
    goto RETURN;
  }

  exit_status = EXIT_SUCCESS;

RETURN:
  return ids;
}
