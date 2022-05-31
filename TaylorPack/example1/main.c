/***********************************************************************
 *                                                                     *
 *  Example 1:  asteroid                                               *
 *                                                                     *
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>


#define MAIN_C
#include "taylor.h"

int        nsines[20], ncosines[20]; /* mark the number of sin/cos terms in P[i] */

MY_FLOAT   term0[20];                /* constant term in Fourier series' */

MY_FLOAT   sincoefs[20][201];        /* coefficients of sin terms        */
short      sinfreqs[20][201][5];     /* freq vectors */

MY_FLOAT   coscoefs[20][201];        /* coefficients of cos terms        */
short      cosfreqs[20][201][5];     /* freq vectors */

int        mxterms = 400;            /* maximu number of terms */

MY_FLOAT   omega[10], phi[10];

/*********************************************************************/
extern MY_FLOAT **taylor_coefficients_input( MY_FLOAT t, MY_FLOAT *x, int order);
/*********************************************************************/

void readCoefficients(MY_FLOAT hq)
{
  FILE *fp, *fopen();
  char line[256], ddd[128];
  int  cnt;
  
  if((fp = fopen("coefs", "r")) == NULL)
    {
      fprintf(stderr, "Couldn't open \"coefs\" for reading ...\n");
      exit(1);
    }

  for(cnt = 0; cnt < 20; cnt++)
    {
      int        nread, i,j, l, mxterms_this;
      int        nsines_t = 0;
      int        ncosines_t = 0;
      int        f[6];
      MY_FLOAT   a;

      fgets(line, 255, fp);
      fgets(ddd,  127, fp);
      mxterms_this = atoi(ddd);
      fgets(ddd, 128, fp);
      term0[cnt] = atof(ddd);
      fprintf(stderr, "Processing %s \t\t %d entries, cterm=%g\n", line, mxterms_this, term0[cnt]);

      mxterms_this--;
      for(i = 0; i < mxterms_this; i++)
	{
	  if(fgets(line, 255, fp))
	    {
	      nread = sscanf(line, "%d %d %d %d %d %d %s", f, f+1, f+2, f+3, f+4, &l, ddd);
	      a = atof(ddd);
	      if(nread == 7)
		{
		  a *= hq;
		  if(l == 0) /* cos */
		    {
		      if(ncosines_t < 200)
			{
			  coscoefs[cnt][ncosines_t] = a;
			  for(j = 0; j < 5; j++) cosfreqs[cnt][ncosines_t][j] = f[j];
			  ncosines_t++;
			}
		    }
		  else
		    {
		      if(nsines_t < 200)
			{
			  sincoefs[cnt][nsines_t] = a;
			  for(j = 0; j < 5; j++) sinfreqs[cnt][nsines_t][j] = f[j];
			  nsines_t++;
			}
		    }
		}
	    }
	}
      nsines[cnt] = nsines_t;
      ncosines[cnt] = ncosines_t;
      fprintf(stderr,"\t\t\t Read %d sines and %d cosines.\n", nsines_t, ncosines_t);
    }
  for(cnt = 0; cnt < 20; cnt++)
    {
      fprintf(stderr, "ns%d=%d; nc%d=%d;\n", cnt, nsines[cnt]-1,cnt, ncosines[cnt]-1);
    }
}
/**************************************************************************/

main()
{
  MY_FLOAT   xy[10], tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, h =8.0*atan(1.0)/27.3216610; 
  MY_FLOAT   **jet;
  int        i , j;

  /* initial value */
  xy[0] = 0.0;
  xy[1] = 0.0;
  xy[2] = 0.0;
  xy[3] = 0.0;
  xy[4] = 0.0;
  xy[5] = 0.0;

   omega[0] = 1.0;
   omega[1] = 0.925195997455093;
   omega[2] = 0.0845477852931292;
   omega[3] = -0.0401883841204748;
   omega[4] = 0.0000357408131981537;
   phi[0] = 0.0;
   phi[1] = 0.0;
   phi[2] = 0.0;
   phi[3] = 0.0;
   phi[4] = 0.0;

  readCoefficients(0.1);

  for(i = 0; i < 365; i++)
    {
      tmp1 = 0.0; tmp2 = 0.0; tmp3 = 0.0, tmp4 = 0.0, tmp5 = 0.0, tmp6 = 0.0;
      jet = taylor_coefficients_input(0.0, xy, 8);

      printf("%f %f %f %f %f %f\n", xy[0] , xy[1], xy[2], xy[3], xy[4], xy[5]);
      for(j = 20; j > 0; j--)
	{
	  tmp1 = (tmp1 + jet[0][j])* h;
	  tmp2 = (tmp2 + jet[1][j])* h;
	  tmp3 = (tmp3 + jet[2][j])* h;
	  tmp4 = (tmp4 + jet[3][j])* h;
	  tmp5 = (tmp5 + jet[4][j])* h;
	  tmp6 = (tmp6 + jet[5][j])* h;
	}
      xy[0] = xy[0] + tmp1;
      xy[1] = xy[1] + tmp2;
      xy[2] = xy[2] + tmp3;
      xy[3] = xy[3] + tmp4;
      xy[4] = xy[4] + tmp5;
      xy[5] = xy[5] + tmp6;
    }
}
