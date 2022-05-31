#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lorenz.h"

int main(int argc, char* argv[])
{
  MY_FLOAT t,tf,x[3],ht;
  double td,eps,lerr;
  int k,kk,ord,nbits;
  FILE *ff;

  if (argc != 4)
    {
      puts("");
      puts("the program needs three arguments:");
      puts(" - length of the mantissa (in bits)");
      puts(" - log10");
      puts(" - name of the results file\n");
      puts("example:");
      puts("./lorenz 256 -80 lorenz.256.80\n");
      exit(1);
    }
  nbits=atoi(argv[1]);
  printf("nbits: %d\n",nbits);
  lerr=atof(argv[2]);
  printf("log10(error): %7.2f\n",lerr);

  eps=1;
  for (k=0; k<nbits; k++) eps /= 2;
  printf("machine precision: %e\n",eps);

  mpf_set_default_prec(nbits);
  InitMyFloat(t);
  InitMyFloat(tf);
  for (k=0; k<3; k++) InitMyFloat(x[k]);
  InitMyFloat(ht);

  mpf_set_str(x[0],"-8.0",10);
  mpf_set_str(x[1]," 8.0",10);
  mpf_set_str(x[2],"27.0",10);

  mpf_set_str(t,"0.0",10);
  mpf_set_str(tf,"16.0",10);

  do {
    kk=taylor_step_lorenz(&t,x,1,1,lerr,lerr,&tf,&ht,&ord);
    MyFloatToDouble(td,t);
    printf("%2d %4d %20.15f\n",k,ord,td);
    ++k;
  } while (kk == 0);

  ff=fopen(argv[3],"w");
  if (ff == NULL) {printf("cannot open %s\n",argv[3]); exit(1);}
  mpf_out_str(ff, 10, 0, t); fprintf(ff,"\n");
  mpf_out_str(ff, 10, 0, x[0]); fprintf(ff,"\n");
  mpf_out_str(ff, 10, 0, x[1]); fprintf(ff,"\n");
  mpf_out_str(ff, 10, 0, x[2]); fprintf(ff,"\n");
  fclose(ff);

  return(0);
}
