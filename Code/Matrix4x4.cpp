/**
 * MIT License
 * Copyright (c) 2026 [AlexBo/My3DEngine]
 * * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 */

#include "Matrix4x4.h"
#include <cmath>

Matrix4x4 Matrix4x4::getProjectionMatrix(int width, int height, float zNear, float zFar, float FOV) noexcept
{
    // Виправлено на стандартне співвідношення сторін: width / height
    float aspect = static_cast<float>(height) / static_cast<float>(width);
    float fovRad = 1.0f / std::tan(FOV * 0.5f / 180.0f * constants::kPi);

    Matrix4x4 mat;
    mat.m[0][0] = aspect * fovRad;
    mat.m[1][1] = fovRad;
    mat.m[2][2] = zFar / (zFar - zNear);
    mat.m[3][2] = (-zFar * zNear) / (zFar - zNear);
    mat.m[2][3] = 1.0f;
    mat.m[3][3] = 0.0f;

    return mat;
}

Matrix4x4 Matrix4x4::getViewMatrix(const Vector3f& pos, const Vector3f& target, const Vector3f& up) noexcept
{
    const Vector3f forward = (target - pos).normalize();
    const Vector3f right = up.cross(forward).normalize();
    const Vector3f newUp = forward.cross(right);

    const float dotX = -pos.dot(right);
    const float dotY = -pos.dot(newUp);
    const float dotZ = -pos.dot(forward);

    Matrix4x4 mat;
    mat.m[0][0] = right.x;    mat.m[0][1] = newUp.x;    mat.m[0][2] = forward.x;    mat.m[0][3] = 0.0f;
    mat.m[1][0] = right.y;    mat.m[1][1] = newUp.y;    mat.m[1][2] = forward.y;    mat.m[1][3] = 0.0f;
    mat.m[2][0] = right.z;    mat.m[2][1] = newUp.z;    mat.m[2][2] = forward.z;    mat.m[2][3] = 0.0f;
    mat.m[3][0] = dotX;       mat.m[3][1] = dotY;       mat.m[3][2] = dotZ;         mat.m[3][3] = 1.0f;

    return mat;
}

Matrix4x4 Matrix4x4::getRotationX(float angle) noexcept
{
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    Matrix4x4 mat;
    mat.m[0][0] = 1.0f;
    mat.m[1][1] = c;  mat.m[1][2] = s;
    mat.m[2][1] = -s; mat.m[2][2] = c;
    mat.m[3][3] = 1.0f;

    return mat;
}

Matrix4x4 Matrix4x4::getRotationY(float angle) noexcept
{
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    Matrix4x4 mat;
    mat.m[0][0] = c;  mat.m[0][2] = s;
    mat.m[1][1] = 1.0f;
    mat.m[2][0] = -s; mat.m[2][2] = c;
    mat.m[3][3] = 1.0f;

    return mat;
}

Matrix4x4 Matrix4x4::getRotationZ(float angle) noexcept
{
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    Matrix4x4 mat;
    mat.m[0][0] = c;  mat.m[0][1] = -s;
    mat.m[1][0] = s;  mat.m[1][1] = c;
    mat.m[2][2] = 1.0f;
    mat.m[3][3] = 1.0f;

    return mat;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const noexcept
{
    Matrix4x4 res;

    // EN: Unrolled matrix multiplication for optimal performance and SIMD auto-vectorization.
    for (int r = 0; r < 4; ++r)
    {
        res.m[r][0] = m[r][0] * other.m[0][0] + m[r][1] * other.m[1][0] + m[r][2] * other.m[2][0] + m[r][3] * other.m[3][0];
        res.m[r][1] = m[r][0] * other.m[0][1] + m[r][1] * other.m[1][1] + m[r][2] * other.m[2][1] + m[r][3] * other.m[3][1];
        res.m[r][2] = m[r][0] * other.m[0][2] + m[r][1] * other.m[1][2] + m[r][2] * other.m[2][2] + m[r][3] * other.m[3][2];
        res.m[r][3] = m[r][0] * other.m[0][3] + m[r][1] * other.m[1][3] + m[r][2] * other.m[2][3] + m[r][3] * other.m[3][3];
    }

    return res;
}

Vector3f Matrix4x4::multiplyNormal(const Vector3f& normal, const Matrix4x4& normalMatrix) noexcept
{
    return Vector3f(
        normal.x * normalMatrix.m[0][0] + normal.y * normalMatrix.m[1][0] + normal.z * normalMatrix.m[2][0],
        normal.x * normalMatrix.m[0][1] + normal.y * normalMatrix.m[1][1] + normal.z * normalMatrix.m[2][1],
        normal.x * normalMatrix.m[0][2] + normal.y * normalMatrix.m[1][2] + normal.z * normalMatrix.m[2][2]
    );
}