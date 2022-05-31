#include <math.h>
#include <stdio.h>

/*
next line is to have extended precision and to declare the time
stepper for extended precision. In the program, we will use the macros
in taylor to access gmp. See the file taylor_gmp.h for more details.
*/
#include "taylor_gmp.h"

/*
To avoid conflicts, the time stepper for double precision is declared
"by hand":
*/
int taylor_step_rtbp(double* ti,
                     double* x,
                     int     dir,
                     int     step_ctl,
                     double  log10abserr,
                     double  log10relerr,
                     double* endtime,
                     double* ht,
                     int*    order);

#define FA 4503599627370496L /* 2^52, 1/(machine precision) */

int main(void)
{
  double t,tf,x[6],tmp,tmpp,ht,xj,u;
  MY_FLOAT t_e,ht_e,x_e[6],tmp_e;
  int j,ord,ord2,kk;

/*
  initializing extended arithmetic...
*/
  mpf_set_default_prec(128);

  InitMyFloat(t_e);
  InitMyFloat(ht_e);
  for (j=0; j<6; j++) InitMyFloat(x_e[j]);
  InitMyFloat(tmp_e);

/*
  initializing variables...
*/
  t=0.e0;
  MakeMyFloatA(t_e,t);
  x[0]=-0.45;
  x[1]= 0.80;
  x[2]= 0.00;
  x[3]=-0.80;
  x[4]=-0.45;
  x[5]= 0.58;

  mpf_set_str(t_e,"0.0",10);
  mpf_set_str(x_e[0],"-0.45",10);
  mpf_set_str(x_e[0],"-0.45",10);
  mpf_set_str(x_e[1]," 0.80",10);
  mpf_set_str(x_e[2]," 0.00",10);
  mpf_set_str(x_e[3],"-0.80",10);
  mpf_set_str(x_e[4],"-0.45",10);
  mpf_set_str(x_e[5]," 0.58",10);

  puts("\nlocal error for the taylor method on an orbit of the rtbp");
  puts("column 1: time");
  puts("column 2: order selected by the step size control");
  puts("the remaining columns show the relative error, in multiples of the");
  puts("machine precision, for the variables x,y,z,px,py and pz\n");

  tf=1.0;
  kk=0;
/*
  main loop...
*/
  do {
    ++kk;
    taylor_step_rtbp(&t,x,1,1,-16,-16,&tf,&ht,&ord);
    ord2=2*ord;
    MakeMyFloatA(ht_e,ht);
    taylor_step_rtbp_gmp(&t_e,x_e,1,0,0,0,NULL,&ht_e,&ord2);

    printf("%18.16f %2d  |",t,ord);
/*
  error of the solution
*/
    for (j=0; j<6; j++)
    {
      MyFloatToDouble(xj,x_e[j]);
      tmpp=x[j]/xj;
      u=1.e0;
      tmp=tmpp-u;
      tmpp=FA*tmp;
      printf("%7.2f",tmpp);
    }
    puts("");
  } while (t < tf);

  return(0);
}
