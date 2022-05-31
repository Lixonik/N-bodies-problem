#include <stdio.h>

#include "pepe.h"
#include "params.h"

#define DIM 2

int main(void)
{
  int i,j;
  double t,x[DIM],**taco;

  t=0.0;
  x[0]=0.0;
  x[1]=0.0;

  for (j=0; j<NIT; j++) taco=taylor_coefficients_pepe(t,x,DEG);

  for(i=0; i<=DEG; i++) {
    for (j=0; j<DIM; j++) printf("%24.16e ",taco[j][i]);
    printf("\n");
  }
  return(0);
}
