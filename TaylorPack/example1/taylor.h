
/************************************************************************
 *
 *  A sample taylor.h
 *     Here is a list of macros/functions needed to compile the auto
 *     generated taylor polynomial procedure.  
 *
 */


typedef double MY_FLOAT;

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*
 *  MY_FLOAT is the data type to be used in computing derivatives. 
 *  It may be 'float', 'double' or user defined private data types
 *  like 'doubledouble', 'complex' etc. 
 */
#ifndef _TAYLOR_
#define _TAYLOR_
#include <math.h>


/* for double or doubledouble, don't need to initialize */
#define   InitMyFloat(r)            
#define   ClearMyFloat(r)           
 
/* assign b to a */
#define   AssignMyFloat(a, b)       {(a)=(b);}

/* creat a MY_FLOAT from a, assigne to r. a is an integer or a float */
#define   MakeMyFloatA(r,a)         (r=(double)(a))

/* creat a MY_FLOAT from a, assign to r and return r */
#define   MakeMyFloatB(r,a)         (r=(double)(a),r)

/* addition r=a+b   */
#define   AddMyFloatA(r,a,b)        (r=(a)+(b))

/* substraction r=a-b */
#define   SubstractMyFloatA(r,a,b)  (r=(a)-(b))

/* multiplciation r=a*b */
#define   MultiplyMyFloatA(r,a,b)   (r=(a)*(b))

/* division r=a/b */
#define   DivideMyFloatA(r,a,b)     (r=(a)/(b))

/* negation r=-a*/
#define   NegateMyFloatA(r,a)       (r= -(a))

/* square root r=sqrt(a) */
#define   sqrtMyFloatA(r,a)         (r=sqrt(a))
/* exponentiation r=a^b */
#define   ExponentiateMyFloatA(r,a,b)  (r=pow((a),(b)))
/* exponentiation r=a^b, b is an integer */
#define   ExponentiateMyFloatIA(r,a,b)  (r=pow((a),(double)(b)))
/* sin(a)  r=sin(a) */
#define   sinMyFloatA(r,a)          (r=sin((a)))
/* cos(a)  r=cos(a) */
#define   cosMyFloatA(r,a)          (r=cos((a)))
/* tan(a)  r=tan(a) */
#define   tanMyFloatA(r,a)          (r=tan((a)))
/* atan(a) r=atan(a) */
#define   atanMyFloatA(r,a)         (r=atan((a)))
/* exp(a)  r=exp(a) */
#define   expMyFloatA(r,a)          (r=exp((a)))
/* log(a)  r=log(a) */
#define   logMyFloatA(r,a)          (r=log((a)))
/* sinh(a) r=sinh(a) */
#define   sinhMyFloatA(r,a)         (r=sinh(a))
/* cosh(a) r=cosh(a) */
#define   coshMyFloatA(r,a)          (r=cosh(a))
/* tanh(a) r=tanh(a) */
#define   tanhMyFloatA(r,a)          (r=tanh(a))


/* log10(a)  r=log10(a) */
#define   log10MyFloatA(r,a)         (r=log10((a)))
/* fabs(a) r=fabs(a) */
#define   fabsMyFloatA(r,a)          (r=fabs(a))

/* convert to int */
#define   MyFloatToInt(ir,fa)       (ir=(int)(fa))
/* convert to double */
#define   MyFloatToDouble(ir,fa)    (ir=(double)(fa))


/* boolean operation  */
#define   MyFloatA_GE_B(a,b)        ((a)>=(b))
#define   MyFloatA_GT_B(a,b)        ((a)> (b))
#define   MyFloatA_LE_B(a,b)        ((a)<=(b))
#define   MyFloatA_LT_B(a,b)        ((a)< (b))
#define   MyFloatA_EQ_B(a,b)        ((a)==(b))
#define   MyFloatA_NEQ_B(a,b)       ((a)!=(b))


/************************************************************************/
#endif

