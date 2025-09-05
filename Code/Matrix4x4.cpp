#include "Matrix4x4.h"






Matrix4x4::Matrix4x4(): cords(4, std::vector<float>(4, 0.0f))
{
}

Matrix4x4::Matrix4x4(const Vector4x4& v) : cords(v)
{

    /*this->cords = v;*/
   
}

Matrix4x4::Matrix4x4(Vector4x4&& v) noexcept : cords(std::move(v)) {}

Matrix4x4::~Matrix4x4(){}

Matrix4x4 Matrix4x4::getProjectionMatrix(const int width, const int height, const float zNear, const float zFar, const float FOV)
{
    static const float PI = 3.14159265358979323846f;

    return Matrix4x4(   //по суті std::move
        std::vector<std::vector<float>> 
    {
        { ((float)height/(float)width) / (tanf(FOV / 2 / 180 * PI)), 0, 0, 0 },  // FOV/2 / 180 * PI градуси в радіани
        {0,          1 / tanf(FOV / 2 / 180 * PI),           0,            0 },
        {0,          0,              zFar / (zFar - zNear),                1 },
        {0,          0,         ( - zFar * zNear) / (zFar - zNear),        0 }

        }
    );
}


//якось оптимізувати бо буде дуже часто використовуватися
Matrix4x4 Matrix4x4::getRotationX(const float angle)
{
    return Matrix4x4(
        std::vector<std::vector<float>>
    {
        { 1,      0,         0,       0 },
        { 0, cos(angle), -sin(angle), 0 },
        { 0, sin(angle), cos(angle),  0 },
        { 0,      0,         0,       1 }

    }
    );

}

Matrix4x4 Matrix4x4::getRotationY(const float angle)
{
    return Matrix4x4(
        std::vector<std::vector<float>>
    {
        { cos(angle),  0, sin(angle),    0 },
        { 0,           1,      0,        0 },
        { -sin(angle), 0, cos(angle),    0 },
        { 0,           0,      0,        1 }

    }
    );

}

Matrix4x4 Matrix4x4::getRotationZ(const float angle)
{
    return Matrix4x4(
        std::vector<std::vector<float>>
    {
        { cos(angle), -sin(angle), 0, 0 },
        { sin(angle), cos(angle),  0, 0 },
        { 0,         0,      1,       0 },
        { 0,         0,      0,       1 }

    }
    );

}

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

