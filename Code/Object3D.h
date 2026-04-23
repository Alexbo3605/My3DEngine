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

#include <memory>

#include "Mesh.h"
#include "Matrix4x4.h"

 /**
  * Description:
  * EN: Represents surface properties of an object
  */
struct Material
{
    // RGB color [0.0, 1.0]. Default: Light Gray.
    Vector3f diffuseColor{ 0.8f, 0.8f, 0.8f };
};

/**
 * Description:
 * EN: Represents an entity in 3D space, containing its spatial transform, material, and geometry (Mesh)
 */
class Object3D final
{
public:
    Object3D();

    /**
     * Description:
     * EN: Initializes the object with a generated or loaded mesh.
     * UA: ≤н≥ц≥ал≥зуЇ об'Їкт з≥ згенерованою або завантаженою с≥ткою.
     */
    Object3D(const std::string& fileName, int meshType, int materialType);
    ~Object3D() = default;

    // Rule of 5: Move semantics explicitly allowed, copying strictly forbidden.
    Object3D(Object3D&&) noexcept = default;
    Object3D& operator=(Object3D&&) noexcept = default;
    Object3D(const Object3D&) = delete;
    Object3D& operator=(const Object3D&) = delete;

    [[nodiscard]] bool isEmpty() const;

    // ==========================================
    // Setters (Absolute Transform)
    // ==========================================
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setScale(float x, float y, float z);

    void setPosition(const Vector3f& pos);
    void setRotation(const Vector3f& rot);
    void setScale(const Vector3f& scale);

    // ==========================================
    // Modifiers (Relative Transform)
    // ==========================================
    void move(const Vector3f& delta);
    void rotate(const Vector3f& delta);
    void scale(const Vector3f& factor); // Multiplicative scaling

    // ==========================================
    // Components
    // ==========================================
    [[nodiscard]] const Material& getMaterial() const { return m_material; }
    void setMaterial(const Material& mat) { m_material = mat; }

    void setMesh(std::unique_ptr<Mesh> mesh);
    [[nodiscard]] Mesh& getMesh() const;

    // ==========================================
    // Rendering Matrices
    // ==========================================
    [[nodiscard]] Matrix4x4 getModelMatrix() const;

    /**
     * Description:
     * EN: Computes the normal matrix (Inverse Transpose of the upper 3x3 model matrix).
     * UA: ќбчислюЇ матрицю нормалей (ќбернена транспонована верхн€ 3x3 матриц€ модел≥).
     */
    [[nodiscard]] Matrix4x4 getNormalMatrix(const Matrix4x4& model) const;

private:
    [[nodiscard]] Matrix4x4 getTransformMatrix() const;
    [[nodiscard]] Matrix4x4 getRotationMatrix() const;
    [[nodiscard]] Matrix4x4 getScaleMatrix() const;

private:
    Vector3f m_position;
    Vector3f m_rotation;
    Vector3f m_scale;

    Material m_material;
    std::unique_ptr<Mesh> m_mesh;
};