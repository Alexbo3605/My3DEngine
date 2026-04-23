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

#pragma once

#include "TVector.h"
#include "Constants.h"

 /**
  * Description:
  * EN: 4x4 Matrix class for 3D transformations (Row-Major convention, row-vector multiplication: v * M).
  */
class Matrix4x4 final
{
public:
   
    float m[4][4] = { 0.0f };

    Matrix4x4() = default;
    ~Matrix4x4() = default;

    Matrix4x4(const Matrix4x4& other) = default;
    Matrix4x4(Matrix4x4&& other) noexcept = default;

    Matrix4x4& operator=(const Matrix4x4& other) = default;
    Matrix4x4& operator=(Matrix4x4&& other) noexcept = default;

    /**
     * Description:
     * EN: Multiplies two 4x4 matrices.
     */
    [[nodiscard]] Matrix4x4 operator*(const Matrix4x4& other) const noexcept;

    /**
     * Description:
     * EN: Multiplies a 3D vector by the matrix. Automatically performs Perspective Divide if w != 1.0.
     */
    [[nodiscard]] friend inline Vector3f operator*(const Vector3f& v, const Matrix4x4& mat) noexcept {
        float x = v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + mat.m[3][0];
        float y = v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + mat.m[3][1];
        float z = v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + mat.m[3][2];
        float w = v.x * mat.m[0][3] + v.y * mat.m[1][3] + v.z * mat.m[2][3] + mat.m[3][3];

        if (w != 0.0f && w != 1.0f) {
            float invW = 1.0f / w;
            x *= invW; y *= invW; z *= invW;
        }

        return Vector3f(x, y, z);
    }

    /**
     * Description:
     * EN: Multiplies a 4D vector by the matrix. Retains the W component for homogeneous clipping.
     */
    [[nodiscard]] friend inline Vector4f operator*(const Vector4f& v, const Matrix4x4& mat) noexcept {
        return Vector4f(
            v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + v.w * mat.m[3][0],
            v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + v.w * mat.m[3][1],
            v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + v.w * mat.m[3][2],
            v.x * mat.m[0][3] + v.y * mat.m[1][3] + v.z * mat.m[2][3] + v.w * mat.m[3][3]
        );
    }

    // ==========================================
    // Фабричні методи для генерації матриць
    // ==========================================

    [[nodiscard]] static Matrix4x4 getProjectionMatrix(
        int width = constants::kWidth,
        int height = constants::kHeight,
        float zNear = constants::kZNear,
        float zFar = constants::kZFar,
        float FOV = constants::kFov
    ) noexcept;

    [[nodiscard]] static Matrix4x4 getViewMatrix(
        const Vector3f& pos,
        const Vector3f& target,
        const Vector3f& up
    ) noexcept;

    [[nodiscard]] static Matrix4x4 getRotationX(float angle) noexcept;
    [[nodiscard]] static Matrix4x4 getRotationY(float angle) noexcept;
    [[nodiscard]] static Matrix4x4 getRotationZ(float angle) noexcept;

    /**
     * Description:
     * EN: Transforms a normal vector (ignores translation components of the matrix).
     * UA: Трансформує вектор нормалі (ігнорує компоненти переміщення у матриці).
     */
    [[nodiscard]] static Vector3f multiplyNormal(const Vector3f& normal, const Matrix4x4& normalMatrix) noexcept;
};