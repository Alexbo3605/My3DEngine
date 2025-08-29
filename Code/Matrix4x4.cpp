#include "Matrix4x4.h"



Matrix4x4::Matrix4x4(const Vector4x4& v) : cords(v)
{}
Matrix4x4::Matrix4x4(Vector4x4&& v) noexcept : cords(std::move(v)) {}

Matrix4x4::~Matrix4x4(){}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
{
    if (this != &other) {
        cords = other.cords;
    }
    return *this;
}

Matrix4x4& Matrix4x4::operator=(Matrix4x4&& other) noexcept
{
    if (this != &other) {
        cords = std::move(other.cords);
    }
    return *this;
}



//основна дія при проекції матриці на екран (множення координат(або одиничних векторів) на матрицю)
// можна ще оптимізувати аби не створювався обєкт але 
// порушу багато правил і смердить 
// void operator*(const Vector3f& v1, const Matrix4x4& m1, Vector3f& result)
 
Vector3f operator*(const Vector3f& v1, const Matrix4x4& m1)
{
    float v1_x = v1.getX();
    float v1_y = v1.getY();
    float v1_z = v1.getZ();
    float v1_w = v1.getW();

    Vector3f v(
    /* x */   v1_x * m1.cords[0][0] + v1_y * m1.cords[1][0] + v1_z * m1.cords[2][0] + v1_w * m1.cords[3][0],
    /* y */   v1_x * m1.cords[0][1] + v1_y * m1.cords[1][1] + v1_z * m1.cords[2][1] + v1_w * m1.cords[3][1],
    /* z */   v1_x * m1.cords[0][2] + v1_y * m1.cords[1][2] + v1_z * m1.cords[2][2] + v1_w * m1.cords[3][2],
    /* w */   v1_x * m1.cords[0][3] + v1_y * m1.cords[1][3] + v1_z * m1.cords[2][3] + v1_w * m1.cords[3][3]);

    float w_val = v.getW();
    if (w_val) {
        v.setX(v.getX() / w_val);
        v.setY(v.getY() / w_val);
        v.setZ(v.getZ() / w_val);
    }
    return v;
}

