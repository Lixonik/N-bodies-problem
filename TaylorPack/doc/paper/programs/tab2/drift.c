#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "taylor.h"

#define MU 0.01
#define FA 4503599627370496L /* 2^52, machine epsilon for the Pentium */
#define NC 32
#define N  10

int main(int argc, char* argv[])
{
  double hamilton(double x[6]);
  double t,tf,x[6],ham,ham0,dif,ht,lerr,tmp;
  int ord,k,kk,idif,drift[2*N+1],*adrift,j;
  char nom[NC];
  FILE *fr;

  if (argc != 2)
    {
      puts("");
      puts("the program needs log10(error) as argument");
      puts("example:");
      puts("./drift -16\n");
      exit(1);
    }
  lerr=atof(argv[1]);
  printf("log10(error): %7.2f\n",lerr);
  strcpy(nom,argv[1]+1);
  strcat(nom,".res");

  adrift=drift+N;
  for (j=-N; j<=N; j++) adrift[j]=0;

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
    tmp=ham-ham0;
    dif=FA*tmp;
    if (((k%2000) == 0) || (kk != 0)) printf("%11.3f %2d %6.2f\n",t,ord,dif);
    idif=(dif > 0) ? (int)(dif+0.5) : (int)(dif-0.5);
    if (abs(idif) > N) {printf("error. idif=%d\n",idif); exit(1);}
    adrift[idif]++;

    ham0=ham;

    ++k;
  } while (kk == 0);

  puts("-------------");
  for (j=-N; j<=N; j++) printf("%3d %9d\n",j,adrift[j]);

  fr=fopen(nom,"w");
  if (fr == NULL)
    {
      printf("error: cannot open %s\n",nom);
    }
  else
    {
      for (j=-N; j<=N; j++) fprintf(fr,"%3d %9d\n",j,adrift[j]);
      fclose(fr);
    }

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
