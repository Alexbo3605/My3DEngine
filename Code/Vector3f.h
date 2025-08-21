#pragma once
#include <iostream>
#include <math.h>
class Vector3f
{
private:
    float x, y, z, additional;

public:
    // ===== ������������ =====
    Vector3f(float xx= 0.0f, float yy= 0.0f, float zz= 0.0f, float aa = 1.0f);

    virtual ~Vector3f(void);


    float getX() const;
    float getY() const;
    float getZ() const;
   

    // ������� (setters)
    void setX(float x_val);
    void setY(float y_val);
    void setZ(float z_val);

    // ===== ��������� =====

   // (������ friend ��� �������� �� ������ ������ ����� �����) � ��� �� �������� ��������� ��������
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
        

    //��������� �������  Dot Product ��������� �������� ������� ������������ ���� 90� �� 0
    float dotProduct(const Vector3f& v1, const Vector3f& v2);

    //��������� �������
    Vector3f CrossProduct(const Vector3f& v1, const Vector3f& v2);

    float len();

    //����������� ������� (���������� ���� �� ��������� ���������)
    void norm();

};

