#include "sph_main.h"
#include "pars.h"
#include "particles.h"
#include "numeric_constants.h"

#define MAX_TAGS         (100)

extern void verbosity(int k, char fname[],PARS *pars);
int SynchroniseNodeInfo(PARS *pars);
