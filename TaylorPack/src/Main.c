/*********************************************************************
 *
 *       Taylor  
 *
 *    Copyright (C) 1999  Maorong Zou, Angel Jorba
 *
 *
 *  This file is part of taylor.
 *
 * Taylor is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * Taylor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taylor; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *
 *************************************************************************/

#define MAIN_C
#include <ctype.h>
#include "Header.h"
#include "SampleHeader.h"
#include "gmpHeader.h"
#include "qdheader.h"
#include "mpfrheader.h"
#include "../VERSION"
int    debug = 0;
int    ddouble = 0;
int    expandpower = 1;
int    expandsum = 10;
int    havesum = 0;
int    genHeader = 0;
int    genMain = 0;
int    genStep = 0;
int    genJet = 0;
int    cdouble = 0;
int    gmp = 0;
int    mpfr = 0;
int    gmp_precision=0;
int    mpfr_precision=0;
int    ldouble=0;
int    qd2 = 0;
int    qd4 = 0;
int    f77hook = 0;
int    step_ctrl = 1;
int    use_rational_exponent=0;
char   *outNames[10];
char   *suffixes[10];
int    num_names = 0;
char   *outName = NULL;
char   *suffix = NULL;
char   *header_name = NULL;
char   *uss_name = NULL;
char   *uso_name = NULL;
FILE   *outfile = NULL;
FILE   *infile = NULL;

extern FILE *yyin;

void help(char *);
void genSampleHeader();
extern int yyparse();

