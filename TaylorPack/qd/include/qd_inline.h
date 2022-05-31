/*
 * include/qd_inline.h
 *
 * This work was supported by the Director, Office of Science, Division
 * of Mathematical, Information, and Computational Sciences of the
 * U.S. Department of Energy under contract number DE-AC03-76SF00098.
 *
 * Copyright (c) 2000-2001
 *
 * Contains small functions (suitable for inlining) in the quad-double
 * arithmetic package.
 */
#ifndef _QD_INLINE_H_
#define _QD_INLINE_H_

#include <cmath>
#include "bits.h"
#include "inline.h"

#ifdef NO_INLINE
#define inline
#endif

/********** Constructors **********/
inline qd_real::qd_real(double x0, double x1, double x2, double x3) {
  x[0] = x0;
  x[1] = x1;
  x[2] = x2;
  x[3] = x3;
}

inline qd_real::qd_real(double x0) {
  x[0] = x0;
  x[1] = x[2] = x[3] = 0.0;
}

inline qd_real::qd_real(const dd_real &a) {
  x[0] = a._hi();
  x[1] = a._lo();
  x[2] = x[3] = 0.0;
}

inline qd_real::qd_real(int i) {
  x[0] = (double) i;
  x[1] = x[2] = x[3] = 0.0;
}

/********** Accessors **********/
inline double qd_real::operator[](int i) const {
  return x[i];
}

/********** Renormalization **********/
inline void quick_renorm(double &c0, double &c1, 
			 double &c2, double &c3, double &c4) {
  double t0, t1, t2, t3;
  double s;
  s  = quick_two_sum(c3, c4, t3);
  s  = quick_two_sum(c2, s , t2);
  s  = quick_two_sum(c1, s , t1);
  c0 = quick_two_sum(c0, s , t0);

  s  = quick_two_sum(t2, t3, t2);
  s  = quick_two_sum(t1, s , t1);
  c1 = quick_two_sum(t0, s , t0);

  s  = quick_two_sum(t1, t2, t1);
  c2 = quick_two_sum(t0, s , t0);
  
  c3 = t0 + t1;
}

inline void renorm(double &c0, double &c1, 
		   double &c2, double &c3) {
  double s0, s1, s2 = 0.0, s3 = 0.0;

  s0 = quick_two_sum(c2, c3, c3);
  s0 = quick_two_sum(c1, s0, c2);
  c0 = quick_two_sum(c0, s0, c1);

  s0 = c0;
  s1 = c1;
  if (s1 != 0.0) {
    s1 = quick_two_sum(s1, c2, s2);
    if (s2 != 0.0)
      s2 = quick_two_sum(s2, c3, s3);
    else
      s1 = quick_two_sum(s1, c3, s2);
  } else {
    s0 = quick_two_sum(s0, c2, s1);
    if (s1 != 0.0)
      s1 = quick_two_sum(s1, c3, s2);
    else
      s0 = quick_two_sum(s0, c3, s1);
  }

  c0 = s0;
  c1 = s1;
  c2 = s2;
  c3 = s3;
}

inline void renorm(double &c0, double &c1, 
		   double &c2, double &c3, double &c4) {
  double s0, s1, s2 = 0.0, s3 = 0.0;

  s0 = quick_two_sum(c3, c4, c4);
  s0 = quick_two_sum(c2, s0, c3);
  s0 = quick_two_sum(c1, s0, c2);
  c0 = quick_two_sum(c0, s0, c1);

  s0 = c0;
  s1 = c1;

  s0 = quick_two_sum(c0, c1, s1);
  if (s1 != 0.0) {
    s1 = quick_two_sum(s1, c2, s2);
    if (s2 != 0.0) {
      s2 = quick_two_sum(s2, c3, s3);
      if (s3 != 0.0)
	s3 += c4;
      else
	s2 += c4;
    } else {
      s1 = quick_two_sum(s1, c3, s2);
      if (s2 != 0.0)
	s2 = quick_two_sum(s2, c4, s3);
      else
	s1 = quick_two_sum(s1, c4, s2);
    }
  } else {
    s0 = quick_two_sum(s0, c2, s1);
    if (s1 != 0.0) {
      s1 = quick_two_sum(s1, c3, s2);
      if (s2 != 0.0)
	s2 = quick_two_sum(s2, c4, s3);
      else
	s1 = quick_two_sum(s1, c4, s2);
    } else {
      s0 = quick_two_sum(s0, c3, s1);
      if (s1 != 0.0)
	s1 = quick_two_sum(s1, c4, s2);
      else
	s0 = quick_two_sum(s0, c4, s1);
    }
  }

  c0 = s0;
  c1 = s1;
  c2 = s2;
  c3 = s3;
}

