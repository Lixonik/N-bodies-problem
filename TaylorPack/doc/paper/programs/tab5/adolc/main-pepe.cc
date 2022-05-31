#include <adouble.h>
#include <DRIVERS/odedrivers.h>
#include <adalloc.h>

#include "params.h"

#define DIM 3

int main(void)
{
  void pepe(int tag, double pt, double* px, double* pxp);
  int i,j,k;
  double t,x[DIM],f[DIM],*taco[DIM];

  for (j=0; j<DIM; j++) {
    taco[j]=(double*)malloc((DEG+1)*sizeof(double));
    if (taco[j] == NULL) {cout << "memory error\n"; return(1);}
  }

  x[0]=0.0;
  x[1]=0.0;
  x[2]=0.0;

  pepe(0,t,x,f);
  for (j=0; j<DIM; j++) taco[j][0]=x[j];

  for (k=0; k<NIT; k++) forode(0,DIM,DEG,taco);

  for(i=0; i<=DEG; i++) {
    for (j=0; j<DIM; j++)
      cout << taco[j][i] << "  ";
    cout << "\n";
  }
  return(0);
}
