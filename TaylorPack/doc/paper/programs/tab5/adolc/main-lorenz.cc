#include <adouble.h>
#include <DRIVERS/odedrivers.h>
#include <adalloc.h>

#include "params.h"

#define DIM 3

int main(void)
{
  void lorenz(int tag, double* px, double* pxp);
  int i,j,k;
  double x[DIM],f[DIM],*taco[DIM];

  for (j=0; j<DIM; j++) {
    taco[j]=(double*)malloc((DEG+1)*sizeof(double));
    if (taco[j] == NULL) {cout << "memory error\n"; return(1);}
  }

  x[0]=-8.0;
  x[1]= 8.0;
  x[2]=27.0;

  lorenz(0,x,f);
  for (j=0; j<DIM; j++) taco[j][0]=x[j];

  for (k=0; k<NIT; k++) forode(0,DIM,DEG,taco);

  for(i=0; i<=DEG; i++) {
    for (j=0; j<DIM; j++)
      cout << taco[j][i] << "  ";
    cout << "\n";
  }
  return(0);
}
