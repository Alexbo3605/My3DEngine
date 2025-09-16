#pragma once

#include <cmath>
class Vector3f
{
public:
	// ===== Конструктори =====
	Vector3f(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f, float ww = 1.0f);

	~Vector3f(void);



    /*Погуглити чому так не можна вибиває помилку лінковки*/
    //inline float getX() const;
    //inline float getY() const;
    //inline float getZ() const;
    //inline float getW() const;




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



    float x, y, z, w;
private:
	
};
