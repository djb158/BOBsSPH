#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ANN.h>
#include "mpi.h"
#include <particles.h>

using namespace std;

void printPt(ostream &out, ANNpoint p)      // print point
{
  out << "(" << p[0];
  for (int i = 1; i < 2; i++) {
    out << ", " << p[i];
  }
  out << ")\n";
}

void UpdateNN(PARTICLES *particles)
{

  double  eps = NN_EPS;

  int       i                          = 0;
  int       j                          = 0;
  int       k                          = NN_k;
  int     dim                          = DIMENSIONS;
  int    nPts                          = TOTAL_PARTICLES;
  int  i_rank                          = 0;
  int       m                          = 0;
  int   m_off                          = 0;
  int    **nn                          = NULL;

  double **all_points = NULL;
  double *x           = NULL;
  double *y           = NULL;
  double *z           = NULL;

  ANNpointArray    dataPts;
  ANNpoint         queryPt;
  ANNidxArray      nnIdx;
  ANNdistArray     dists;
  ANNkd_tree*      kdTree;

  MPI_Win_fence(0,particles[0].w[32]);
  MPI_Win_fence(0,particles[0].w[33]);
  MPI_Win_fence(0,particles[0].w[34]);
  MPI_Win_fence(0,particles[0].w[35]);

  nn = (int **)calloc(nPts,sizeof(int *));
  for (i=0;i<nPts;i++)
  {
    nn[i] = (int *)calloc(NN_k,sizeof(int));
    for (j=0;j<NN_k;j++)
    {
      nn[i][j] = 0;
    }
  }

  all_points = (double **)calloc(nPts,sizeof(double *));
  x          = (double *)calloc(nPts,sizeof(double));
  y          = (double *)calloc(nPts,sizeof(double));
  z          = (double *)calloc(nPts,sizeof(double));
  for (i=0;i<nPts;i++)
  {
   all_points[i] = (double *)calloc(DIMENSIONS,sizeof(double));
   x[i] = 0.0;
   y[i] = 0.0;
   z[i] = 0.0;
  }

  m_off  = 0;
  m      = NPARTICLES;
  for (i_rank=1;i_rank<CLUSTER_SIZE;i_rank++)
  {
    MPI_Get(&x[m_off],m,MPI_DOUBLE,i_rank,0,m,MPI_DOUBLE,particles[0].w[32]);
    MPI_Get(&y[m_off],m,MPI_DOUBLE,i_rank,0,m,MPI_DOUBLE,particles[0].w[33]);
    MPI_Get(&z[m_off],m,MPI_DOUBLE,i_rank,0,m,MPI_DOUBLE,particles[0].w[34]);
    m_off = m_off + m;
  }

  for (i=0;i<nPts;i++)
  {
   if (DIMENSIONS == 1)
   {
     all_points[i][0] = x[i];
   }
   if (DIMENSIONS == 2)
   {
     all_points[i][0] = x[i]; 
     all_points[i][1] = y[i];
   }
   if (DIMENSIONS == 3)
   {
     all_points[i][0] = x[i];
     all_points[i][1] = y[i];
     all_points[i][2] = z[i];
   }
  }
  dataPts = all_points;
  nnIdx   = new ANNidx[k];
  dists   = new ANNdist[k];

  kdTree = new ANNkd_tree(dataPts,nPts,dim);

  for (i=0;i<nPts;i++)
  {
    queryPt = (ANNpoint)all_points[i];
    
/*  cout << "Query point: ";
    printPt(cout, queryPt); */

    kdTree->annkSearch(queryPt,k,nnIdx,dists,eps);
    for (j=0;j<k;j++)
    {
      nn[i][j] = nnIdx[j];
    }
  }
  delete [] nnIdx;
  delete kdTree;
  delete [] dists; 
  if (all_points)
  {
    for (i=0;i<nPts;i++)
    {
     free(all_points[i]);
   }
    free(all_points);
    all_points = NULL;
  }
  annClose();
  m = nPts*NN_k;
  for (i_rank=1;i_rank<CLUSTER_SIZE;i_rank++)
  {
    MPI_Put(&nn[0][0],m,MPI_INT,i_rank,0,m,MPI_INT,particles[0].w[35]);
  }
  free(x);
  free(y);
  free(z);
  if (nn)
  {
    for (i=0;i<nPts;i++)
    {
      free(nn[i]);
    }
    free(nn);
  }

  MPI_Win_fence(0,particles[0].w[32]);
  MPI_Win_fence(0,particles[0].w[33]);
  MPI_Win_fence(0,particles[0].w[34]);
  MPI_Win_fence(0,particles[0].w[35]);

  return;
}
