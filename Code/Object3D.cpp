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

#include "Object3D.h"
#include <utility>

Object3D::Object3D()
    : m_position{ 0.0f, 0.0f, 0.0f }
    , m_rotation{ 0.0f, 0.0f, 0.0f }
    , m_scale{ 1.0f, 1.0f, 1.0f }
    , m_mesh{ std::make_unique<Mesh>() }
{
}

Object3D::Object3D(const std::string& fileName, int meshType, int materialType)
    : m_position{ 0.0f, 0.0f, 0.0f }
    , m_rotation{ 0.0f, 0.0f, 0.0f }
    , m_scale{ 1.0f, 1.0f, 1.0f }
    , m_mesh{ std::make_unique<Mesh>(fileName, meshType, materialType) }
{
}

bool Object3D::isEmpty() const
{
    return m_mesh->isEmpty();
}

void Object3D::setPosition(float x, float y, float z) { m_position = Vector3f(x, y, z); }
void Object3D::setRotation(float x, float y, float z) { m_rotation = Vector3f(x, y, z); }
void Object3D::setScale(float x, float y, float z) { m_scale = Vector3f(x, y, z); }

void Object3D::setPosition(const Vector3f& pos) { m_position = pos; }
void Object3D::setRotation(const Vector3f& rot) { m_rotation = rot; }
void Object3D::setScale(const Vector3f& scale) { m_scale = scale; }

void Object3D::move(const Vector3f& delta)
{
    m_position += delta;
}

void Object3D::rotate(const Vector3f& delta)
{
    m_rotation += delta;
}

void Object3D::scale(const Vector3f& factor)
{
    // EN: Scaling is multiplicative.
    // UA: Масштабування є мультиплікативним.
    m_scale *= factor;
}

void Object3D::setMesh(std::unique_ptr<Mesh> mesh)
{
    m_mesh = std::move(mesh);
}

Mesh& Object3D::getMesh() const
{
    return *m_mesh;
}

Matrix4x4 Object3D::getTransformMatrix() const
{
    Matrix4x4 matrix;

    // Identity + Translation
    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;

    matrix.m[3][0] = m_position.x;
    matrix.m[3][1] = m_position.y;
    matrix.m[3][2] = m_position.z;

    return matrix;
}

Matrix4x4 Object3D::getRotationMatrix() const
{
    const Matrix4x4 matRotX = Matrix4x4::getRotationX(m_rotation.x);
    const Matrix4x4 matRotY = Matrix4x4::getRotationY(m_rotation.y);
    const Matrix4x4 matRotZ = Matrix4x4::getRotationZ(m_rotation.z);

    // Order matters: Pitch (X), Yaw (Y), Roll (Z)
    return matRotX * matRotY * matRotZ;
}

Matrix4x4 Object3D::getScaleMatrix() const
{
    Matrix4x4 matrix;
    matrix.m[0][0] = m_scale.x;
    matrix.m[1][1] = m_scale.y;
    matrix.m[2][2] = m_scale.z;
    matrix.m[3][3] = 1.0f;

    return matrix;
}

Matrix4x4 Object3D::getModelMatrix() const
{
    const Matrix4x4 matScale = getScaleMatrix();
    const Matrix4x4 matRot = getRotationMatrix();
    const Matrix4x4 matTrans = getTransformMatrix();

    // V * Scale * Rotation * Translation
    return matScale * matRot * matTrans;
}

Matrix4x4 Object3D::getNormalMatrix(const Matrix4x4& model) const
{
    Matrix4x4 normalMat;

    float m00 = model.m[0][0], m01 = model.m[0][1], m02 = model.m[0][2];
    float m10 = model.m[1][0], m11 = model.m[1][1], m12 = model.m[1][2];
    float m20 = model.m[2][0], m21 = model.m[2][1], m22 = model.m[2][2];

    float det = m00 * (m11 * m22 - m21 * m12) -
        m01 * (m10 * m22 - m12 * m20) +
        m02 * (m10 * m21 - m11 * m20);

    // Fallback if scaling collapses the object
    if (det == 0.0f) {
        return getRotationMatrix();
    }

    float invDet = 1.0f / det;

    normalMat.m[0][0] = (m11 * m22 - m21 * m12) * invDet;
    normalMat.m[0][1] = -(m01 * m22 - m02 * m21) * invDet;
    normalMat.m[0][2] = (m01 * m12 - m02 * m11) * invDet;

    normalMat.m[1][0] = -(m10 * m22 - m12 * m20) * invDet;
    normalMat.m[1][1] = (m00 * m22 - m02 * m20) * invDet;
    normalMat.m[1][2] = -(m00 * m12 - m02 * m10) * invDet;

    normalMat.m[2][0] = (m10 * m21 - m11 * m20) * invDet;
    normalMat.m[2][1] = -(m00 * m21 - m01 * m20) * invDet;
    normalMat.m[2][2] = (m00 * m11 - m01 * m10) * invDet;

    normalMat.m[3][3] = 1.0f;

    return normalMat;
}