/********** Additions ************/
inline void three_sum(double &a, double &b, double &c) {
  double t1, t2, t3;
  t1 = two_sum(a, b, t2);
  a  = two_sum(c, t1, t3);
  b  = two_sum(t2, t3, c);
}

inline void three_sum2(double &a, double &b, double &c) {
  double t1, t2, t3;
  t1 = two_sum(a, b, t2);
  a  = two_sum(c, t1, t3);
  b = t2 + t3;
}

/* quad-double + double */
inline qd_real operator+(const qd_real &a, double b) {
  double c0, c1, c2, c3;
  double e;

  c0 = two_sum(a[0], b, e);
  c1 = two_sum(a[1], e, e);
  c2 = two_sum(a[2], e, e);
  c3 = two_sum(a[3], e, e);

  renorm(c0, c1, c2, c3, e);

  return qd_real(c0, c1, c2, c3);
}

/* quad-double + double-double */
inline qd_real operator+(const qd_real &a, const dd_real &b) {

  double s0, s1, s2, s3;
  double t0, t1;

  s0 = two_sum(a[0], b._hi(), t0);
  s1 = two_sum(a[1], b._lo(), t1);

  s1 = two_sum(s1, t0, t0);

  s2 = a[2];
  three_sum(s2, t0, t1);

  s3 = two_sum(t0, a[3], t0);
  t0 += t1;

  renorm(s0, s1, s2, s3, t0);
  return qd_real(s0, s1, s2, s3);
}


/* double + quad-double */
inline qd_real operator+(double a, const qd_real &b) {
  return (b + a);
}

/* double-double + quad-double */
inline qd_real operator+(const dd_real &a, const qd_real &b) {
  return (b + a);
}

inline double quick_three_accum(double &a, double &b, double c) {
  double s;
  bool za, zb;

  s = two_sum(b, c, b);
  s = two_sum(a, s, a);

  za = (a != 0.0);
  zb = (b != 0.0);

  if (za && zb)
    return s;

  if (!za) {
    a = s;
    s = 0.0;
  }
  if (!zb) {
    b = a;
    a = s;
  }    

  return 0.0;
}

