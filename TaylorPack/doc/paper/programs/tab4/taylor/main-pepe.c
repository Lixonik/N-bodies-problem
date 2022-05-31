#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "pepe.h"

#define Y0  0.53752534081134067261
#define Y1 -0.12104140610381475352

int main(void)
{
  double t,tf,x[2],ht,lerr,e,ee;
  int ord,j;

  lerr=-16;

  for (j=0; j<999; j++)
  {
    x[0]=0.0;
    x[1]=0.0;
    t=0.0;
    tf=16;
    while(taylor_step_pepe(&t,x,1,1,lerr,lerr,&tf,&ht,&ord) == 0);
  }

  x[0]=0.0;
  x[1]=0.0;
  t=0.0;
  tf=16;
  while(taylor_step_pepe(&t,x,1,1,lerr,lerr,&tf,&ht,&ord) == 0);

  e=fabs(x[0]-Y0);
  ee=fabs(x[1]-Y1);
  if (ee > e) e=ee;
  printf("error: %e\n",e);

  return(0);
}
