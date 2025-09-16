#include "Vector3f.h"

// ===== Конструктори =====
Vector3f::Vector3f(float xx, float yy, float zz, float ww)
    : x(xx), y(yy), z(zz), w(ww) {
}

Vector3f::~Vector3f(void) {}



void Vector3f::operator+=(const Vector3f& v){

    this->x += v.x, y += v.y, z += v.z;
}

void Vector3f::operator-=(const Vector3f& v){
    x -= v.x, y -= v.y, z -= v.z;
}

void Vector3f::operator*=(const float f){
    x *= f, y *= f, z *= f;
}

void Vector3f::operator/=(const float f){
    x /= f, y /= f, z /= f;
}



Vector3f operator+(const Vector3f& v1, const Vector3f& v2){
    return Vector3f(v1.x + v2.x,
                    v1.y + v2.y,
                    v1.z + v2.z);
}

Vector3f operator-(const Vector3f& v1, const Vector3f& v2){
    return Vector3f(v1.x - v2.x,
                    v1.y - v2.y,
                    v1.z - v2.z);
}

Vector3f operator*(const Vector3f& v1, const float f){
    return Vector3f(v1.x * f,
                    v1.y * f,
                    v1.z * f);
}

Vector3f operator*(const float f, const Vector3f& v1){
    return v1 * f;
}

Vector3f operator/(const Vector3f& v1, const float f){   
    return Vector3f(v1.x / f,
                    v1.y / f,
                    v1.z / f);
}

Vector3f operator/(const float f, const Vector3f& v1){
    return v1 / f;
}

Vector3f operator-(const Vector3f& v1){
    return v1* -1;
}

float Vector3f::dotProduct(const Vector3f& v1, const Vector3f& v2)
{
    return
        v1.x * v2.x +
        v1.y * v2.y +
        v1.z * v2.z;
}

Vector3f Vector3f::CrossProduct(const Vector3f& v1, const Vector3f& v2)
{
    return Vector3f(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x);
}

float Vector3f::len()
{
    return sqrt(x * x + y * y + z * z);
}

void Vector3f::norm()
{
    *this /= sqrt(x * x + y * y + z * z);

}
