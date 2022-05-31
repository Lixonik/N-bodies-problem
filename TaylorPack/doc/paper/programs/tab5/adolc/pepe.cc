#include <adouble.h>
#include <DRIVERS/odedrivers.h>
#include <adalloc.h>

#define EP 0.1
#define MU 0.1

void pepe(int tag, double pt, double* px, double* pxp)
{
  adoublev x(3),xp(3);

  trace_on(tag);
  x <<= px;

  xp[0]=1;
  xp[1]=x[2];
  xp[2]=-sin(x[1])-EP*x[2]+MU*sin(x[0]);

  xp >>= pxp;
  trace_off(tag);
  return;
}
