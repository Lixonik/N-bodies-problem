/*
 * include/c_qd.h
 *
 * This work was supported by the Director, Office of Science, Division
 * of Mathematical, Information, and Computational Sciences of the
 * U.S. Department of Energy under contract number DE-AC03-76SF00098.
 *
 * Copyright (c) 2000-2001
 *
 * Contains C wrapper function prototypes for quad-double precision 
 * arithmetic.  This can also be used from fortran code.
 */
#ifndef _C_QD_H_
#define _C_QD_H_

#include "qd.h"
#include "c_dd.h"

#if (NAMING == _ADD_UNDERSCORE)
#define c_qd_add         c_qd_add_
#define c_qd_add_dd_qd   c_qd_add_dd_qd_
#define c_qd_add_qd_dd   c_qd_add_qd_dd_
#define c_qd_add_d_qd    c_qd_add_d_qd_
#define c_qd_add_qd_d    c_qd_add_qd_d_

#define c_qd_sub         c_qd_sub_
#define c_qd_sub_dd_qd   c_qd_sub_dd_qd_
#define c_qd_sub_qd_dd   c_qd_sub_qd_dd_
#define c_qd_sub_d_qd    c_qd_sub_d_qd_
#define c_qd_sub_qd_d    c_qd_sub_qd_d_

#define c_qd_mul         c_qd_mul_
#define c_qd_mul_dd_qd   c_qd_mul_dd_qd_
#define c_qd_mul_qd_dd   c_qd_mul_qd_dd_
#define c_qd_mul_d_qd    c_qd_mul_d_qd_
#define c_qd_mul_qd_d    c_qd_mul_qd_d_

#define c_qd_div         c_qd_div_
#define c_qd_div_dd_qd   c_qd_div_dd_qd_
#define c_qd_div_qd_dd   c_qd_div_qd_dd_
#define c_qd_div_d_qd    c_qd_div_d_qd_
#define c_qd_div_qd_d    c_qd_div_qd_d_

#define c_qd_copy        c_qd_copy_
#define c_qd_copy_dd     c_qd_copy_dd_
#define c_qd_copy_d      c_qd_copy_d_

#define c_qd_sqrt        c_qd_sqrt_
#define c_qd_sqr         c_qd_sqr_

#define c_qd_abs         c_qd_abs_

#define c_qd_npwr        c_qd_npwr_
#define c_qd_nroot       c_qd_nroot_

#define c_qd_nint        c_qd_nint_
#define c_qd_aint        c_qd_aint_
#define c_qd_floor       c_qd_floor_
#define c_qd_ceil        c_qd_ceil_

#define c_qd_exp         c_qd_exp_
#define c_qd_log         c_qd_log_
#define c_qd_log10       c_qd_log10_

#define c_qd_sin         c_qd_sin_
#define c_qd_cos         c_qd_cos_
#define c_qd_tan         c_qd_tan_

#define c_qd_asin        c_qd_asin_
#define c_qd_acos        c_qd_acos_
#define c_qd_atan        c_qd_atan_
#define c_qd_atan2       c_qd_atan2_

#define c_qd_sinh        c_qd_sinh_
#define c_qd_cosh        c_qd_cosh_
#define c_qd_tanh        c_qd_tanh_

#define c_qd_asinh       c_qd_asinh_
#define c_qd_acosh       c_qd_acosh_
#define c_qd_atanh       c_qd_atanh_

#define c_qd_sincos      c_qd_sincos_
#define c_qd_sincosh     c_qd_sincosh_

#define c_qd_read        c_qd_read_
#define c_qd_swrite      c_qd_swrite_
#define c_qd_write       c_qd_write_

#define c_qd_neg         c_qd_neg_
#define c_qd_rand        c_qd_rand_
#define c_qd_comp        c_qd_comp_
#define c_qd_comp_qd_d   c_qd_comp_qd_d_
#define c_qd_comp_d_qd   c_qd_comp_d_qd_
#define c_qd_polyeval    c_qd_polyeval_
#define c_qd_polyroot    c_qd_polyroot_
#define c_qd_pi          c_qd_pi_

#endif
#if (NAMING == _UPPER_CASE)

