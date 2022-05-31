#include <adouble.h>
#include <DRIVERS/odedrivers.h>
#include <adalloc.h>

#define MU 0.01

void rtbp(int tag, double* px, double* pxp)
{
  adoublev x(6),xp(6);
  adouble r2,rpe2,rpe,rpe3i,rpm2,rpm,rpm3i,tmp;

  trace_on(tag);
  x <<= px;

  r2=x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
  rpe2=r2-2*MU*x[0]+MU*MU;
  rpe=sqrt(rpe2);
  rpe3i=1/(rpe*rpe2);
  rpm2=r2+2*(1-MU)*x[0]+(1-MU)*(1-MU);
  rpm=sqrt(rpm2);
  rpm3i=1/(rpm*rpm2);
  tmp=(1-MU)*rpe3i+MU*rpm3i;

  xp[0]= x[3]+x[1];
  xp[1]= x[4]-x[0];
  xp[2]= x[5];
  xp[3]= x[4]-(1-MU)*(x[0]-MU)*rpe3i-MU*(x[0]+(1-MU))*rpm3i;
  xp[4]=-x[3]-x[1]*tmp;
  xp[5]=-x[2]*tmp;

  xp >>= pxp;
  trace_off(tag);
  return;
}
