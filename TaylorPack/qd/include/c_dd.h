/*
 * include/c_dd.h
 *
 * This work was supported by the Director, Office of Science, Division
 * of Mathematical, Information, and Computational Sciences of the
 * U.S. Department of Energy under contract number DE-AC03-76SF00098.
 *
 * Copyright (c) 2000-2001
 *
 * Contains C wrapper function prototypes for double-double precision
 * arithmetic.  This can also be used from fortran code.
 */
#ifndef _C_DD_H_
#define _C_DD_H_

#include "dd.h"

#ifdef CRAY_STRINGS
#include <fortran.h>
#endif

#define _NO_CHANGE      0
#define _ADD_UNDERSCORE 1
#define _UPPER_CASE     2

#ifdef ADD_UNDERSCORE
#define NAMING _ADD_UNDERSCORE
#endif

#ifdef UPPER_CASE
#define NAMING _UPPER_CASE
#endif

#ifndef NAMING
#define NAMING _NO_CHANGE
#endif

#if (NAMING == _ADD_UNDERSCORE)
#define c_dd_add         c_dd_add_
#define c_dd_add_dd_d    c_dd_add_dd_d_
#define c_dd_add_d_dd    c_dd_add_d_dd_

#define c_dd_sub         c_dd_sub_
#define c_dd_sub_dd_d    c_dd_sub_dd_d_
#define c_dd_sub_d_dd    c_dd_sub_d_dd_

#define c_dd_mul         c_dd_mul_
#define c_dd_mul_dd_d    c_dd_mul_dd_d_
#define c_dd_mul_d_dd    c_dd_mul_d_dd_

#define c_dd_div         c_dd_div_
#define c_dd_div_dd_d    c_dd_div_dd_d_
#define c_dd_div_d_dd    c_dd_div_d_dd_

#define c_dd_copy        c_dd_copy_
#define c_dd_copy_d      c_dd_copy_d_

#define c_dd_sqrt        c_dd_sqrt_
#define c_dd_sqr         c_dd_sqr_

#define c_dd_abs         c_dd_abs_

#define c_dd_npwr        c_dd_npwr_
#define c_dd_nroot       c_dd_nroot_

#define c_dd_nint        c_dd_nint_
#define c_dd_aint        c_dd_aint_
#define c_dd_floor       c_dd_floor_
#define c_dd_ceil        c_dd_ceil_

#define c_dd_exp         c_dd_exp_
#define c_dd_log         c_dd_log_
#define c_dd_log10       c_dd_log10_

#define c_dd_sin         c_dd_sin_
#define c_dd_cos         c_dd_cos_
#define c_dd_tan         c_dd_tan_

#define c_dd_asin        c_dd_asin_
#define c_dd_acos        c_dd_acos_
#define c_dd_atan        c_dd_atan_
#define c_dd_atan2       c_dd_atan2_

#define c_dd_sinh        c_dd_sinh_
#define c_dd_cosh        c_dd_cosh_
#define c_dd_tanh        c_dd_tanh_

#define c_dd_asinh       c_dd_asinh_
#define c_dd_acosh       c_dd_acosh_
#define c_dd_atanh       c_dd_atanh_

#define c_dd_sincos      c_dd_sincos_
#define c_dd_sincosh     c_dd_sincosh_

#define c_dd_read        c_dd_read_
#define c_dd_swrite      c_dd_swrite_
#define c_dd_write       c_dd_write_

#define c_dd_neg         c_dd_neg_
#define c_dd_rand        c_dd_rand_
#define c_dd_comp        c_dd_comp_
#define c_dd_comp_dd_d   c_dd_comp_dd_d_
#define c_dd_comp_d_dd   c_dd_comp_d_dd_
#define c_dd_polyeval    c_dd_polyeval_
#define c_dd_polyroot    c_dd_polyroot_
#define c_dd_pi          c_dd_pi_

#endif
#if (NAMING == _UPPER_CASE)

#define c_dd_add         C_DD_ADD
#define c_dd_add_dd_d    C_DD_ADD_DD_D
#define c_dd_add_d_dd    C_DD_ADD_D_DD

#define c_dd_sub         C_DD_SUB
#define c_dd_sub_dd_d    C_DD_SUB_DD_D
#define c_dd_sub_d_dd    C_DD_SUB_D_DD

#define c_dd_mul         C_DD_MUL
#define c_dd_mul_dd_d    C_DD_MUL_DD_D
#define c_dd_mul_d_dd    C_DD_MUL_D_DD

#define c_dd_div         C_DD_DIV
#define c_dd_div_dd_d    C_DD_DIV_DD_D
#define c_dd_div_d_dd    C_DD_DIV_D_DD

#define c_dd_copy        C_DD_COPY
#define c_dd_copy_d      C_DD_COPY_D

#define c_dd_sqrt        C_DD_SQRT
#define c_dd_sqr         C_DD_SQR

#define c_dd_abs         C_DD_ABS

#define c_dd_npwr        C_DD_NPWR
#define c_dd_nroot       C_DD_NROOT

#define c_dd_nint        C_DD_NINT
#define c_dd_aint        C_DD_AINT
#define c_dd_floor       C_DD_FLOOR
#define c_dd_ceil        C_DD_CEIL

#define c_dd_exp         C_DD_EXP
#define c_dd_log         C_DD_LOG
#define c_dd_log10       C_DD_LOG10

