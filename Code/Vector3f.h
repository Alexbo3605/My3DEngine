#pragma once

#include <cmath>
class Vector3f
{
public:
	// ===== ������������ =====
	Vector3f(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f, float ww = 1.0f);

	~Vector3f(void);



    /*��������� ���� ��� �� ����� ������ ������� �������*/
    //inline float getX() const;
    //inline float getY() const;
    //inline float getZ() const;
    //inline float getW() const;




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



    float x, y, z, w;
private:
	
};
