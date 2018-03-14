#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ANN.h>
#include <sph_main.h>
#include <pars.h>
#include <numeric_constants.h>

using namespace std;

extern void verbosity(int k, char fname[],PARS *pars);

int UpdateRij(int **nn, double **all_points,PARS *pars)
{
  char fname[] = "...UpdateRij";

  double  eps = 0.0;

  int i                                = 0;
  int j                                = 0;
  int k                                = 0;
  int dim                              = 0;
  int nPts                             = 0;
  int exit_status                      = EXIT_FAILURE;

  ANNpointArray    dataPts;
  ANNpoint         queryPt;
  ANNidxArray      nnIdx;
  ANNdistArray     dists;
  ANNkd_tree*      kdTree;

#include "pars_include.h"
  verbosity(1,fname,pars);

  eps = NN_EPS;
  dim = DIMENSIONS;
  printf(" DIMENSIONS = %i \n",DIMENSIONS);
  k   = NN_K;
  nPts = TOTAL_PARTICLES;
  dataPts = all_points;
  nnIdx   = new ANNidx[k];
  dists   = new ANNdist[k];

  kdTree = new ANNkd_tree(dataPts,nPts,dim);

  for (i=0;i<nPts;i++)
  {
    queryPt = (ANNpoint)all_points[i];
    kdTree->annkSearch(queryPt,k,nnIdx,dists,eps);
    for (j=0;j<k;j++)
    {
      nn[i][j] = nnIdx[j];
    }
  }
  delete [] nnIdx;
  delete kdTree;
  delete [] dists; 
  annClose();
  exit_status = EXIT_SUCCESS;

RETURN:

  verbosity(2,fname,pars);
  return exit_status;
}
