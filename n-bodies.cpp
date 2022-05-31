// Гравитационная задача N тел.
// Нужно изучать поведение инвариантов:
// импульса системы, момента импульса системы, энергии (суммы кинетической и потенциальной, по всем телам).

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include "Vec3D.h"
#include "KeplerDataBox.h"
#include <utility>

using namespace std;

void print(Vec3D *X, ofstream &file, int n)
{
    // std::cout << "Body 1: r or v - " << X[0] << "   v or a - " << X[1] << std::endl
    //           << "Body 2:  r or v - " << X[2] << "   v or a - " << X[3] << "\n";
    file << "\n";
    for (int i = 0; i < 2 * n; i += 2)
    {
        file << X[i] << " ";
        //std::cout << X[i] << " ";
    }
        //std::cout << "\n";
}

Vec3D *f_gravitation(Vec3D *X, Vec3D *Xdot, double *M, int n)
{
    for (int i = 0; i < 2 * n; i += 2)
        Xdot[i] = X[i + 1];

    for (int i = 1; i < 2 * n; i += 2)
    {
        Xdot[i] = Vec3D();
        for (int j = 0; j < 2 * n; j += 2)
            if (j + 1 != i)
                Xdot[i] += (M[j / 2] * G * (X[j] - X[i - 1])) / (pow(norm(X[j] - X[i - 1]), 3));
    }

    return Xdot;
}

void d_t(Vec3D kepler, Vec3D numerical, ofstream &f)
{
    //cout << "dt: " << dist(numerical, kepler) << "\n";
    f << " " << setprecision(10) << dist(numerical, kepler);
}

Vec3D r_kepler(double t, KeplerDataBox *kdb, ofstream &file)
{
    double mean_anomaly = kdb->M;
    //cout << "Some value or vector:  " << mean_anomaly << "\n";
    mean_anomaly += kdb->mean_motion * t;

    // обратный переход
    double E_t = mean_anomaly; // the eccentric anomaly E(t)
    for (int j = 0; j < 5; j++)
        E_t = E_t - (E_t - kdb->e * sin(E_t) - mean_anomaly) / (1 - kdb->e * cos(E_t));

    double v_t = 2 * atan2(sqrt(1 + kdb->e) * sin(E_t / 2), sqrt(1 - kdb->e) * cos(E_t / 2)); // the true anomaly ν(t)

    double rc_t = kdb->a * (1 - kdb->e * cos(E_t));

    Vec3D or_t = {rc_t * cos(v_t), rc_t * sin(v_t), 0}; // the position vector
    Vec3D r_t = {
        or_t.get_x() * (cos(kdb->w) * cos(kdb->omega) - sin(kdb->w) * cos(kdb->i) * sin(kdb->omega)) - or_t.get_y() * (sin(kdb->w) * cos(kdb->omega) + cos(kdb->w) * cos(kdb->i) * sin(kdb->omega)), // o(t) in the inertial frame
        or_t.get_x() * (cos(kdb->w) * sin(kdb->omega) + sin(kdb->w) * cos(kdb->i) * cos(kdb->omega)) + or_t.get_y() * (cos(kdb->w) * cos(kdb->i) * cos(kdb->omega) - sin(kdb->w) * sin(kdb->omega)),
        or_t.get_x() * (sin(kdb->w) * sin(kdb->i)) + or_t.get_y() * (cos(kdb->w) * sin(kdb->i)),
    };

    file << r_t << " ";
    return r_t;
}

pair<Vec3D, Vec3D> barycentre(Vec3D *X, double *M, int n, ofstream &file)
{
    Vec3D rb, vb;
    double masses = 0.0;

    for (int i = 0; i < 2 * n; i += 2)
    {
        rb += (M[i / 2] * X[i]);
        vb += (M[i / 2] * X[i + 1]);

        masses += M[i / 2];
    }

    rb /= masses;
    vb /= masses;

    //cout << "rb: " << norm(rb) << "\n";
    file << setprecision(10) << norm(rb);

    //cout << "vb: " << norm(vb) << "\n";
    file << " " << setprecision(10) << norm(vb);
    return make_pair(rb, vb);
}