#define c_qd_add         C_QD_ADD
#define c_qd_add_dd_qd   C_QD_ADD_DD_QD
#define c_qd_add_qd_dd   C_QD_ADD_QD_DD
#define c_qd_add_d_qd    C_QD_ADD_D_QD
#define c_qd_add_qd_d    C_QD_ADD_QD_D

#define c_qd_sub         C_QD_SUB
#define c_qd_sub_dd_qd   C_QD_SUB_DD_QD
#define c_qd_sub_qd_dd   C_QD_SUB_QD_DD
#define c_qd_sub_d_qd    C_QD_SUB_D_QD
#define c_qd_sub_qd_d    C_QD_SUB_QD_D

#define c_qd_mul         C_QD_MUL
#define c_qd_mul_dd_qd   C_QD_MUL_DD_QD
#define c_qd_mul_qd_dd   C_QD_MUL_QD_DD
#define c_qd_mul_d_qd    C_QD_MUL_D_QD
#define c_qd_mul_qd_d    C_QD_MUL_QD_D

#define c_qd_div         C_QD_DIV
#define c_qd_div_dd_qd   C_QD_DIV_DD_QD
#define c_qd_div_qd_dd   C_QD_DIV_QD_DD
#define c_qd_div_d_qd    C_QD_DIV_D_QD
#define c_qd_div_qd_d    C_QD_DIV_QD_D

#define c_qd_copy        C_QD_COPY
#define c_qd_copy_dd     C_QD_COPY_DD
#define c_qd_copy_d      C_QD_COPY_D

#define c_qd_sqrt        C_QD_SQRT
#define c_qd_sqr         C_QD_SQR

#define c_qd_abs         C_QD_ABS

#define c_qd_npwr        C_QD_NPWR
#define c_qd_nroot       C_QD_NROOT

#define c_qd_nint        C_QD_NINT
#define c_qd_aint        C_QD_AINT
#define c_qd_floor       C_QD_FLOOR
#define c_qd_ceil        C_QD_CEIL

#define c_qd_exp         C_QD_EXP
#define c_qd_log         C_QD_LOG
#define c_qd_log10       C_QD_LOG10

#define c_qd_sin         C_QD_SIN
#define c_qd_cos         C_QD_COS
#define c_qd_tan         C_QD_TAN

#define c_qd_asin        C_QD_ASIN
#define c_qd_acos        C_QD_ACOS
#define c_qd_atan        C_QD_ATAN
#define c_qd_atan2       C_QD_ATAN2

#define c_qd_sinh        C_QD_SINH
#define c_qd_cosh        C_QD_COSH
#define c_qd_tanh        C_QD_TANH

#define c_qd_asinh       C_QD_ASINH
#define c_qd_acosh       C_QD_ACOSH
#define c_qd_atanh       C_QD_ATANH

#define c_qd_sincos      C_QD_SINCOS
#define c_qd_sincosh     C_QD_SINCOSH

#define c_qd_read        C_QD_READ
#define c_qd_swrite      C_QD_SWRITE
#define c_qd_write       C_QD_WRITE

#define c_qd_neg         C_QD_NEG
#define c_qd_rand        C_QD_RAND
#define c_qd_comp        C_QD_COMP
#define c_qd_comp_qd_d   C_QD_COMP_QD_D
#define c_qd_comp_d_qd   C_QD_COMP_D_QD
#define c_qd_polyeval    C_QD_POLYEVAL
#define c_qd_polyroot    C_QD_POLYROOT
#define c_qd_pi          C_QD_PI

#endif