/* quad-double + quad-double */
inline qd_real operator+(const qd_real &a, const qd_real &b) {
#ifndef ACCURATE
  /*
  double s0, s1, s2, s3;
  double t0, t1, t2, t3;
  
  s0 = two_sum(a[0], b[0], t0);
  s1 = two_sum(a[1], b[1], t1);
  s2 = two_sum(a[2], b[2], t2);
  s3 = two_sum(a[3], b[3], t3);

  s1 = two_sum(s1, t0, t0);
  three_sum(s2, t0, t1);
  three_sum2(s3, t0, t2);
  t0 = t0 + t1 + t3;

  renorm(s0, s1, s2, s3, t0);
  return qd_real(s0, s1, s2, s3, t0);
  */

  /* Same as above, but addition re-organized to minimize
     data dependency ... unfortunately some compilers are
     not very smart to do this automatically */
  double s0, s1, s2, s3;
  double t0, t1, t2, t3;

  double v0, v1, v2, v3;
  double u0, u1, u2, u3;
  double w0, w1, w2, w3;

  s0 = a[0] + b[0];
  s1 = a[1] + b[1];
  s2 = a[2] + b[2];
  s3 = a[3] + b[3];

  v0 = s0 - a[0];
  v1 = s1 - a[1];
  v2 = s2 - a[2];
  v3 = s3 - a[3];

  u0 = s0 - v0;
  u1 = s1 - v1;
  u2 = s2 - v2;
  u3 = s3 - v3;

  w0 = a[0] - u0;
  w1 = a[1] - u1;
  w2 = a[2] - u2;
  w3 = a[3] - u3;

  u0 = b[0] - v0;
  u1 = b[1] - v1;
  u2 = b[2] - v2;
  u3 = b[3] - v3;

  t0 = w0 + u0;
  t1 = w1 + u1;
  t2 = w2 + u2;
  t3 = w3 + u3;

  s1 = two_sum(s1, t0, t0);
  three_sum(s2, t0, t1);
  three_sum2(s3, t0, t2);
  t0 = t0 + t1 + t3;

  /* renormalize */
  renorm(s0, s1, s2, s3, t0);
  return qd_real(s0, s1, s2, s3);

#else
  int i, j, k;
  double s, t;
  double u, v;   /* double-length accumulator */
  double x[4] = {0.0, 0.0, 0.0, 0.0};
  
  i = j = k = 0;
  if (fabs(a[i]) > fabs(b[j]))
    u = a[i++];
  else
    u = b[j++];
  if (fabs(a[i]) > fabs(b[j]))
    v = a[i++];
  else
    v = b[j++];

  u = quick_two_sum(u, v, v);
  
  while (k < 4) {
    if (i >= 4 && j >= 4) {
      x[k] = u;
      if (k < 3)
	x[++k] = v;
      break;
    }

    if (i >= 4)
      t = b[j++];
    else if (j >= 4)
      t = a[i++];
    else if (fabs(a[i]) > fabs(b[j])) {
      t = a[i++];
    } else
      t = b[j++];

    s = quick_three_accum(u, v, t);

    if (s != 0.0) {
      x[k++] = s;
    }
  }

  /* add the rest. */
  for (k = i; k < 4; k++)
    x[3] += a[k];
  for (k = j; k < 4; k++)
    x[3] += b[k];

  renorm(x[0], x[1], x[2], x[3]);
  return qd_real(x[0], x[1], x[2], x[3]);
#endif
}



/********** Self-Additions ************/
/* quad-double += double */
inline qd_real &qd_real::operator+=(double a) {
  *this = *this + a;
  return *this;
}

/* quad-double += double-double */
inline qd_real &qd_real::operator+=(const dd_real &a) {
  *this = *this + a;
  return *this;
}

/* quad-double += quad-double */
inline qd_real &qd_real::operator+=(const qd_real &a) {
  *this = *this + a;
  return *this;
}

/********** Unary Minus **********/
inline qd_real qd_real::operator-() const {
  return qd_real(-x[0], -x[1], -x[2], -x[3]);
}

/********** Subtractions **********/
inline qd_real operator-(const qd_real &a, double b) {
  return (a + (-b));
}

inline qd_real operator-(double a, const qd_real &b) {
  return (a + (-b));
}

inline qd_real operator-(const qd_real &a, const dd_real &b) {
  return (a + (-b));
}

inline qd_real operator-(const dd_real &a, const qd_real &b) {
  return (a + (-b));
}

inline qd_real operator-(const qd_real &a, const qd_real &b) {
  return (a + (-b));
}

/********** Self-Subtractions **********/
inline qd_real &qd_real::operator-=(double a) {
  return ((*this) += (-a));
}

inline qd_real &qd_real::operator-=(const dd_real &a) {
  return ((*this) += (-a));
}

inline qd_real &qd_real::operator-=(const qd_real &a) {
  return ((*this) += (-a));
}


inline qd_real operator*(double a, const qd_real &b) {
  return (b * a);
}

