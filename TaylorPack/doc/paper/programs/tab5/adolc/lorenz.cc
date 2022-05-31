#include <adouble.h>
#include <DRIVERS/odedrivers.h>
#include <adalloc.h>

#define S 10.0
#define R 28.0
#define B 2.66666666666666666666

void lorenz(int tag, double* px, double* pxp)
{
  adoublev x(3),xp(3);

  trace_on(tag);
  x <<= px;

  xp[0]=S*(x[1]-x[0]);
  xp[1]=x[0]*(R-x[2])-x[1];
  xp[2]=x[0]*x[1]-B*x[2];

  xp >>= pxp;
  trace_off(tag);
  return;
}