void zeroing_barycentre(Vec3D *X, pair<Vec3D, Vec3D> bc, int n)
{
    for (int i = 0; i < 2 * n; i += 2)
    {
        X[i] -= bc.first;
        X[i + 1] -= bc.second;
    }
}

Vec3D momentum(Vec3D *X, double *M, int n, ofstream &file)
{
    Vec3D p;
    for (int i = 0; i < 2 * n; i += 2)
    {
        p += M[i / 2] * X[i + 1];
    }

    //cout << "momentum: " << X[1].get_x() << "\n";

    file << " " << setprecision(10) << norm(p);

    return p;
}

Vec3D angular_momentum(Vec3D *Xt, double *M, int n, ofstream &file)
{
    Vec3D L;
    for (int i = 0; i < 2 * n; i += 2)
        L += X(Xt[i], M[i / 2] * Xt[i + 1]);

    //cout << "angular momentum: " << norm(L) << "\n";

    file << " " << setprecision(10) << norm(L);

    return L;
}

double energy(Vec3D *Xt, double *M, int n, ofstream &file)
{
    double kinetic = 0.0;
    double potential = 0.0;
    double potential_i = 0.0;
    double total = 0.0;

    for (int i = 0; i < 2 * n; i += 2)
        kinetic += (M[i / 2] * pow(norm(Xt[i + 1]), 2)) / 2.0;

    for (int i = 0; i < 2 * n; i += 2)
    {
        potential_i = 0;
        for (int j = i + 2; j < 2 * n; j += 2)
            potential_i += M[j / 2] / dist(Xt[i], Xt[j]);

        potential_i *= (-M[i / 2]) * G;
        potential += potential_i;
    }

    total = kinetic + potential;
    //cout << "energy: " << total << "\n";
    file << " " << setprecision(10) << total;

    return total;
}

