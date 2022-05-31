#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtbp.h"

#define Y0 -0.56210340265552085504
#define Y1  0.87742260648445467260
#define Y2 -0.22370669045517274593
#define Y3 -0.61230928495937399217
#define Y4 -0.51125245057813111131
#define Y5 -0.45728848688565667119

int main(void)
{
  double t,tf,x[6],ht,lerr,e,ee;
  int ord,j;

  lerr=-16;

  for (j=0; j<999; j++)
  {
    x[0]=-0.45;
    x[1]= 0.80;
    x[2]= 0.00;
    x[3]=-0.80;
    x[4]=-0.45;
    x[5]= 0.58;
    t=0.0;
    tf=16;
    while(taylor_step_rtbp(&t,x,1,1,lerr,lerr,&tf,&ht,&ord) == 0);
  }

  x[0]=-0.45;
  x[1]= 0.80;
  x[2]= 0.00;
  x[3]=-0.80;
  x[4]=-0.45;
  x[5]= 0.58;
  t=0.0;
  tf=16;
  while(taylor_step_rtbp(&t,x,1,1,lerr,lerr,&tf,&ht,&ord) == 0);

  e=fabs(x[0]-Y0);
  ee=fabs(x[1]-Y1);
  if (ee > e) e=ee;
  ee=fabs(x[2]-Y2);
  if (ee > e) e=ee;
  ee=fabs(x[3]-Y3);
  if (ee > e) e=ee;
  ee=fabs(x[4]-Y4);
  if (ee > e) e=ee;
  ee=fabs(x[5]-Y5);
  if (ee > e) e=ee;
  printf("error: %e\n",e);

  return(0);
}
