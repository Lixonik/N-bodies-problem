#include "Vec3D.h"

Vec3D ::Vec3D(double x, double y, double z) : x(x), y(y), z(z){};

double Vec3D::get_x()
{
    return x;
}

double Vec3D::get_y()
{
    return y;
}

double Vec3D::get_z()
{
    return z;
}

Vec3D operator-(const Vec3D vec_1, const Vec3D vec_2)
{
    return Vec3D(vec_1.x - vec_2.x, vec_1.y - vec_2.y, vec_1.z - vec_2.z);
}

Vec3D operator+(const Vec3D vec_1, const Vec3D vec_2)
{
    return Vec3D(vec_1.x + vec_2.x, vec_1.y + vec_2.y, vec_1.z + vec_2.z);
}

Vec3D ::Vec3D(const Vec3D &other) : x(other.x), y(other.y), z(other.z){};

double operator*(const Vec3D vec_1, const Vec3D vec_2)
{
    return vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z;
}

Vec3D operator*(const double value, const Vec3D vec)
{
    return Vec3D(value * vec.x, value * vec.y, value * vec.z);
}

Vec3D operator*(const Vec3D vec, const double value)
{
    return Vec3D(value * vec.x, value * vec.y, value * vec.z);
}

Vec3D operator/(const Vec3D vec_1, const Vec3D vec_2)
{
    return Vec3D(vec_1.x / vec_2.x, vec_1.y / vec_2.y, vec_1.z / vec_2.z);
}

Vec3D operator/(const double value, const Vec3D vec)
{
    return Vec3D(value / vec.x, value / vec.y, value / vec.z);
}

Vec3D operator/(const Vec3D vec, const double value)
{
    return Vec3D(vec.x / value, vec.y / value, vec.z / value);
}

double norm(Vec3D vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double dist(Vec3D vec_1, Vec3D vec_2)
{
    return sqrt(pow(vec_2.x - vec_1.x, 2) + pow(vec_2.y - vec_1.y, 2) + pow(vec_2.z - vec_1.z, 2));
}

Vec3D X(const Vec3D vec_1, const Vec3D vec_2)
{
    return Vec3D(vec_1.y * vec_2.z - vec_2.y * vec_1.z, vec_2.x * vec_1.z - vec_1.x * vec_2.z, vec_1.x * vec_2.y - vec_2.x * vec_1.y);
}

Vec3D &Vec3D::operator=(const Vec3D &other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

Vec3D ::Vec3D(Vec3D &&other)
{
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(z, other.z);
}

Vec3D &Vec3D::operator=(Vec3D &&other)
{
    if (this != &other)
    {
        std::swap(x, other.x);
        std::swap(y, other.y);
        std::swap(z, other.z);
    }
    return *this;
}

bool operator==(const Vec3D &object_1, const Vec3D &object_2)
{
    return object_1.x == object_2.x && object_1.y == object_2.y && object_1.z == object_2.z;
}

bool operator!=(const Vec3D &object_1, const Vec3D &object_2)
{
    return !(object_1 == object_2);
}

Vec3D &Vec3D::operator+=(const Vec3D &other)
{
    *this = *this + other;

    return *this;
}

Vec3D &Vec3D::operator-=(const Vec3D &other)
{
    *this = *this - other;

    return *this;
}

Vec3D &Vec3D::operator*=(const Vec3D &other)
{
    *this = *this * other;

    return *this;
}

Vec3D &Vec3D::operator/=(const Vec3D &other)
{
    *this = *this / other;

    return *this;
}

Vec3D &Vec3D::operator+=(const double &value)
{
    *this = *this + value;

    return *this;
}

Vec3D &Vec3D::operator-=(const double &value)
{
    *this = *this - value;

    return *this;
}

Vec3D &Vec3D::operator*=(const double &value)
{
    *this = *this * value;

    return *this;
}

Vec3D &Vec3D::operator/=(const double &value)
{
    *this = *this / value;

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Vec3D &object)
{
    out << std::scientific << std::setprecision(7) << object.x << ' ' << object.y << ' ' << object.z;

    return out;
}
