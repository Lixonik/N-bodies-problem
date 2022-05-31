#include <math.h>
#include <stdio.h>
#include <string.h>

#include "taylor.h"

#define MU "0.01"
#define NCAR 32
#define N  10

int main(int argc, char* argv[])
{
  void hamilton(MY_FLOAT x[6], MY_FLOAT* ham);
  static MY_FLOAT t,tf,x[6],ham,ham0,ham00,ht,dif;
  double tmp,td,eps,lerr;
  int j,k,kk,ord,idif,nbits,drift[2*N+1],*adrift;
  char nom[NCAR],noh[NCAR];
  FILE *fr;

  if (argc != 3)
    {
      puts("");
      puts("the program needs two arguments:");
      puts(" * length of the mantissa (in bits)");
      puts(" * log10 of the error threshold\n");
      puts("example:");
      puts("./ham 128 -40\n");
      exit(1);
    }
  nbits=atoi(argv[1]);
  printf("nbits: %d\n",nbits);
  lerr=atof(argv[2]);
  printf("log10(error): %7.2f\n",lerr);
/*
the ouput files are named using -log10 of the accuracy.
the "+1" in the next strcpy lines are to leave out the "-"
in the name.
*/
  strcpy(nom,argv[2]+1);
  strcat(nom,".res");
  strcpy(noh,argv[2]+1);
  strcat(noh,".ham");

  adrift=drift+N;
  for (j=-N; j<=N; j++) adrift[j]=0;

  eps=1;
  for (k=0; k<nbits; k++) eps /= 2;
  printf("machine precision: %e\n",eps);

  mpf_set_default_prec(nbits);
  InitMyFloat(t);
  InitMyFloat(tf);
  for (k=0; k<6; k++) InitMyFloat(x[k]);
  InitMyFloat(ham);
  InitMyFloat(ham0);
  InitMyFloat(ham00);
  InitMyFloat(dif);
  InitMyFloat(ht);

  mpf_set_str(x[0],"-0.45",10);
  mpf_set_str(x[1]," 0.80",10);
  mpf_set_str(x[2]," 0.00",10);
  mpf_set_str(x[3],"-0.80",10);
  mpf_set_str(x[4],"-0.45",10);
  mpf_set_str(x[5]," 0.58",10);

  mpf_out_str(stdout, 10, 0, x[0]); printf("\n");
  mpf_out_str(stdout, 10, 0, x[1]); printf("\n");
  mpf_out_str(stdout, 10, 0, x[2]); printf("\n");
  mpf_out_str(stdout, 10, 0, x[3]); printf("\n");
  mpf_out_str(stdout, 10, 0, x[4]); printf("\n");
  mpf_out_str(stdout, 10, 0, x[5]); printf("\n");

  hamilton(x,&ham00);
  printf("value of H at the initial condition: ");
  mpf_out_str(stdout, 10, 20, ham0); printf("\n");
  AssignMyFloat(ham0,ham00);

  fr=fopen(noh,"w");
  if (fr == NULL) {printf("cannot open %s\n",noh); exit(1);}
  printf("%f %e\n",0.0,0.0);

  mpf_set_str(t,"0.0",10);
  mpf_set_str(tf,"1000000",10);
  k=0;

  puts("numerical integration starts...");

  do {
    kk=taylor_step_rtbp(&t,x,1,2,lerr,lerr,&tf,&ht,&ord);
    hamilton(x,&ham);
    SubstractMyFloatA(dif,ham,ham0);
    AssignMyFloat(ham0,ham);
    MyFloatToDouble(td,t);
    MyFloatToDouble(tmp,dif);
    tmp /= eps;
    idif=(tmp > 0) ? (int)(tmp+0.5) : (int)(tmp-0.5);
    if (abs(idif) > N) {printf("error. idif=%d\n",idif); exit(1);}
    adrift[idif]++;

    if ((k%100) == 0)
      {
        printf("%d %20.15f %d %10.5f\n",k,td,ord,tmp); 
        SubstractMyFloatA(dif,ham,ham00);
        MyFloatToDouble(tmp,dif);
        tmp /= eps;
        fprintf(fr,"%12.2f %12.2f\n",td,tmp);
      }
    ++k;
  } while (kk == 0);
  --k;
  printf("%d %20.15f %d %10.5f\n",k,td,ord,tmp);
  SubstractMyFloatA(dif,ham,ham00);
  MyFloatToDouble(tmp,dif);
  tmp /= eps;
  fprintf(fr,"%12.2f %12.2f\n",td,tmp);
  fclose(fr);

  printf("%d %20.15f %d %10.5f\n",k,td,ord,tmp);
  puts("-------------");
  for (j=-N; j<=N; j++) printf("%3d %9d\n",j,adrift[j]);

  fr=fopen(nom,"w");
  if (fr == NULL)
    {
      printf("ULL: no puc obrir %s\n",nom);
    }
  else
    {
      for (j=-N; j<=N; j++) fprintf(fr,"%3d %9d\n",j,adrift[j]);
      fclose(fr);
    }

  return(0);
}
void hamilton(MY_FLOAT x[6], MY_FLOAT* h)
{
  static MY_FLOAT x2[6],r2,a,b,c,u,v,w,z,mu,umu,mu2,umu2,dmu,dumu;
  static int init=0;

  if (init == 0)
    {
      init=1;
      InitMyFloat(x2[0]);
      InitMyFloat(x2[1]);
      InitMyFloat(x2[2]);
      InitMyFloat(x2[3]);
      InitMyFloat(x2[4]);
      InitMyFloat(x2[5]);
      InitMyFloat(r2);
      InitMyFloat(a);
      InitMyFloat(b);
      InitMyFloat(c);
      InitMyFloat(u);
      InitMyFloat(v);
      InitMyFloat(w);
      InitMyFloat(z);
      InitMyFloat(mu);
      InitMyFloat(umu);
      InitMyFloat(mu2);
      InitMyFloat(umu2);
      InitMyFloat(dmu);
      InitMyFloat(dumu);

      mpf_set_str(mu,MU,10);
      AddMyFloatA(dmu,mu,mu);
      MultiplyMyFloatA(mu2,mu,mu);
      mpf_set_str(u,"1",10);
      SubstractMyFloatA(umu,u,mu);
      AddMyFloatA(dumu,umu,umu);
      MultiplyMyFloatA(umu2,umu,umu);
    }

  MultiplyMyFloatA(x2[0],x[0],x[0]);
  MultiplyMyFloatA(x2[1],x[1],x[1]);
  MultiplyMyFloatA(x2[2],x[2],x[2]);
  MultiplyMyFloatA(x2[3],x[3],x[3]);
  MultiplyMyFloatA(x2[4],x[4],x[4]);
  MultiplyMyFloatA(x2[5],x[5],x[5]);

//  r2=x2[0]+x2[1]+x2[2];
  AddMyFloatA(a,x2[0],x2[1]);
  AddMyFloatA(r2,a,x2[2]);

//  a=r2-2*MU*x[0]+MU*MU;
  MultiplyMyFloatA(u,dmu,x[0]);
  SubstractMyFloatA(v,r2,u);
  AddMyFloatA(a,v,mu2);

//  b=r2+2*(1-MU)*x[0]+(1-MU)*(1-MU);
  MultiplyMyFloatA(u,dumu,x[0]);
  AddMyFloatA(v,r2,u);
  AddMyFloatA(b,v,umu2);

//  c=x[1]*x[3]-x[0]*x[4];
  MultiplyMyFloatA(u,x[1],x[3]);
  MultiplyMyFloatA(v,x[0],x[4]);
  SubstractMyFloatA(c,u,v);

//  h=0.5*(x2[3]+x2[4]+x2[5])+c-(1-MU)/sqrt(a)-MU/sqrt(b);
  AddMyFloatA(u,x2[3],x2[4]);
  AddMyFloatA(v,u,x2[5]);
  mpf_set_str(u,"0.5",10);
  MultiplyMyFloatA(w,u,v);

  AddMyFloatA(z,w,c);

  sqrtMyFloatA(u,a);
  DivideMyFloatA(v,umu,u);
  SubstractMyFloatA(w,z,v);

  sqrtMyFloatA(u,b);
  DivideMyFloatA(v,mu,u);
  SubstractMyFloatA(*h,w,v);

  return;
}
