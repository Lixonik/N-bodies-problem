#include <iomanip>
#include <iostream>
#include <cmath>

#pragma once

#define G 6.67e-20

class Vec3D
{

public:
    double x, y, z;
    Vec3D(double x = 0, double y = 0, double z = 0);

    double get_x();

    double get_y();

    double get_z();

    friend Vec3D operator-(const Vec3D vec_1, const Vec3D vec_2);

    friend Vec3D operator+(const Vec3D vec_1, const Vec3D vec_2);

    Vec3D(const Vec3D &other);

    friend double operator*(const Vec3D vec_1, const Vec3D vec_2);

    friend Vec3D operator*(const double value, const Vec3D vec);

    friend Vec3D operator*(const Vec3D vec, const double value);

    friend Vec3D operator/(const Vec3D vec_1, const Vec3D vec_2);

    friend Vec3D operator/(const double value, const Vec3D vec);

    friend Vec3D operator/(const Vec3D vec, const double value);

    friend double norm(Vec3D vec);

    friend double dist(Vec3D vec_1, Vec3D vec_2);

    friend Vec3D X(const Vec3D vec_1, const Vec3D vec_2);

    Vec3D &operator=(const Vec3D &other);

    Vec3D(Vec3D &&other);

    Vec3D &operator=(Vec3D &&other);

    friend bool operator==(const Vec3D &object_1, const Vec3D &object_2);

    friend bool operator!=(const Vec3D &object_1, const Vec3D &object_2);
    
    Vec3D &operator+=(const Vec3D &other);

    Vec3D &operator-=(const Vec3D &other);

    Vec3D &operator*=(const Vec3D &other);

    Vec3D &operator/=(const Vec3D &other);

    Vec3D &operator+=(const double &value);

    Vec3D &operator-=(const double &value);

    Vec3D &operator*=(const double &value);

    Vec3D &operator/=(const double &value);

    friend std::ostream &operator<<(std::ostream &out, const Vec3D &object);
};