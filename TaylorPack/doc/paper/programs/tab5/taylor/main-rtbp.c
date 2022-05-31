#include <stdio.h>

#include "rtbp.h"
#include "params.h"

#define DIM 6

int main(void)
{
  int i,j;
  double t,x[DIM],**taco;

  t=0.0;
  x[0]=-0.45;
  x[1]= 0.80;
  x[2]= 0.00;
  x[3]=-0.80;
  x[4]=-0.45;
  x[5]= 0.58;

  for (j=0; j<NIT; j++) taco=taylor_coefficients_rtbp(t,x,DEG);

  for(i=0; i<=DEG; i++) {
    for (j=0; j<DIM; j++) printf("%24.16e ",taco[j][i]);
    printf("\n");
  }
  return(0);
}