#define c_dd_sin         C_DD_SIN
#define c_dd_cos         C_DD_COS
#define c_dd_tan         C_DD_TAN

#define c_dd_asin        C_DD_ASIN
#define c_dd_acos        C_DD_ACOS
#define c_dd_atan        C_DD_ATAN
#define c_dd_atan2       C_DD_ATAN2

#define c_dd_sinh        C_DD_SINH
#define c_dd_cosh        C_DD_COSH
#define c_dd_tanh        C_DD_TANH

#define c_dd_asinh       C_DD_ASINH
#define c_dd_acosh       C_DD_ACOSH
#define c_dd_atanh       C_DD_ATANH

#define c_dd_sincos      C_DD_SINCOS
#define c_dd_sincosh     C_DD_SINCOSH

#define c_dd_read        C_DD_READ
#define c_dd_swrite      C_DD_SWRITE
#define c_dd_write       C_DD_WRITE

#define c_dd_neg         C_DD_NEG
#define c_dd_rand        C_DD_RAND
#define c_dd_comp        C_DD_COMP
#define c_dd_comp_dd_d   C_DD_COMP_DD_D
#define c_dd_comp_d_dd   C_DD_COMP_D_DD
#define c_dd_polyeval    C_DD_POLYEVAL
#define c_dd_polyroot    C_DD_POLYROOT
#define c_dd_pi          C_DD_PI

#endif

extern "C" {

/* add */
void c_dd_add(const dd_real &a, const dd_real &b, dd_real &c);
void c_dd_add_d_dd(const double &a, const dd_real &b, dd_real &c);
void c_dd_add_dd_d(const dd_real &a, const double &b, dd_real &c);

/* sub */
void c_dd_sub(const dd_real &a, const dd_real &b, dd_real &c);
void c_dd_sub_d_dd(const double &a, const dd_real &b, dd_real &c);
void c_dd_sub_dd_d(const dd_real &a, const double &b, dd_real &c);

/* mul */
void c_dd_mul(const dd_real &a, const dd_real &b, dd_real &c);
void c_dd_mul_d_dd(const double &a, const dd_real &b, dd_real &c);
void c_dd_mul_dd_d(const dd_real &a, const double &b, dd_real &c);

/* div */
void c_dd_div(const dd_real &a, const dd_real &b, dd_real &c);
void c_dd_div_d_dd(const double &a, const dd_real &b, dd_real &c);
void c_dd_div_dd_d(const dd_real &a, const double &b, dd_real &c);

/* copy */
void c_dd_copy(const dd_real &a, dd_real &b);
void c_dd_copy_d(const double &a, dd_real &b);

void c_dd_sqrt(const dd_real &a, dd_real &b);
void c_dd_sqr(const dd_real &a, dd_real &b);

void c_dd_abs(const dd_real &a, dd_real &b);

void c_dd_npwr_dd_i(const dd_real &a, const int &b, dd_real &c);
void c_dd_nroot_dd_i(const dd_real &a, const int &b, dd_real &c);

void c_dd_nint(const dd_real &a, dd_real &b);
void c_dd_aint(const dd_real &a, dd_real &b);
void c_dd_floor(const dd_real &a, dd_real &b);
void c_dd_ceil(const dd_real &a, dd_real &b);

void c_dd_exp(const dd_real &a, dd_real &b);
void c_dd_log(const dd_real &a, dd_real &b);
void c_dd_log10(const dd_real &a, dd_real &b);

void c_dd_sin(const dd_real &a, dd_real &b);
void c_dd_cos(const dd_real &a, dd_real &b);
void c_dd_tan(const dd_real &a, dd_real &b);

void c_dd_asin(const dd_real &a, dd_real &b);
void c_dd_acos(const dd_real &a, dd_real &b);
void c_dd_atan(const dd_real &a, dd_real &b);
void c_dd_atan2(const dd_real &a, const dd_real &b, dd_real &c);

void c_dd_sinh(const dd_real &a, dd_real &b);
void c_dd_cosh(const dd_real &a, dd_real &b);
void c_dd_tanh(const dd_real &a, dd_real &b);

void c_dd_asinh(const dd_real &a, dd_real &b);
void c_dd_acosh(const dd_real &a, dd_real &b);
void c_dd_atanh(const dd_real &a, dd_real &b);

void c_dd_sincos(const dd_real &a, dd_real &s, dd_real &c);
void c_dd_sincosh(const dd_real &a, dd_real &s, dd_real &c);

#ifdef CRAY_STRINGS
void c_dd_read(_fcd s, dd_real &dd);
#else
void c_dd_read(const char *s, dd_real &dd, int slen = 64);
#endif

void c_dd_swrite(const dd_real &dd, char *s);
void c_dd_write(const dd_real &dd);
void c_dd_neg(const dd_real &a, dd_real &b);
void c_dd_rand(dd_real &a);
void c_dd_comp(const dd_real &a, const dd_real &b, int &result);
void c_dd_comp_dd_d(const dd_real &a, const double &b, int &result);
void c_dd_comp_d_dd(const double &a, const dd_real &b, int &result);
void c_dd_polyeval(const dd_real *c, const int &n, 
	const dd_real &x, dd_real &result);
void c_dd_polyroot(const dd_real *c, const int &n, 
	const dd_real &x0, dd_real &r);
void c_dd_pi(dd_real &a);

}

#endif  /* _C_DD_H_ */
