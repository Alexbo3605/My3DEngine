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

#include <vector>
#include <cstdint>

#include <string>
#include "TVector.h" 

 /**
  * Description:
  * EN: Represents the geometric structure (SoA) of a 3D object, holding vertices, normals, UVs, and indices.
  */
class Mesh final
{
public:
    Mesh() = default;
    ~Mesh() = default;

    /**
     * Description:
     * EN: Move constructor for initializing with existing data buffers. Avoids expensive copying.
     */
    Mesh(std::vector<Vector3f> positions,
        std::vector<Vector3f> normals,
        std::vector<Vector2f> uvs,
        std::vector<uint32_t> indices);

    /**
     * Description:
     * EN: Initializes the mesh either procedurally or by loading from a file.
     *
     * Arguments:
     * fileName     (I) - EN: Path to the 3D model file
     * readWith     (I) - EN: Loading mode identifier
     * materialType (I) - EN: Material preset index
     */
    Mesh(const std::string& fileName, int readWith, int materialType);

    // ==========================================
    // Геттери (Zero-copy)
    // ==========================================
    [[nodiscard]] const std::vector<Vector3f>& getPositions() const;
    [[nodiscard]] const std::vector<Vector3f>& getNormals() const;
    [[nodiscard]] const std::vector<Vector2f>& getUVs() const;
    [[nodiscard]] const std::vector<uint32_t>& getIndices() const;

    /**
     * Description:
     * EN: Appends a single vertex (position, UV, normal) to the SoA buffers.
     */
    void addVertexData(const Vector3f& position, const Vector2f& uv, const Vector3f& normal);

    /**
     * Description:
     * EN: Appends three indices to define a new triangle.
     */
    void addTriangle(uint32_t i0, uint32_t i1, uint32_t i2);

    /**
     * Description:
     * EN: Returns the total number of vertices currently in the mesh.
     */
    [[nodiscard]] uint32_t getVertexCount() const;

    // ==========================================
    // Перевірки стану
    // ==========================================
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] bool hasNormals() const;
    [[nodiscard]] bool hasUVs() const;

    /**
     * Description:
     * EN: Loads mesh data from an external file via ObjLoader.
     */
    bool serialize(const std::string& fileName, int readWith);

private:
    /**
     * Description:
     * EN: Procedurally generates a 1x1x1 unit cube centered at origin.
     */
    void define_as_cube();

private:
    // EN: Data-Oriented Design (Structure of Arrays) for cache-friendly iterations.
    std::vector<Vector3f> m_positions;
    std::vector<Vector3f> m_normals;
    std::vector<Vector2f> m_uvs;
    std::vector<uint32_t> m_indices;
};