inline qd_real operator*(const dd_real &a, const qd_real &b) {
  return (b * a);
}

inline qd_real mul_pwr2(const qd_real &a, double b) {
  return qd_real(a[0] * b, a[1] * b, a[2] * b, a[3] * b);
}

/********** Multiplications **********/
inline qd_real operator*(const qd_real &a, double b) {
  double p0, p1, p2, p3;
  double q0, q1, q2;
  double s0, s1, s2, s3, s4;

  p0 = two_prod(a[0], b, q0);
  p1 = two_prod(a[1], b, q1);
  p2 = two_prod(a[2], b, q2);
  p3 = a[3] * b;

  s0 = p0;

  s1 = two_sum(q0, p1, s2);

  three_sum(s2, q1, p2);

  three_sum2(q1, q2, p3);
  s3 = q1;

  s4 = q2 + p2;

  renorm(s0, s1, s2, s3, s4);
  return qd_real(s0, s1, s2, s3);

}

/* quad-double * double-double */
/* a0 * b0                        0
        a0 * b1                   1
        a1 * b0                   2
             a1 * b1              3
             a2 * b0              4
                  a2 * b1         5
                  a3 * b0         6
	               a3 * b1    7 */
inline qd_real operator*(const qd_real &a, const dd_real &b) {
  double p0, p1, p2, p3, p4;
  double q0, q1, q2, q3, q4;
  double s0, s1, s2;
  double t0, t1;

  p0 = two_prod(a[0], b._hi(), q0);
  p1 = two_prod(a[0], b._lo(), q1);
  p2 = two_prod(a[1], b._hi(), q2);
  p3 = two_prod(a[1], b._lo(), q3);
  p4 = two_prod(a[2], b._hi(), q4);
  
  three_sum(p1, p2, q0);
  
  /* Five-Three-Sum */
  three_sum(p2, p3, p4);
  q1 = two_sum(q1, q2, q2);
  s0 = two_sum(p2, q1, t0);
  s1 = two_sum(p3, q2, t1);
  s1 = two_sum(s1, t0, t0);
  s2 = t0 + t1 + p4;
  p2 = s0;

  p3 = a[2] * b._hi() + a[3] * b._lo() + q3 + q4;
  three_sum2(p3, q0, s1);
  p4 = q0 + s2;

  renorm(p0, p1, p2, p3, p4);
  return qd_real(q0, q1, q2, q3);
}

/* quad-double * quad-double */
/* a0 * b0                    0
        a0 * b1               1
        a1 * b0               2
             a0 * b2          3
             a1 * b1          4
             a2 * b0          5
                  a0 * b3     6
                  a1 * b2     7
                  a2 * b1     8
                  a3 * b0     9  */