extern "C" {

/* add */
void c_qd_add(const qd_real &a, const qd_real &b, qd_real &c);
void c_qd_add_dd_qd(const dd_real &a, const qd_real &b, qd_real &c);
void c_qd_add_qd_dd(const qd_real &a, const dd_real &b, qd_real &c);
void c_qd_add_d_qd(const double &a, const qd_real &b, qd_real &c);
void c_qd_add_qd_d(const qd_real &a, const double &b, qd_real &c);

/* sub */
void c_qd_sub(const qd_real &a, const qd_real &b, qd_real &c);
void c_qd_sub_dd_qd(const dd_real &a, const qd_real &b, qd_real &c);
void c_qd_sub_qd_dd(const qd_real &a, const dd_real &b, qd_real &c);
void c_qd_sub_d_qd(const double &a, const qd_real &b, qd_real &c);
void c_qd_sub_qd_d(const qd_real &a, const double &b, qd_real &c);

/* mul */
void c_qd_mul(const qd_real &a, const qd_real &b, qd_real &c);
void c_qd_mul_dd_qd(const dd_real &a, const qd_real &b, qd_real &c);
void c_qd_mul_qd_dd(const qd_real &a, const dd_real &b, qd_real &c);
void c_qd_mul_d_qd(const double &a, const qd_real &b, qd_real &c);
void c_qd_mul_qd_d(const qd_real &a, const double &b, qd_real &c);

/* div */
void c_qd_div(const qd_real &a, const qd_real &b, qd_real &c);
void c_qd_div_dd_qd(const dd_real &a, const qd_real &b, qd_real &c);
void c_qd_div_qd_dd(const qd_real &a, const dd_real &b, qd_real &c);
void c_qd_div_d_qd(const double &a, const qd_real &b, qd_real &c);
void c_qd_div_qd_d(const qd_real &a, const double &b, qd_real &c);

/* copy */
void c_qd_copy(const qd_real &a, qd_real &b);
void c_qd_copy_dd(const dd_real &a, qd_real &b);
void c_qd_copy_d(const double &a, qd_real &b);

void c_qd_sqrt(const qd_real &a, qd_real &b);
void c_qd_sqr(const qd_real &a, qd_real &b);

void c_qd_abs(const qd_real &a, qd_real &b);

void c_qd_npwr_qd_i(const qd_real &a, const int &b, qd_real &c);
void c_qd_nroot_qd_i(const qd_real &a, const int &b, qd_real &c);

void c_qd_nint(const qd_real &a, qd_real &b);
void c_qd_aint(const qd_real &a, qd_real &b);
void c_qd_floor(const qd_real &a, qd_real &b);
void c_qd_ceil(const qd_real &a, qd_real &b);

void c_qd_exp(const qd_real &a, qd_real &b);
void c_qd_log(const qd_real &a, qd_real &b);
void c_qd_log10(const qd_real &a, qd_real &b);

void c_qd_sin(const qd_real &a, qd_real &b);
void c_qd_cos(const qd_real &a, qd_real &b);
void c_qd_tan(const qd_real &a, qd_real &b);

void c_qd_asin(const qd_real &a, qd_real &b);
void c_qd_acos(const qd_real &a, qd_real &b);
void c_qd_atan(const qd_real &a, qd_real &b);
void c_qd_atan2(const qd_real &a, const qd_real &b, qd_real &c);

void c_qd_sinh(const qd_real &a, qd_real &b);
void c_qd_cosh(const qd_real &a, qd_real &b);
void c_qd_tanh(const qd_real &a, qd_real &b);

void c_qd_asinh(const qd_real &a, qd_real &b);
void c_qd_acosh(const qd_real &a, qd_real &b);
void c_qd_atanh(const qd_real &a, qd_real &b);

void c_qd_sincos(const qd_real &a, qd_real &s, qd_real &c);
void c_qd_sincosh(const qd_real &a, qd_real &s, qd_real &c);

#ifdef CRAY_STRINGS
void c_qd_read(_fcd s, qd_real &qd);
#else
void c_qd_read(const char *s, qd_real &qd, int slen = 64);
#endif

void c_qd_swrite(const qd_real &qd, char *s);
void c_qd_write(const qd_real &qd);
void c_qd_neg(const qd_real &a, qd_real &b);
void c_qd_rand(qd_real &a);
void c_qd_comp(const qd_real &a, const qd_real &b, int &result);
void c_qd_comp_qd_d(const qd_real &a, const double &b, int &result);
void c_qd_comp_d_qd(const double &a, const qd_real &b, int &result);
void c_qd_polyeval(const qd_real *c, const int &n, 
		   const qd_real &x, qd_real &result);
void c_qd_polyroot(const qd_real *c, const int &n, 
	const qd_real &x0, qd_real &r);
void c_qd_pi(qd_real &a);

}

#endif  /* _C_QD_H_ */
