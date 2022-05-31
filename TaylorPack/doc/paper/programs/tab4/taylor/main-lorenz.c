#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lorenz.h"

#define Y0  -9.13131302736875292786
#define Y1 -12.47617881107825333392
#define Y2  22.84333896098238820550

int main(void)
{
  double t,tf,x[3],ht,lerr,e,ee;
  int ord,j;

  lerr=-16;

  for (j=0; j<999; j++)
  {
    x[0]=-8.0;
    x[1]= 8.0;
    x[2]=27.0;
    t=0.0;
    tf=16;
    while (taylor_step_lorenz(&t,x,1,2,lerr,lerr,&tf,&ht,&ord) == 0);
  }

  x[0]=-8.0;
  x[1]= 8.0;
  x[2]=27.0;
  t=0.0;
  tf=16;
  while (taylor_step_lorenz(&t,x,1,2,lerr,lerr,&tf,&ht,&ord) == 0);

  e=fabs(x[0]-Y0);
  ee=fabs(x[1]-Y1);
  if (ee > e) e=ee;
  ee=fabs(x[2]-Y2);
  if (ee > e) e=ee;
  printf("error: %e\n",e);

  return(0);
}