inline qd_real operator*(const qd_real &a, const qd_real &b) {
  double p0, p1, p2, p3, p4, p5;
  double q0, q1, q2, q3, q4, q5;
#ifndef SLOPPY
  double p6, p7, p8, p9;
  double q6, q7, q8, q9;
  double r0, r1;
#endif
  double t0, t1;
  double s0, s1, s2;

  p0 = two_prod(a[0], b[0], q0);

  p1 = two_prod(a[0], b[1], q1);
  p2 = two_prod(a[1], b[0], q2);

  p3 = two_prod(a[0], b[2], q3);
  p4 = two_prod(a[1], b[1], q4);
  p5 = two_prod(a[2], b[0], q5);

  /* Start Accumulation */

  three_sum(p1, p2, q0);

  /* Six-Three Sum  of p2, q1, q2, p3, p4, p5. */
  three_sum(p2, q1, q2);
  three_sum(p3, p4, p5);
  /* compute (s0, s1, s2) = (p2, q1, q2) + (p3, p4, p5). */
  s0 = two_sum(p2, p3, t0);
  s1 = two_sum(q1, p4, t1);
  s2 = q2 + p5;
  s1 = two_sum(s1, t0, t0);
  s2 += (t0 + t1);

  /* O(eps^3) order terms */
#ifdef SLOPPY
  s1 += a[0]*b[3] + a[1]*b[2] + a[2]*b[1] + a[3]*b[0] + q0 + q3 + q4 + q5;
  renorm(p0, p1, s0, s1, s2);
  return qd_real(p0, p1, s0, s1);
#else
  p6 = two_prod(a[0], b[3], q6);
  p7 = two_prod(a[1], b[2], q7);
  p8 = two_prod(a[2], b[1], q8);
  p9 = two_prod(a[3], b[0], q9);

  /* Nine-Two-Sum of q0, s1, q3, q4, q5, p6, p7, p8, p9. */
  q0 = two_sum(q0, q3, q3);
  q4 = two_sum(q4, q5, q5);
  p6 = two_sum(p6, p7, p7);
  p8 = two_sum(p8, p9, p9);
  /* Compute (t0, t1) = (q0, q3) + (q4, q5). */
  t0 = two_sum(q0, q4, t1);
  t1 += (q3 + q5);
  /* Compute (r0, r1) = (p6, p7) + (p8, p9). */
  r0 = two_sum(p6, p8, r1);
  r1 += (p7 + p9);
  /* Compute (q3, q4) = (t0, t1) + (r0, r1). */
  q3 = two_sum(t0, r0, q4);
  q4 += (t1 + r1);
  /* Compute (t0, t1) = (q3, q4) + s1. */
  t0 = two_sum(q3, s1, t1);
  t1 += q4;

  /* O(eps^4) terms -- Nine-One-Sum */
  t1 += a[1] * b[3] + a[2] * b[2] + a[3] * b[1] + q6 + q7 + q8 + q9 + s2;

  renorm(p0, p1, s0, t0, t1);
  return qd_real(p0, p1, s0, t0);
#endif
}

/* quad-double ^ 2  = (x0 + x1 + x2 + x3) ^ 2
                    = x0 ^ 2 + 2 x0 * x1 + (2 x0 * x2 + x1 ^ 2)
  	                     + (2 x0 * x3 + 2 x1 * x2)           */
inline qd_real sqr(const qd_real &a) {
  double p0, p1, p2, p3, p4, p5;
  double q0, q1, q2, q3;
  double s0, s1;
  double t0, t1;
  
  p0 = two_sqr(a[0], q0);
  p1 = two_prod(2.0 * a[0], a[1], q1);
  p2 = two_prod(2.0 * a[0], a[2], q2);
  p3 = two_sqr(a[1], q3);

  p1 = two_sum(q0, p1, q0);

  q0 = two_sum(q0, q1, q1);
  p2 = two_sum(p2, p3, p3);

  s0 = two_sum(q0, p2, t0);
  s1 = two_sum(q1, p3, t1);

  s1 = two_sum(s1, t0, t0);
  t0 += t1;

  s1 = quick_two_sum(s1, t0, t0);
  p2 = quick_two_sum(s0, s1, t1);
  p3 = quick_two_sum(t1, t0, q0);

  p4 = 2.0 * a[0] * a[3];
  p5 = 2.0 * a[1] * a[2];

  p4 = two_sum(p4, p5, p5);
  q2 = two_sum(q2, q3, q3);

  t0 = two_sum(p4, q2, t1);
  t1 = t1 + p5 + q3;

  p3 = two_sum(p3, t0, p4);
  p4 = p4 + q0 + t1;

  renorm(p0, p1, p2, p3, p4);
  return qd_real(p0, p1, p2, p3);

}

/********** Self-Multiplication **********/
/* quad-double *= double */
inline qd_real &qd_real::operator*=(double a) {
  *this = (*this * a);
  return *this;
}

/* quad-double *= double-double */
inline qd_real &qd_real::operator*=(const dd_real &a) {
  *this = (*this * a);
  return *this;
}

/* quad-double *= quad-double */
inline qd_real &qd_real::operator*=(const qd_real &a) {
  *this = *this * a;
  return *this;
}