int main(int ac, char **av)
{
  int i, header=0, nariths=0;
  char *arith=NULL;

  for(i = 1; i < ac; i++)
    {
      char *arg = av[i];
      if(arg[0] == '-')
	{
	  switch(arg[1])
	    {
	    case 'n':                   /* -name */
	      if(!strcmp(arg,"-n") || !strcmp(arg,"-name"))
		{
		  if(++i < ac) {
                    suffixes[num_names++] = av[i];
                    if(num_names >= 10) {
                      fprintf(stderr, "Too many names ...\n"); 
                      exit(1);
                    }
                  }
		  else --i;
		}
	      break;
	    case 'u':
	      if(!strcmp(arg,"-u") || !strcmp(arg,"-ud") || !strncmp(arg,"-userdefined", 9)) 
		{
		  if(i+2 < ac && av[i+1][0] != '-' && av[i+2][0] != '-' ) {
		    i++; uss_name = av[i];
                    i++;  uso_name = av[i];
		  } else {  help(av[0]);  }
		}
              break;
	    case 'f':
	      if(!strcmp(arg,"-f77")) { f77hook=1;}
	      break;
            case 'm':
	      if(!strcmp(arg,"-main_only") || !strcmp(arg,"-mainonly")) { genMain = 1;}
	      else if(!strcmp(arg,"-main")) { genMain = 2;}
	      else if(!strcmp(arg,"-mpfr"))
		{ ddouble = 0; gmp=0; ldouble=0; mpfr=1; nariths++; arith="mpfr";}
	      else if(!strcmp(arg,"-mpfr_precision")) {
                if( ac > i+1 && atoi(av[i+1]) > 0)
                  {
                    ddouble=0; ldouble=0;
                    gmp =0; qd4 = qd2 = 0; mpfr=1;
                    mpfr_precision = atoi(av[i+1]);
                    i++;
                    nariths++; arith="mpfr";
                  } else {
                    fprintf(stderr,"\t The -mpfr_precision flag must be followed by PRECISION in number of bits\n");
                    exit(1);
                  }	
	      }
              break;
            case 's':
	      if(!strcmp(arg,"-step")) {
                genStep = 1;
                step_ctrl = 1;
                if(++i < ac && strlen(av[i]) == 1 && isdigit(av[i][0])) {
                  step_ctrl = atoi(av[i]);
                  if( step_ctrl < 0 || step_ctrl >= 4) {
                    fprintf(stderr, "Invalid step control parameter: %d\n", step_ctrl);
                    step_ctrl = 1;
                  }
                } else --i;                
              } else if( !strcmp(arg, "-sqrt")) {
                use_rational_exponent=1;         
	      }     
              break;
            case 'j':
	      if(!strcmp(arg,"-jet")) { genJet = 1;} 
              break;
	    case 'h':
	      if(!strcmp(arg,"-header_name") || !strcmp(arg,"-headername")  ) { if(++i < ac) { header_name = av[i];} }
	      else if(!strcmp(arg,"-header")) { header = 1;}
	      else { help(av[0]);}
	      break;
	    case 'd':
	      if(!strcmp(arg,"-debug") || !strcmp(arg,"-d"))
		debug = 1;
	      else if(!strcmp(arg,"-doubledouble") || !strcmp(arg,"-ddouble"))
		{ ddouble = 1; gmp=0; ldouble=0; nariths++; arith="doubledouble";}
	      else if(!strcmp(arg,"-dd_real") || !strcmp(arg,"-dd"))
		{ qd2 =1 ; qd4 =0; ddouble=0; gmp =0; ldouble=0; nariths++; arith="dd_real";}
              break;
	    case 'q':
	      if(!strcmp(arg,"-qd") || !strcmp(arg,"-qd_real")) {
		qd4 = 1; qd2 = 0; ddouble=0; gmp=0; ldouble=0; nariths++; arith="qd_real";
	      }
	      break;
	    case 'l':
	      if(!strcmp(arg,"-long_double") || !strcmp(arg,"-longdouble")) {
		qd4 = 0; qd2 = 0; ddouble=0; gmp=0;  ldouble=1; nariths++; arith="longdouble";
	      }
	      break;
            case 'g':
	      if(!strcmp(arg,"-gmp_precision")) {
                if( ac > i+1 && atoi(av[i+1]) > 0)
                  {
                    ddouble=0; ldouble=0;
                    gmp =1; qd4 = qd2 = 0;
                    gmp_precision = atoi(av[i+1]);
                    i++;
                    nariths++; arith="gmp";
                  } else {
                    fprintf(stderr,"\t The -gmp_precision flag must be followed by PRECISION in number of bits\n");
                    exit(1);
                  }
              } else if(!strcmp(arg,"-gmp")) {
                ddouble=0; ldouble=0;
                gmp =1; qd4 = qd2 = 0;
                nariths++; arith="gmp";
              }
              break;
            case 'c':
              if(!strcmp(arg,"-constantsafe") || !strcmp(arg,"-const"))
                { cdouble = 1;}
	      break; 
	    case 'e':
	      if(!strncmp(arg,"-expandsum",8))
		{
		  if(++i < ac) expandsum = atoi(av[i]);
		  else --i;
		}
	      else if(!strncmp(arg,"-expandpower",8))
		{
		  if(++i < ac) expandpower = atoi(av[i]);
		  else --i;
		}
	      break;
	    case 'v':
	      if(!strcmp(arg,"-v") ||  !strcmp(arg,"-verbose") ) debug = 1;
              else  if(!strcmp(arg,"-version")) 
                {
                  fprintf(stderr,"%s\n", versionString);
                  exit(0);
                }
	      break;
	    case 'o':
	      if(!strcmp(arg,"-o") || !strcmp(arg,"-out"))
		{
		  if(++i < ac) 
		    { 
		      char *str = av[i];
		      if((outfile = fopen(str, "w")) == NULL)
			{
			  fprintf(stderr, "Cannot open '%s'\n", str);
			  exit(1);
			}
		    }
		  else --i;
		}
	      break;
	    default:
	      break;
	    }
	}
      else {
        if((infile = fopen(av[i], "r")) == NULL)
          {
            fprintf(stderr, "Cannot open '%s'\n", av[i]);
            exit(2);
          } else {
            if(suffix == NULL) 
              {
                int ii, len = strlen(av[i]);
                char *s = av[i];
                suffix = (char *)malloc( (len+len+128)*sizeof(char));
                for(ii=0; ii<len; ii++) {
                  char c = s[ii];
                  if( isalnum(c)) { suffix[ii] =c;} else {suffix[ii]='_';}
                }
                suffix[ii]='\0';
              }
          }
      }
    }  
  if(suffixes[0] == NULL) { 
    if(suffix != NULL) { suffixes[0] = suffix; } else { suffixes[0] = "_NoName";} num_names = 1;
  }
  if(nariths > 1) {
    fprintf(stderr, "\n Warning: You have specified more than one arithmetic options. Only \"%s\" will be used.\n\n", arith);
  }

  {
    int i, j, len;
    for(j = 0; j < num_names; j++) {
      len = strlen(suffixes[j]);
      for(i=0; i< len; i++) {
        if(!isalnum(suffixes[j][i]) && suffixes[j][i] != '_' ) {
          fprintf(stderr, "Name '%s' must be contain only alpha numeric characters.\n", suffixes[j]); exit(1);
        }
      }
      outNames[j] = (char *)malloc((len+32)*sizeof(char));
      sprintf(outNames[j], "taylor_coefficients_%s", suffixes[j]);
    }
  }
  suffix = suffixes[0];
  outName = outNames[0];

  if(infile == NULL) infile= stdin;
  if(outfile == NULL) outfile=stdout;

  if(header) {
    if((genStep|genJet|genMain|genHeader) == 0) {
      fprintf(outfile, "%s\n",sample_headerI);              
      genSampleHeader();  
      exit(0);
    } else {
      genHeader = 1;
    }
  }

  if( (genStep|genJet|genMain|genHeader) == 0) { genMain = 2;}

  if(genMain > 1) { genStep = 1; genJet = 1; genHeader = 1;}
  
  if(header_name == NULL) { header_name = "taylor.h";}
  


  initialize_vars();
  yyin = infile;
  yyparse();
  showPaserInfo();
  identifyFunctions();   
  checkVars();
  checkEquations();
  decompose();
  showVars();
  genVariables(); 
  if(neqns == 0) {fprintf(stderr, "\nNo ODEs present. Bye!\n\n"); exit(3);}
  gencode();
  exit(0);
}
/********************************************************/
void help(char *name)
{
  fprintf(stderr, "Taylor %s\n\n", versionString);
  fprintf(stderr, "Usage: %s \n", name);
  fprintf(stderr, "  [-name ODE_NAME]\n");
  fprintf(stderr, "  [-o outfile] \n");
  fprintf(stderr, "  [-doubledouble | -qd_real | -dd_real | -gmp | -gmp_precision PRECISION ] \n");
  fprintf(stderr, "  [-mpfr | -mpfr_precision PRECISION ] \n");
  fprintf(stderr, "  [-main | -header | -jet | -main_only] \n");
  fprintf(stderr, "  [-step STEP_CONTROL_METHOD ]\n");
  fprintf(stderr, "  [-u | -userdefined ] STEP_SIZE_FUNCTION_NAME ORDER_FUNCTION_NAME \n");
  fprintf(stderr, "  [-f77 ]\n");
  fprintf(stderr, "  [-sqrt ]\n");
  fprintf(stderr, "  [-headername HEADER_FILE_NAME]\n");
  fprintf(stderr, "  [-debug] [-help] [-v]  file\n");
  exit(0);
}
/********************************************************/

