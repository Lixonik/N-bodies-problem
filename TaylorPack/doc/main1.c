
/* save as main1.c */


#include <stdio.h>
#include <math.h>
#include "taylor.h"
int main(int argc, char **argv)
{
   MY_FLOAT  xx[3], t;
   double    h, abs_err, rel_err, h_return, log10abs_err;
   double    log10rel_err, endtime;
   int       nsteps = 100, step_ctrl_method = 2, direction = 1;
   int       order = 10;
   /* set initiaial conditions */
   xx[0] = 0.1;
   xx[1] = 0.2;
   xx[2] = 0.3;
   t     = 0.0;
   /* control parameters       */
   h= 0.001;
   abs_err = 1.0e-16;
   rel_err = 1.0e-16;
   log10abs_err = log10(abs_err); 
   log10rel_err = log10(rel_err); 
   endtime = 10.0;

   /* integrate 100 steps */
   while( -- nsteps > 0 && h_return != 0.0 ) {
      /* do something with xx and t. We just print it */
      printf("%f %f %f %f\n", xx[0],xx[1],xx[2],t);
      taylor_step_lorenz(&t, &xx[0], direction, step_ctrl_method,
                         log10abs_err, log10rel_err, 
                         &endtime, &h_return, &order);
   }       
}