/* double / quad-double */
inline qd_real operator/(double a, const qd_real &b) {
  return qd_real(a) / b;
}

/* double-double / quad-double */
inline qd_real operator/(const dd_real &a, const qd_real &b) {
  return qd_real(a) / b;
}

/********** Self-Divisions **********/
/* quad-double /= double */
inline qd_real &qd_real::operator/=(double a) {
  *this = (*this / a);
  return *this;
}

/* quad-double /= double-double */
inline qd_real &qd_real::operator/=(const dd_real &a) {
  *this = (*this / a);
  return *this;
}

/* quad-double /= quad-double */
inline qd_real &qd_real::operator/=(const qd_real &a) {
  *this = (*this / a);
  return *this;
}


/********** Exponentiation **********/
inline qd_real qd_real::operator^(int n) const {
  return pow(*this, n);
}

/********** Miscellaneous **********/
inline qd_real fabs(const qd_real &a) {
  return (a[0] < 0.0) ? -a : a;
}

inline qd_real abs(const qd_real &a) {
  return fabs(a);
}

/* Quick version.  May be off by one when qd is very close
   to the middle of two integers.                         */
inline qd_real quick_nint(const qd_real &a) {
  qd_real r = qd_real(nint(a[0]), nint(a[1]), 
		      nint(a[2]), nint(a[3]));
  r.renorm();
  return r;
}

/********** Equality Comparison **********/
inline bool operator==(const qd_real &a, double b) {
  return (a[0] == b && a[1] == 0.0 && a[2] == 0.0 && a[3] == 0.0);
}

inline bool operator==(double a, const qd_real &b) {
  return (b == a);
}

inline bool operator==(const qd_real &a, const dd_real &b) {
  return (a[0] == b._hi() && a[1] == b._lo() && 
	  a[2] == 0.0 && a[3] == 0.0);
}

inline bool operator==(const dd_real &a, const qd_real &b) {
  return (b == a);
}

inline bool operator==(const qd_real &a, const qd_real &b) {
  return (a[0] == b[0] && a[1] == b[1] && 
	  a[2] == b[2] && a[3] == b[3]);
}


/********** Less-Than Comparison ***********/
inline bool operator<(const qd_real &a, double b) {
  return (a[0] < b || (a[0] == b && a[1] < 0.0));
}

inline bool operator<(double a, const qd_real &b) {
  return (b > a);
}

inline bool operator<(const qd_real &a, const dd_real &b) {
  return (a[0] < b._hi() || 
	  (a[0] == b._hi() && (a[1] < b._lo() ||
			    (a[1] == b._lo() && a[2] < 0.0))));
}

inline bool operator<(const dd_real &a, const qd_real &b) {
  return (b > a);
}

inline bool operator<(const qd_real &a, const qd_real &b) {
  return (a[0] < b[0] ||
	  (a[0] == b[0] && (a[1] < b[1] ||
			    (a[1] == b[1] && (a[2] < b[2] ||
					      (a[2] == b[2] && a[3] < b[3]))))));
}

/********** Greater-Than Comparison ***********/
inline bool operator>(const qd_real &a, double b) {
  return (a[0] > b || (a[0] == b && a[1] > 0.0));
}

inline bool operator>(double a, const qd_real &b) {
  return (b < a);
}

inline bool operator>(const qd_real &a, const dd_real &b) {
  return (a[0] > b._hi() || 
	  (a[0] == b._hi() && (a[1] > b._lo() ||
			    (a[1] == b._lo() && a[2] > 0.0))));
}

inline bool operator>(const dd_real &a, const qd_real &b) {
  return (b < a);
}

inline bool operator>(const qd_real &a, const qd_real &b) {
  return (a[0] > b[0] ||
	  (a[0] == b[0] && (a[1] > b[1] ||
			    (a[1] == b[1] && (a[2] > b[2] ||
					      (a[2] == b[2] && a[3] > b[3]))))));
}


