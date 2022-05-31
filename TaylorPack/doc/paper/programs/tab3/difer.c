#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
difference, in multiples of the machine precision, of two points
(produced by program ./rtbp) contained in two different files.
*/

#include "taylor.h"

int main(int argc, char* argv[])
{
  MY_FLOAT a,b,c,u,tmp;
  double d,e,eps;
  int k,nbits;
  FILE *fa,*fb,*ftmp;

  if (argc != 4)
    {
      puts("");
      puts("the program needs three arguments:");
      puts(" - length of the mantissa (in bits)");
      puts(" - name of the 1st file to compare");
      puts(" - name of the 2nd file to compare\n");
      puts("example:");
      puts("./difer 256 rtbp.256.80 rtbp.512.160\n");
      exit(1);
    }
  nbits=atoi(argv[1]);

  printf("nbits: %d\n",nbits);

  eps=1;
  for (k=0; k<nbits; k++) eps /= 2;
  printf("machine precision of the selected arithmetic: %e\n",eps);

  mpf_set_default_prec(nbits);
  InitMyFloat(a);
  InitMyFloat(b);
  InitMyFloat(c);
  InitMyFloat(u);
  InitMyFloat(tmp);

  mpf_set_str(u,"1.0",10);

  fa=fopen(argv[2],"r");
  if (fa == NULL) {printf("no puc obrir %s\n",argv[2]);}
  fb=fopen(argv[3],"r");
  if (fb == NULL) {printf("no puc obrir %s\n",argv[3]);}

  while (mpf_inp_str(a,fa,10) != 0)
  {
    mpf_inp_str(b,fb,10);
    DivideMyFloatA(tmp,a,b);

/*
As we are not sure of the number of bits in the mantissa of a GMP
number, and we need to compute the number of wrong bits in the
mantissa, we write the number into a file and we read it again, in
base 2. In this way we are forcing GMP to cut the number to the
length prescribed by the mpf_set_default_prec funtion.

In some sense, this is similar to the -ffloat-store flag of the gcc
compiler used, for instance, to compute the error in the double
precision examples.
*/
    ftmp=fopen("difer.tmp","w");
    if (ftmp == NULL) {puts("cannot open difer.tmp (1)"); exit(1);}
    mpf_out_str(ftmp,2,0,tmp);
    fclose(ftmp);
    ftmp=fopen("difer.tmp","r");
    if (ftmp == NULL) {puts("cannot open difer.tmp (2)"); exit(1);}
    mpf_inp_str(tmp,ftmp,2);
    fclose(ftmp);

    SubstractMyFloatA(c,u,tmp);
    MyFloatToDouble(d,c);
    e=d/eps;
    printf("%e %10.6f  ",d,e);
    printf("\n");
  }

  fclose(fb);
  fclose(fa);

  return(0);
}