void genSampleHeader()
{
  fprintf(outfile,"/***********************************************************************\n");
  fprintf(outfile," *\n");
  fprintf(outfile," * Code generated by the TAYLOR translator.\n");
  fprintf(outfile," */\n\n");

  fprintf(outfile, "#ifndef _TAYLOR_H_\n");
  fprintf(outfile, "#define _TAYLOR_H_\n");
  if(qd4 | qd2 ) { /* use library qd */
    fprintf(outfile, "#include <iostream>\n");
    fprintf(outfile, "#include <qd/qd.h>\n");
    fprintf(outfile, "#include <qd/fpu.h>\n");
    fprintf(outfile, "using namespace std;\n");    
    if(qd4) {  /* use quad double */
      fprintf(outfile,"typedef qd_real MY_FLOAT;\n");      
    } else if(qd2) { /* use double double */
      fprintf(outfile,"typedef dd_real MY_FLOAT;\n");      
    }
    fprintf(outfile,"#include<stdio.h>\n");  
    fprintf(outfile,"#include<stdlib.h>\n");  
    fprintf(outfile,"#include<string.h>\n");      
    fprintf(outfile, "%s\n",qd_header);
  } else if(mpfr) {
    fprintf(outfile,"#include<math.h>\n");      
    fprintf(outfile,"#include<stdio.h>\n");  
    fprintf(outfile,"#include<stdlib.h>\n");  
    fprintf(outfile,"#include<string.h>\n");  
    fprintf(outfile,"#include<mpfr.h>\n");      
    fprintf(outfile, "%s\n", mpfr_header);
  } else if(gmp) {
    fprintf(outfile,"#include<stdio.h>\n");  
    fprintf(outfile,"#include<stdlib.h>\n");  
    fprintf(outfile,"#include<string.h>\n");  
    fprintf(outfile,"#include<gmp.h>\n");      
    fprintf(outfile,"#include<math.h>\n");      
    fprintf(outfile, "%s\n",gmp_header);
  } else if(ldouble) {
    fprintf(outfile,"typedef long double MY_FLOAT;\n\n");
    fprintf(outfile,"#include<math.h>\n");      
    fprintf(outfile,"#include<stdio.h>\n");  
    fprintf(outfile,"#include<stdlib.h>\n");  
    fprintf(outfile,"#include<string.h>\n");  
    fprintf(outfile, "%s\n",sample_header);
  } else if(ddouble) {
    fprintf(outfile, "#include \"doubledouble.h\"\n");
    fprintf(outfile,"typedef doubledouble MY_FLOAT;\n");
    fprintf(outfile,"#define double doubledouble\n\n");
    fprintf(outfile,"#include<math.h>\n");      
    fprintf(outfile,"#include<stdio.h>\n");  
    fprintf(outfile,"#include<stdlib.h>\n");  
    fprintf(outfile,"#include<string.h>\n");  
    fprintf(outfile, "%s\n",sample_header);
  } else {
    fprintf(outfile,"typedef double MY_FLOAT;\n\n");
    fprintf(outfile,"#include<math.h>\n");      
    fprintf(outfile,"#include<stdio.h>\n");  
    fprintf(outfile,"#include<stdlib.h>\n");  
    fprintf(outfile,"#include<string.h>\n");  
    fprintf(outfile, "%s\n",sample_header);
  }
  fprintf(outfile, "#endif\n");

  /*  function prototypes */
  {
    int i;
    for(i = 0; i < num_names; i++) {
      fprintf(outfile,"\nMY_FLOAT **%s(MY_FLOAT t, MY_FLOAT *x, int order);\n", outNames[i]);
      fprintf(outfile,"\nMY_FLOAT **%sA(MY_FLOAT t, MY_FLOAT *x, int order, int reuse_last_computation);\n", outNames[i]);
      fprintf(outfile, "int       taylor_step_%s(MY_FLOAT *ti, MY_FLOAT *x, int dir, int step_ctl,\n", suffixes[i]);
      fprintf(outfile, "                          double log10abserr, double log10relerr, \n");
      fprintf(outfile, "                          MY_FLOAT *endtime, MY_FLOAT *ht, int *order);\n\n");
    }
  }
  fprintf(outfile, "/************************************************************************/\n\n");
}
/********************************************************/