/********** Less-Than-Or-Equal-To Comparison **********/
inline bool operator<=(const qd_real &a, double b) {
  return (a[0] < b || (a[0] == b && a[1] <= 0.0));
}

inline bool operator<=(double a, const qd_real &b) {
  return (b >= a);
}

inline bool operator<=(const qd_real &a, const dd_real &b) {
  return (a[0] < b._hi() || 
	  (a[0] == b._hi() && (a[1] < b._lo() || 
			    (a[1] == b._lo() && a[2] <= 0.0))));
}

inline bool operator<=(const dd_real &a, const qd_real &b) {
  return (b >= a);
}

inline bool operator<=(const qd_real &a, const qd_real &b) {
  return (a[0] < b[0] || 
	  (a[0] == b[0] && (a[1] < b[1] ||
			    (a[1] == b[1] && (a[2] < b[2] ||
					      (a[2] == b[2] && a[3] <= b[3]))))));
}

/********** Greater-Than-Or-Equal-To Comparison **********/
inline bool operator>=(const qd_real &a, double b) {
  return (a[0] > b || (a[0] == b && a[1] >= 0.0));
}

inline bool operator>=(double a, const qd_real &b) {
  return (b <= a);
}

inline bool operator>=(const qd_real &a, const dd_real &b) {
  return (a[0] > b._hi() || 
	  (a[0] == b._hi() && (a[1] > b._lo() || 
			    (a[1] == b._lo() && a[2] >= 0.0))));
}

inline bool operator>=(const dd_real &a, const qd_real &b) {
  return (b <= a);
}

inline bool operator>=(const qd_real &a, const qd_real &b) {
  return (a[0] > b[0] || 
	  (a[0] == b[0] && (a[1] > b[1] ||
			    (a[1] == b[1] && (a[2] > b[2] ||
					      (a[2] == b[2] && a[3] >= b[3]))))));
}



/********** Not-Equal-To Comparison **********/
inline bool operator!=(const qd_real &a, double b) {
  return !(a == b);
}

inline bool operator!=(double a, const qd_real &b) {
  return !(a == b);
}

inline bool operator!=(const qd_real &a, const dd_real &b) {
  return !(a == b);
}

inline bool operator!=(const dd_real &a, const qd_real &b) {
  return !(a == b);
}

inline bool operator!=(const qd_real &a, const qd_real &b) {
  return !(a == b);
}



inline qd_real aint(const qd_real &a) {
  return (a[0] >= 0) ? floor(a) : ceil(a);
}

inline bool qd_real::is_zero() const {
  return (x[0] == 0.0);
}

inline bool qd_real::is_one() const {
  return (x[0] == 1.0 && x[1] == 0.0 && x[2] == 0.0 && x[3] == 0.0);
}

inline bool qd_real::is_positive() const {
  return (x[0] > 0.0);
}

inline bool qd_real::is_negative() const {
  return (x[0] < 0.0);
}

inline qd_real::operator dd_real() const {
  return dd_real(x[0], x[1]);
}

inline qd_real::operator double() const {
  return x[0];
}

inline qd_real::operator int() const {
  return (int) x[0];
}

inline qd_real inv(const qd_real &qd) {
  return 1.0 / qd;
}

inline qd_real max(const qd_real &a, const qd_real &b) {
  return (a > b) ? a : b;
}

inline qd_real max(const qd_real &a, const qd_real &b, 
		   const qd_real &c) {
  return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

inline qd_real min(const qd_real &a, const qd_real &b) {
  return (a < b) ? a : b;
}

inline qd_real min(const qd_real &a, const qd_real &b, 
		   const qd_real &c) {
  return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

/* Random number generator */
inline qd_real qd_real::rand() {
  return qdrand();
}

inline qd_real ldexp(const qd_real &a, int n) {
  return qd_real(ldexp(a[0], n), ldexp(a[1], n), 
		 ldexp(a[2], n), ldexp(a[3], n));
}

#endif /* _QD_INLINE_H_ */
