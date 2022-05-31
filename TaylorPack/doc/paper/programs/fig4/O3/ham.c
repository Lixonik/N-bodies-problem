#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "taylor.h"

#define MU 0.01
#define FA 4503599627370496L /* 2^52, machine epsilon for the Pentium */

int main(int argc, char* argv[])
{
  double hamilton(double x[6]);
  double t,tf,x[6],ham,ham0,dif,ht,lerr;
  int ord,k,kk;
  FILE *fr;

  if (argc != 2)
    {
      puts("");
      puts("the program needs log10(error) as argument");
      puts("example:");
      puts("./ham -16\n");
      exit(1);
    }
  lerr=atof(argv[1]);
  printf("error: %7.2f\n",lerr);
/*
  initial condition
*/
  t=0.e0;
  x[0]=-0.45;
  x[1]= 0.80;
  x[2]= 0.00;
  x[3]=-0.80;
  x[4]=-0.45;
  x[5]= 0.58;

  tf=1.e6;
/*
  initializing computations...
*/
  ham0=hamilton(x);
  printf("value of H at the initial condition: %20.16f\n",ham0);

  fr=fopen("ham.res","w");
  if (fr == NULL) {puts("cannot open ham.res"); exit(1);}

  puts("numerical integration starts...");
/*
  main loop...
*/
  k=0;
  do {
    kk=taylor_step_rtbp(&t,x,1,1,lerr,lerr,&tf,&ht,&ord);
/*
  error in the hamiltonian, in multiples of the machine epsilon
*/
    ham=hamilton(x);
    dif=FA*(ham-ham0);
    if (((k%1000) == 0) || (kk != 0))
      {
        printf("%11.3f %2d %5.1f\n",t,ord,dif);
        fprintf(fr,"%11.3f %5.1f\n",t,dif);
      }
    ++k;
  } while (kk == 0);
  fclose(fr);

  return(0);
}
double hamilton(double x[6])
{
  double x2[6],r2,a,b,c,h;
  x2[0]=x[0]*x[0]; x2[1]=x[1]*x[1]; x2[2]=x[2]*x[2];
  x2[3]=x[3]*x[3]; x2[4]=x[4]*x[4]; x2[5]=x[5]*x[5];
  r2=x2[0]+x2[1]+x2[2];
  a=r2-2*MU*x[0]+MU*MU;
  b=r2+2*(1-MU)*x[0]+(1-MU)*(1-MU);
  c=x[1]*x[3]-x[0]*x[4];
  h=0.5*(x2[3]+x2[4]+x2[5])+c-(1-MU)/sqrt(a)-MU/sqrt(b);
  return(h);
}
