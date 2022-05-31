#include <math.h>
#include <stdio.h>

/*
program to compute the error of a long term numerical integration of
an orbit of the RTBP. The error is obtained comparing with an
integration with extended precision arithmetic (gmp). To avoid phase
errors (i.e., errors along the orbit), the comparison are done when
the orbit cuts z=0 (in the "ascending" direction).

next line is to have extended precision and to declare the time
stepper for extended precision. In the program, we will use the macros
in taylor to access gmp. See the file taylor_gmp.h for more details.
*/

#include "taylor_gmp.h"

int taylor_step_rtbp(double* ti,
                     double* x,
                     int     dir,
                     int     step_ctl,
                     double  log10abserr,
                     double  log10relerr,
                     double* endtime,
                     double* ht,
                     int*    order);

int main(int argc, char* argv[])
{
  MY_FLOAT t_e,ht_e,x_e[6],dif_e,tmp_e;
  double t,x[6],z,dif,tmp,ht,xj;
  int i,j,k,ord,ord2,nit;

  if (argc != 2)
    {
      puts("");
      puts("the program needs the number of Poincare iterates as argument");
      puts("example:");
      puts("./esp 10000\n");
      exit(1);
    }
  nit=atoi(argv[1]);

/*
  initializing extended arithmetic...
*/
  mpf_set_default_prec(128);

  InitMyFloat(t_e);
  InitMyFloat(ht_e);
  for (j=0; j<6; j++) InitMyFloat(x_e[j]);
  InitMyFloat(dif_e);
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

  k=0;
/*
  main loop...
*/
  do {
    ++k;
    i=0;
    z=1;
/*
    next loop is to detect the second passage through z=0
*/
    do {
      taylor_step_rtbp(&t,x,1,1,-16,-16,NULL,&ht,&ord);
      ord2=2*ord;
      MakeMyFloatA(ht_e,ht);
      taylor_step_rtbp_gmp(&t_e,x_e,1,0,0,0,NULL,&ht_e,&ord2);

      if (x[2]*z < 0) ++i;
      z=x[2];
    } while (i<2);
/*
    we use a newton iteration to compute the intersection with z=0
*/
    do {
      ht=-x[2]/x[5];
      taylor_step_rtbp(&t,x,1,0,0,0,NULL,&ht,&ord);

      NegateMyFloatA(tmp_e,x_e[2]);
      DivideMyFloatA(ht_e,tmp_e,x_e[5]);
      taylor_step_rtbp_gmp(&t_e,x_e,1,0,0,0,NULL,&ht_e,&ord2);

    } while (fabs(x[2]) > 1.e-17);
/*
  error of the solution
*/
    dif=0;
    for (j=0; j<6; j++)
    {
      if (j == 2) continue;
      MyFloatToDouble(xj,x_e[j]);
      tmp=fabs(x[j]-xj);
      if (tmp > dif) dif=tmp;
    }
    printf("%12.4e\n",dif);
  } while (k < nit);

  printf("integration time (in standard RTBP units): %f\n",t);

  return(0);   
}
