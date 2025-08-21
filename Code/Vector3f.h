#pragma once
#include <iostream>
#include <math.h>
class Vector3f
{
private:
    float x, y, z, additional;

public:
    // ===== Конструктори =====
    Vector3f(float xx= 0.0f, float yy= 0.0f, float zz= 0.0f, float aa = 1.0f);

    virtual ~Vector3f(void);


    float getX() const;
    float getY() const;
    float getZ() const;
   

    // Сеттери (setters)
    void setX(float x_val);
    void setY(float y_val);
    void setZ(float z_val);

    // ===== Оператори =====

   // (зробив friend для швидкості бо гетери будуть більше жерти) а так по хорошему звичайною функцією
    friend Vector3f operator +(const Vector3f& v1, const Vector3f& v2);
    friend Vector3f operator -(const Vector3f& v1, const Vector3f& v2);

    friend Vector3f operator *(const Vector3f& v1, const float f);
    friend Vector3f operator *(const float f, const Vector3f& v1);

    friend Vector3f operator /(const Vector3f& v1, const float f);
    friend Vector3f operator /(const float f, const Vector3f& v1);

    friend Vector3f operator -(const Vector3f& v1);

    void operator += (const Vector3f& v);
    void operator -= (const Vector3f& v);
    void operator *= (const float f);
    void operator /= (const float f);
        

    //скалярний добуток  Dot Product показують наскільки вектори співнапрямлені якщо 90° то 0
    float dotProduct(const Vector3f& v1, const Vector3f& v2);

    //векторний добуток
    Vector3f CrossProduct(const Vector3f& v1, const Vector3f& v2);

    float len();

    //Нормалізація вектора (приведення його до одиничних координат)
    void norm();

};

