#include <stdio.h>
#include <stdlib.h>

#include "dd.h"
typedef qd_real MY_FLOAT;
#include "x86.h"

#include "taylor.h"

#define MU "0.01"

int main(int argc, char* argv[])
{
  MY_FLOAT hamilton(MY_FLOAT x[6]);
  MY_FLOAT t,tf,x[6],ham,ham0,dif,ht;
  double lerr,td,difd;
  int ord,k,kk;
  FILE *fr;

  unsigned short old_cw;
  x86_fix_start(&old_cw);

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
  t="0.0";
  x[0]="-0.45";
  x[1]=" 0.80";
  x[2]=" 0.00";
  x[3]="-0.80";
  x[4]="-0.45";
  x[5]=" 0.58";

  tf="1000000";
/*
  initializing computations...
*/
  ham0=hamilton(x);

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
    dif=ham-ham0;
    if (((k%1000) == 0) || (kk != 0))
      {
	td=t;
	difd=dif;
        printf("%11.3f %2d %12.3e\n",td,ord,difd);
        fprintf(fr,"%11.3f %12.3e\n",td,difd);
      }
    ++k;
  } while (kk == 0);
  fclose(fr);

  x86_fix_end(&old_cw);

  return(0);
}
MY_FLOAT hamilton(MY_FLOAT x[6])
{
  MY_FLOAT x2[6],r2,a,b,c,h,mu;
  mu=MU;
  x2[0]=x[0]*x[0]; x2[1]=x[1]*x[1]; x2[2]=x[2]*x[2];
  x2[3]=x[3]*x[3]; x2[4]=x[4]*x[4]; x2[5]=x[5]*x[5];
  r2=x2[0]+x2[1]+x2[2];
  a=r2-2*mu*x[0]+mu*mu;
  b=r2+2*(1-mu)*x[0]+(1-mu)*(1-mu);
  c=x[1]*x[3]-x[0]*x[4];
  h=0.5*(x2[3]+x2[4]+x2[5])+c-(1-mu)/sqrt(a)-mu/sqrt(b);
  return(h);
}
