#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
integration, with the extended arithmetic of GMP, of the RTBP.
the program integrates the initial condition (see below) for a unit
of RTBP time and writes the result into the file rtbp.res
*/

#include "taylor.h"

int main(int argc, char* argv[])
{
  MY_FLOAT t,tf,x[6],ht;
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
      puts("./rtbp 256 -80 rtbp.256.80\n");
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
  for (k=0; k<6; k++) InitMyFloat(x[k]);
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

  mpf_set_str(t,"0.0",10);
  mpf_set_str(tf,"1.0",10);

  puts("numerical integration starts...");

  k=0;
  do {
    kk=taylor_step_rtbp(&t,x,1,1,lerr,lerr,&tf,&ht,&ord);
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
  mpf_out_str(ff, 10, 0, x[3]); fprintf(ff,"\n");
  mpf_out_str(ff, 10, 0, x[4]); fprintf(ff,"\n");
  mpf_out_str(ff, 10, 0, x[5]); fprintf(ff,"\n");
  fclose(ff);

  return(0);
}