void euler (int n,  Vec3D *x0, double T,
            Vec3D *(*f)(Vec3D *, Vec3D *, double *, int),
            double h, void (*save)(Vec3D *, ofstream &, int), double *M,
            string namef, string namef_s)
{
    Vec3D *x = new Vec3D[2 * n];
    Vec3D *xdot = new Vec3D[2 * n];

    KeplerDataBox *KeplerElements = new KeplerDataBox;

    memcpy(x, x0, 2 * n * sizeof(Vec3D));
    double t = 0;
    bool last = false;

    ofstream f_scalars(namef_s);
    ofstream outf(namef);

    save(x, outf, n);
    // if (n == 2)
    //     KeplerElements->direct_transition(x[2] - x[0], x[3] - x[1], M[0] + M[1]);

    // barycentre(x, M, n, f_scalars);
    // momentum(x, M, n, f_scalars);
    // angular_momentum(x, M, n, f_scalars);
    // energy(x, M, n, f_scalars);
    // if (n == 2)
    //     d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
    // f_scalars << "\n";

    Vec3D *xdot_tmp = new Vec3D[2 * n];
    Vec3D *x_tmp = new Vec3D[2 * n];
    Vec3D *k = new Vec3D[2 * n];

    do
    {
        if (t + h > T)
        {
            h = (T - t);
            last = true;
        }
        //x += h * f(x, context);
        memcpy(k, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x[i] += h * k[i];

        save(x, outf, n);

        // barycentre(x, M, n, f_scalars);
        // momentum(x, M, n, f_scalars);
        // angular_momentum(x, M, n, f_scalars);
        // energy(x, M, n, f_scalars);
        t += h;
        // if (n == 2)
        //     d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        //f_scalars << "\n";
    } while (!last);
    
    delete[] x_tmp;
    delete[] xdot_tmp;
    delete[] x;
    delete[] xdot;
    delete[] k;
    //delete KeplerElements;
}

void rk4(int n, Vec3D *x0, double T,
         Vec3D *(*f)(Vec3D *, Vec3D *, double *, int),
         double h, void (*save)(Vec3D *, ofstream &, int), double *M,
         string namef, string namef_s)
{
    Vec3D *x = new Vec3D[2 * n];
    Vec3D *xdot = new Vec3D[2 * n];

    KeplerDataBox *KeplerElements = new KeplerDataBox;

    memcpy(x, x0, 2 * n * sizeof(Vec3D));
    double t = 0;
    bool last = false;

    ofstream f_scalars(namef_s);
    ofstream outf(namef);

    save(x, outf, n);
    if (n == 2)
        KeplerElements->direct_transition(x[2] - x[0], x[3] - x[1], M[0] + M[1]);

    barycentre(x, M, n, f_scalars);
    momentum(x, M, n, f_scalars);
    angular_momentum(x, M, n, f_scalars);
    energy(x, M, n, f_scalars);
    if (n == 2)
        d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
    f_scalars << "\n";

    Vec3D *xdot_tmp = new Vec3D[2 * n];
    Vec3D *x_tmp = new Vec3D[2 * n];
    Vec3D *k1 = new Vec3D[2 * n];
    Vec3D *k2 = new Vec3D[2 * n];
    Vec3D *k3 = new Vec3D[2 * n];
    Vec3D *k4 = new Vec3D[2 * n];

    do
    {
        if (t + h > T)
        {
            h = (T - t);
            last = true;
        }

        memcpy(k1, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += (h / 2) * k1[i];

        memcpy(k2, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += (h / 2) * k2[i];

        memcpy(k3, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * k3[i];

        memcpy(k4, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        for (int i = 0; i < 2 * n; i++)
            x[i] += h * ((1.0 / 6.0) * k1[i] + 1.0 / 3.0 * k2[i] + 1.0 / 3.0 * k3[i] + 1.0 / 6.0 * k4[i]);

        save(x, outf, n);

        barycentre(x, M, n, f_scalars);
        momentum(x, M, n, f_scalars);
        angular_momentum(x, M, n, f_scalars);
        energy(x, M, n, f_scalars);
        t += h;
        if (n == 2)
            d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        f_scalars << "\n";
    } while (!last);

    delete[] x_tmp;
    delete[] xdot_tmp;
    delete[] x;
    delete[] xdot;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete KeplerElements;
}

void rk4_Ralston(int n, Vec3D *x0, double T,
                 Vec3D *(*f)(Vec3D *, Vec3D *, double *, int),
                 double h, void (*save)(Vec3D *, ofstream &, int), double *M,
                 string namef, string namef_s)
{
    Vec3D *x = new Vec3D[2 * n];
    Vec3D *xdot = new Vec3D[2 * n];

    KeplerDataBox *KeplerElements = new KeplerDataBox;

    memcpy(x, x0, 2 * n * sizeof(Vec3D));
    double t = 0;
    bool last = false;

    ofstream f_scalars(namef_s);
    ofstream outf(namef);

    save(x0, outf, n);

    if (n == 2)
        KeplerElements->direct_transition(x[2]-x[0], x[3]-x[1], M[0]+M[1]);

    barycentre(x, M, n, f_scalars);
    momentum(x, M, n, f_scalars);
    angular_momentum(x, M, n, f_scalars);
    energy(x, M, n, f_scalars);
    if (n == 2)
        d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
    f_scalars << "\n";

    Vec3D *xdot_tmp = new Vec3D[2 * n];
    Vec3D *x_tmp = new Vec3D[2 * n];
    Vec3D *k1 = new Vec3D[2 * n];
    Vec3D *k2 = new Vec3D[2 * n];
    Vec3D *k3 = new Vec3D[2 * n];
    Vec3D *k4 = new Vec3D[2 * n];

    do
    {
        if (t + h > T)
        {
            h = (T - t);
            last = true;
        }

        memcpy(k1, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * (0.4) * k1[i]; 

        memcpy(k2, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * ((0.29697761) * k1[i] + (0.15875964) * k2[i]);

        memcpy(k3, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * ((0.21810040) * k1[i] - (3.05096516) * k2[i] + (3.83286476) * k3[i]);

        memcpy(k4, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        for (int i = 0; i < 2 * n; i++)
            x[i] += h * ((0.17476028) * k1[i] + (-0.55148066) * k2[i] + (1.20553560) * k3[i] + (0.17118478) * k4[i]);


        save(x, outf, n);

        barycentre(x, M, n, f_scalars);
        momentum(x, M, n, f_scalars);
        angular_momentum(x, M, n, f_scalars);
        energy(x, M, n, f_scalars);
        t += h;
        if (n == 2)
            d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        f_scalars << "\n";
    } while (!last);
    delete[] x_tmp;
    delete[] xdot_tmp;
    delete[] x;
    delete[] xdot;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete KeplerElements;
}

void rk5(int n, Vec3D *x0, double T,
         Vec3D *(*f)(Vec3D *, Vec3D *, double *, int),
         double h, void (*save)(Vec3D *, ofstream &, int), double *M,
         string namef, string namef_s)
{
    Vec3D *x = new Vec3D[2 * n];
    Vec3D *xdot = new Vec3D[2 * n];

    KeplerDataBox *KeplerElements = new KeplerDataBox;

    memcpy(x, x0, 2 * n * sizeof(Vec3D));
    double t = 0;
    bool last = false;

    ofstream f_scalars(namef_s);
    ofstream outf(namef);

    save(x0, outf, n);

    if (n == 2)
        KeplerElements->direct_transition(x[2]-x[0], x[3]-x[1], M[0]+M[1]);

    barycentre(x, M, n, f_scalars);
    momentum(x, M, n, f_scalars);
    angular_momentum(x, M, n, f_scalars);
    energy(x, M, n, f_scalars);
    if (n == 2)
        d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
    f_scalars << "\n";

    Vec3D *xdot_tmp = new Vec3D[2 * n];
    Vec3D *x_tmp = new Vec3D[2 * n];
    Vec3D *k1 = new Vec3D[2 * n];
    Vec3D *k2 = new Vec3D[2 * n];
    Vec3D *k3 = new Vec3D[2 * n];
    Vec3D *k4 = new Vec3D[2 * n];
    Vec3D *k5 = new Vec3D[2 * n];
    Vec3D *k6 = new Vec3D[2 * n];

    do
    {
        if (t + h > T)
        {
            h = (T - t);
            last = true;
        }

        memcpy(k1, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * (1.0 / 5.0) * k1[i];

        memcpy(k2, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * (3.0 / 40.0) * k1[i] + h * (9.0 / 40.0) * k2[i];

        memcpy(k3, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * (44.0 / 45.0) * k1[i] - h * (56.0 / 15.0) * k2[i] + h * (32.0 / 9.0) * k3[i];

        memcpy(k4, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * (19372.0 / 6561.0) * k1[i] - h * (25360.0 / 2187.0) * k2[i] + h * (64448.0 / 6561.0) * k3[i] - h * (212.0 / 729.0) * k4[i];

        memcpy(k5, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * (9017.0 / 3168.0) * k1[i] - h * (355.0 / 33.0) * k2[i] + h * (46732.0 / 5247.0) * k3[i] + h * (49.0 / 176.0) * k4[i] - h * (5103.0 / 18656.0) * k5[i];

        memcpy(k6, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        for (int i = 0; i < 2 * n; i++)
            x[i] += h * ((35.0 / 384.0) * k1[i] + (500.0 / 1113.0) * k3[i] + (125.0 / 192.0) * k4[i] - (2187.0 / 6784.0) * k5[i] + (11.0 / 84.0) * k6[i]);

        save(x, outf, n);
        barycentre(x, M, n, f_scalars);
        momentum(x, M, n, f_scalars);
        angular_momentum(x, M, n, f_scalars);
        energy(x, M, n, f_scalars);
        t += h;
        if (n == 2)
            d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        f_scalars << "\n";
    } while (!last);
    delete[] x_tmp;
    delete[] xdot_tmp;
    delete[] x;
    delete[] xdot;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete[] k5;
    delete[] k6;

    delete KeplerElements;
}

void adams_bashfort_4(int n, Vec3D *x0, double T,
                      Vec3D *(*f)(Vec3D *, Vec3D *, double *, int),
                      double h, void (*save)(Vec3D *, ofstream &, int), double *M,
                      string namef, string namef_s)
{
    Vec3D *x = new Vec3D[2 * n];
    Vec3D *xdot = new Vec3D[2 * n];

    KeplerDataBox *KeplerElements = new KeplerDataBox;

    memcpy(x, x0, 2 * n * sizeof(Vec3D));
    double t = 0;
    bool last = false;

    ofstream f_scalars(namef_s);
    ofstream outf(namef);

    save(x, outf, n);
    if (n == 2)
        KeplerElements->direct_transition(x[2] - x[0], x[3] - x[1], M[0] + M[1]);

    barycentre(x, M, n, f_scalars);
    momentum(x, M, n, f_scalars);
    angular_momentum(x, M, n, f_scalars);
    energy(x, M, n, f_scalars);
    if (n == 2)
        d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
    f_scalars << "\n";

    Vec3D *xdot_tmp = new Vec3D[2 * n];
    Vec3D *x_tmp = new Vec3D[2 * n];
    Vec3D *k1 = new Vec3D[2 * n];
    Vec3D *k2 = new Vec3D[2 * n];
    Vec3D *k3 = new Vec3D[2 * n];
    Vec3D *k4 = new Vec3D[2 * n];

    Vec3D **buffer = new Vec3D *[3];
    for (int i = 0; i < 3; i++)
    {
        memcpy(k1, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));
        buffer[i] = new Vec3D[2 * n];
        memcpy(buffer[i], k1, 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += (h / 2) * k1[i];

        memcpy(k2, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += (h / 2) * k2[i];

        memcpy(k3, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * k3[i];

        memcpy(k4, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        for (int i = 0; i < 2 * n; i++)
            x[i] += h * ((1.0 / 6.0) * k1[i] + 1.0 / 3.0 * k2[i] + 1.0 / 3.0 * k3[i] + 1.0 / 6.0 * k4[i]);

        save(x, outf, n);

        barycentre(x, M, n, f_scalars);
        momentum(x, M, n, f_scalars);
        angular_momentum(x, M, n, f_scalars);
        energy(x, M, n, f_scalars);
        t += h;
        if (n == 2)
            d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        f_scalars << "\n";
    }

    do
    {
        if (t + h > T)
        {
            h = (T - t);
            last = true;
        }
        memcpy(k1, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x[i] += h * ((55.0 / 24.0) * k1[i] - (59.0 / 24.0) * buffer[2][i] + (37.0 / 24.0) * buffer[1][i] - (3.0 / 8.0) * buffer[0][i]);

        for (int i = 0; i < 2; i++)
            memcpy(buffer[i], buffer[i + 1], 2 * n * sizeof(Vec3D));

        memcpy(buffer[2], xdot, 2 * n * sizeof(Vec3D));

        save(x, outf, n);

        barycentre(x, M, n, f_scalars);
        momentum(x, M, n, f_scalars);
        angular_momentum(x, M, n, f_scalars);
        energy(x, M, n, f_scalars);
        t += h;
        if (n == 2)
            d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        f_scalars << "\n";
    } while (!last);

    for (int i = 0; i < 3; i++)
        delete[] buffer[i];
    delete[] buffer;
    delete[] x_tmp;
    delete[] xdot_tmp;
    delete[] x;
    delete[] xdot;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete KeplerElements;
}

void adams_bashfort_10(int n, Vec3D *x0, double T,
                      Vec3D *(*f)(Vec3D *, Vec3D *, double *, int),
                      double h, void (*save)(Vec3D *, ofstream &, int), double *M,
                      string namef, string namef_s)
{
    Vec3D *x = new Vec3D[2 * n];
    Vec3D *xdot = new Vec3D[2 * n];

    KeplerDataBox *KeplerElements = new KeplerDataBox;

    memcpy(x, x0, 2 * n * sizeof(Vec3D));
    double t = 0;
    bool last = false;

    ofstream f_scalars(namef_s);
    ofstream outf(namef);

    save(x, outf, n);
    if (n == 2)
        KeplerElements->direct_transition(x[2] - x[0], x[3] - x[1], M[0] + M[1]);

    barycentre(x, M, n, f_scalars);
    momentum(x, M, n, f_scalars);
    angular_momentum(x, M, n, f_scalars);
    energy(x, M, n, f_scalars);
    if (n == 2)
        d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
    f_scalars << "\n";

    Vec3D *xdot_tmp = new Vec3D[2 * n];
    Vec3D *x_tmp = new Vec3D[2 * n];
    Vec3D *k1 = new Vec3D[2 * n];
    Vec3D *k2 = new Vec3D[2 * n];
    Vec3D *k3 = new Vec3D[2 * n];
    Vec3D *k4 = new Vec3D[2 * n];

    Vec3D **buffer = new Vec3D *[9];
    for (int i = 0; i < 9; i++) // i < 3
    {
        memcpy(k1, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));
        buffer[i] = new Vec3D[2 * n];
        memcpy(buffer[i], k1, 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += (h / 2) * k1[i];

        memcpy(k2, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += (h / 2) * k2[i];

        memcpy(k3, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        memcpy(x_tmp, x, 2 * n * sizeof(Vec3D));
        for (int i = 0; i < 2 * n; i++)
            x_tmp[i] += h * k3[i];

        memcpy(k4, f(x_tmp, xdot, M, n), 2 * n * sizeof(Vec3D));

        for (int i = 0; i < 2 * n; i++)
            x[i] += h * ((1.0 / 6.0) * k1[i] + 1.0 / 3.0 * k2[i] + 1.0 / 3.0 * k3[i] + 1.0 / 6.0 * k4[i]);

        save(x, outf, n);

        barycentre(x, M, n, f_scalars);
        momentum(x, M, n, f_scalars);
        angular_momentum(x, M, n, f_scalars);
        energy(x, M, n, f_scalars);
        t += h;
        if (n == 2)
            d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        f_scalars << "\n";
    }

    do
    {
        if (t + h > T)
        {
            h = (T - t);
            last = true;
        }
        memcpy(k1, f(x, xdot, M, n), 2 * n * sizeof(Vec3D));

        /*
            coefficient of f_n / k1 = 4.1717988040123455
            coefficient of f_n-1 / buffer[8] = -14.466929701278659
            coefficient of f_n-2 / buffer[7] = 36.64195877425044
            coefficient of f_n-3 / buffer[6] = -62.64629850088183
            coefficient of f_n-4 / buffer[5] = 74.17932071208114
            coefficient of f_n-5 / buffer[4] = -61.28364225088183
            coefficient of f_n-6 / buffer[3] = 34.80740520282187
            coefficient of f_n-7 / buffer[2] = -12.994284611992946
            coefficient of f_n-8 / buffer[1] = 2.87764701829806
            coefficient of f_n-9 / buffer[0] = -0.2869754464285714
        */
        
        for (int i = 0; i < 2 * n; i++)
            x[i] += h * ((4.1717988040123455) * k1[i]
             + (-14.466929701278659) * buffer[8][i]
             + (36.64195877425044) * buffer[7][i] 
             + (-62.64629850088183) * buffer[6][i] 
             + (74.17932071208114) * buffer[5][i] 
             + (-61.28364225088183) * buffer[4][i] 
             + (34.80740520282187) * buffer[3][i] 
             + (-12.994284611992946) * buffer[2][i] 
             + (2.87764701829806) * buffer[1][i] 
             + (-0.2869754464285714) * buffer[0][i]);

        for (int i = 0; i < 8; i++) // i < 2
            memcpy(buffer[i], buffer[i + 1], 2 * n * sizeof(Vec3D));
        memcpy(buffer[8], xdot, 2 * n * sizeof(Vec3D)); // buffer[2]
        save(x, outf, n);

        barycentre(x, M, n, f_scalars);
        momentum(x, M, n, f_scalars);
        angular_momentum(x, M, n, f_scalars);
        energy(x, M, n, f_scalars);
        t += h;
        if (n == 2)
            d_t(r_kepler(t, KeplerElements, outf), x[2] - x[0], f_scalars);
        f_scalars << "\n";
    } while (!last);

    for (int i = 0; i < 9; i++)
        delete[] buffer[i];
    delete[] buffer;
    delete[] x_tmp;
    delete[] xdot_tmp;
    delete[] x;
    delete[] xdot;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete KeplerElements;
}

int main(int argc, char *argv[])
{
    double T = 100000, h = 4.3;
    double M[3] = {0, 0, 0};
    int n = 0;
    Vec3D body_r_1(0, 0, 0);
    Vec3D body_v_1(0, 0, 0);

    Vec3D body_r_2(0, 0, 0);
    Vec3D body_v_2(0, 0, 0);

    Vec3D body_r_3(0, 0, 0);
    Vec3D body_v_3(0, 0, 0);

    Vec3D x0[6] = {body_r_1, body_v_1, body_r_2, body_v_2, body_r_3, body_v_3};

    string namef;
    string namef_s;
    string quantity = "(";

    cout << "Enter stop time: ";
    cin >> T;

    cout << "Enter step: ";
    cin >> h;

    int q;
    //cout << "At the begin of main you can change period and step\n";
    cout << "Choose one of the following tests:\n";
    cout << "   '1' — Sun–Earth\n";
    cout << "   '2' — Sun–Mercury\n";
    cout << "   '3' — Earth–Moon\n";
    cout << "   '4' — Sun–Earth–Moon\n";
    cout << "   '5' — Sun–Earth–Mercury\n";
    cout << "   '6' — Sun–Earth–Jupiter\n";
    cout << "\nEnter a number from 1 to 6: ";

    cin >> q;

    cout << "\nChoose a method of integration:\n";
    cout << "   '1' — classical RK4\n";
    cout << "   '2' — Ralston's RK4\n";
    cout << "   '3' — Adams-Bashforth's of the 4th order\n";
    cout << "   '4' — Dorman-Prince's RK5\n";
    cout << "   '5' — Adams-Bashforth's of the 10th order\n";
    cout << "\nEnter a number from 1 to 5: ";

    int option = 0;
    cin >> option;

    ofstream ff;
    switch (q)
    {
    case 1:
        n = 2;

        M[0] = 132712440043.17/G; M[1] = 398600.43629/G;

        body_r_1.x = -1289359.131389; body_r_1.y = 435580.809773; body_r_1.z = 217346.339234; // Sun
        body_v_1.x = -0.005589; body_v_1.y = -0.013552; body_v_1.z = -0.005606;

        body_r_2.x = -56393719.986435; body_r_2.y = 125599283.627938; body_r_2.z = 54475540.715896; // Earth
        body_v_2.x = -28.101464; body_v_2.y = -10.359519; body_v_2.z = -4.491546;

        x0[0] = body_r_1; x0[1] = body_v_1; x0[2] = body_r_2; x0[3] = body_v_2;
        
        break;
    case 2:
        n = 2;

        M[0] = 132712440043.17/G; M[1] = 22031.78000/G;

        body_r_1.x = -1289359.131389; body_r_1.y = 435580.809773; body_r_1.z = 217346.339234; // Sun
        body_v_1.x = -0.005589; body_v_1.y = -0.013552; body_v_1.z = -0.005606;

        body_r_2.x = 24829189.310503; body_r_2.y = 35490246.260774; body_r_2.z = 16236286.402691; // Mercury
        body_v_2.x = -50.025633; body_v_2.y = 24.091267; body_v_2.z = 18.055668;

        x0[0] = body_r_1; x0[1] = body_v_1; x0[2] = body_r_2; x0[3] = body_v_2;

        break;
    case 3:
        n = 2;

        M[0] = 398600.43629/G; M[1] = 4902.800088/G;

        body_r_1.x = -56393719.986435; body_r_1.y = 125599283.627938; body_r_1.z = 54475540.715896; // Earth
        body_v_1.x = -28.101464; body_v_1.y = -10.359519; body_v_1.z = -4.491546;

        body_r_2.x = -56149090.514527; body_r_2.y = 125896244.845812; body_r_2.z = 54599075.137295; // Moon
        body_v_2.x = -28.855760; body_v_2.y = -9.840541; body_v_2.z = -4.172968;

        x0[0] = body_r_1; x0[1] = body_v_1; x0[2] = body_r_2; x0[3] = body_v_2;

        break;
    case 4:
        n = 3;

        M[0] = 132712440043.17/G; M[1] = 398600.43629/G; M[2] = 4902.800088/G;

        body_r_1.x = -1289359.131389; body_r_1.y = 435580.809773; body_r_1.z = 217346.339234; // Sun
        body_v_1.x = -0.005589; body_v_1.y = -0.013552; body_v_1.z = -0.005606;

        body_r_2.x = -56393719.986435; body_r_2.y = 125599283.627938; body_r_2.z = 54475540.715896; // Earth
        body_v_2.x = -28.101464; body_v_2.y = -10.359519; body_v_2.z = -4.491546;

        body_r_3.x = -56149090.514527; body_r_3.y = 125896244.845812; body_r_3.z = 54599075.137295; // Moon
        body_v_3.x = -28.855760; body_v_3.y = -9.840541; body_v_3.z = -4.172968;

        x0[0] = body_r_1; x0[1] = body_v_1; x0[2] = body_r_2; x0[3] = body_v_2;  x0[4] = body_r_3; x0[5] = body_v_3;

        break;
    case 5:
        n = 3;

        M[0] = 132712440043.17/G; M[1] = 398600.43629/G; M[2] = 22031.78000/G;

        body_r_1.x = -1289359.131389; body_r_1.y = 435580.809773; body_r_1.z = 217346.339234; // Sun
        body_v_1.x = -0.005589; body_v_1.y = -0.013552; body_v_1.z = -0.005606;

        body_r_2.x = -56393719.986435; body_r_2.y = 125599283.627938; body_r_2.z = 54475540.715896; // Earth
        body_v_2.x = -28.101464; body_v_2.y = -10.359519; body_v_2.z = -4.491546;

        body_r_3.x = 24829189.310503; body_r_3.y = 35490246.260774; body_r_3.z = 16236286.402691; // Mercury
        body_v_3.x = -50.025633; body_v_3.y = 24.091267; body_v_3.z = 18.055668;

        x0[0] = body_r_1; x0[1] = body_v_1; x0[2] = body_r_2; x0[3] = body_v_2;  x0[4] = body_r_3; x0[5] = body_v_3;

        break;
    case 6:
        n = 3;

        M[0] = 132712440043.17/G; M[1] = 398600.43629/G; M[2] = 22031.78000/G;

        body_r_1.x = -1289359.131389; body_r_1.y = 435580.809773; body_r_1.z = 217346.339234; // Sun
        body_v_1.x = -0.005589; body_v_1.y = -0.013552; body_v_1.z = -0.005606;

        body_r_2.x = -56393719.986435; body_r_2.y = 125599283.627938; body_r_2.z = 54475540.715896; // Earth
        body_v_2.x = -28.101464; body_v_2.y = -10.359519; body_v_2.z = -4.491546;

        body_r_3.x = 699972473.074112; body_r_3.y = -228287591.855144; body_r_3.z = -114889588.896914; // Jupiter
        body_v_3.x = 4.318004; body_v_3.y = 11.884809; body_v_3.z = 4.989120;

        x0[0] = body_r_1; x0[1] = body_v_1; x0[2] = body_r_2; x0[3] = body_v_2;  x0[4] = body_r_3; x0[5] = body_v_3;

        break;
    
    default:
        cout << "pls try again\n";

        return 0;
    }

    quantity += to_string(n) + ").txt";

    zeroing_barycentre(x0, barycentre(x0, M, n, ff), n);

    switch(option)
    {
        case 1:
            namef = "data_rk4" + quantity;
            namef_s = "scalars_rk4" + quantity;
            rk4(n, x0, T, f_gravitation, h, print, M, namef, namef_s);
            break;
        case 2:
            namef = "data_ralston" + quantity;
            namef_s = "scalars_ralston" + quantity;
            rk4_Ralston(n, x0, T, f_gravitation, h, print, M, namef, namef_s);
            break;
        case 3:
            namef = "data_adams" + quantity;
            namef_s = "scalars_adams" + quantity;
            adams_bashfort_4(n, x0, T, f_gravitation, h, print, M, namef, namef_s);
            break;
        case 4:
            namef = "data_rk5" + quantity;
            namef_s = "scalars_rk5" + quantity;
            rk5(n, x0, T, f_gravitation, h, print, M, namef, namef_s);
            break;
        case 5:
            namef = "data_adams_10" + quantity;
            namef_s = "scalars_adams_10" + quantity;
            adams_bashfort_10(n, x0, T, f_gravitation, h, print, M, namef, namef_s);
            break;
        default:
            cout << "pls try again\n";
    }

    return 0;
}
