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

#include "Mesh.h"
#include "ObjLoader.h"
#include <utility>

Mesh::Mesh(std::vector<Vector3f> pos,
    std::vector<Vector3f> norm,
    std::vector<Vector2f> uv,
    std::vector<uint32_t> ind)
    : m_positions(std::move(pos))
    , m_normals(std::move(norm))
    , m_uvs(std::move(uv))
    , m_indices(std::move(ind))
{
}

Mesh::Mesh(const std::string& fileName, int readWith, int materialType)
{
    if (readWith == 1)
    {
        define_as_cube();
    }
    else
    {
        if (!serialize(fileName, readWith))
        {
            // TODO: обробка помилок
            // throw ReadError(readWith);
        }
    }
}

const std::vector<Vector3f>& Mesh::getPositions() const { return m_positions; }
const std::vector<Vector3f>& Mesh::getNormals() const { return m_normals; }
const std::vector<Vector2f>& Mesh::getUVs() const { return m_uvs; }
const std::vector<uint32_t>& Mesh::getIndices() const { return m_indices; }

void Mesh::addVertexData(const Vector3f& position, const Vector2f& uv, const Vector3f& normal)
{
    m_positions.push_back(position);
    m_uvs.push_back(uv);
    m_normals.push_back(normal);
}

void Mesh::addTriangle(uint32_t i0, uint32_t i1, uint32_t i2)
{
    m_indices.push_back(i0);
    m_indices.push_back(i1);
    m_indices.push_back(i2);
}

uint32_t Mesh::getVertexCount() const
{
    return static_cast<uint32_t>(m_positions.size());
}

bool Mesh::isEmpty() const
{
    // Сітка вважається порожньою, якщо немає індексів (немає що малювати)
    return m_indices.empty();
}

bool Mesh::hasNormals() const
{
    return !m_normals.empty();
}

bool Mesh::hasUVs() const
{
    return !m_uvs.empty();
}

bool Mesh::serialize(const std::string& fileName, int readWith)
{
    ObjLoader loader;
    if (loader.load(fileName, *this)) {
        return true;
    }
    return false;
}

void Mesh::define_as_cube()
{
    m_positions.clear();
    m_normals.clear();
    m_uvs.clear();
    m_indices.clear();

    // EN: Prevent reallocation by reserving exact memory.
    m_positions.reserve(24);
    m_normals.reserve(24);
    m_uvs.reserve(24);
    m_indices.reserve(36);

    auto addFace = [&](const Vector3f& bl, const Vector3f& tl,
        const Vector3f& tr, const Vector3f& br,
        const Vector3f& normal)
        {
            uint32_t startIdx = static_cast<uint32_t>(m_positions.size());

            m_positions.push_back(bl);
            m_positions.push_back(tl);
            m_positions.push_back(tr);
            m_positions.push_back(br);

            for (int i = 0; i < 4; ++i) {
                m_normals.push_back(normal);
            }

            // Використовуємо emplace_back для уникнення копіювання тимчасових Vector2f
            m_uvs.emplace_back(0.0f, 0.0f);
            m_uvs.emplace_back(0.0f, 1.0f);
            m_uvs.emplace_back(1.0f, 1.0f);
            m_uvs.emplace_back(1.0f, 0.0f);

            m_indices.push_back(startIdx + 0);
            m_indices.push_back(startIdx + 1);
            m_indices.push_back(startIdx + 2);

            m_indices.push_back(startIdx + 0);
            m_indices.push_back(startIdx + 2);
            m_indices.push_back(startIdx + 3);
        };

    const float s = 0.5f;

    // SOUTH (Z = -0.5)
    addFace(Vector3f(-s, -s, -s), Vector3f(-s, s, -s), Vector3f(s, s, -s), Vector3f(s, -s, -s), Vector3f(0.0f, 0.0f, -1.0f));

    // EAST (X = 0.5)
    addFace(Vector3f(s, -s, -s), Vector3f(s, s, -s), Vector3f(s, s, s), Vector3f(s, -s, s), Vector3f(1.0f, 0.0f, 0.0f));

    // NORTH (Z = 0.5)
    addFace(Vector3f(s, -s, s), Vector3f(s, s, s), Vector3f(-s, s, s), Vector3f(-s, -s, s), Vector3f(0.0f, 0.0f, 1.0f));

    // WEST (X = -0.5)
    addFace(Vector3f(-s, -s, s), Vector3f(-s, s, s), Vector3f(-s, s, -s), Vector3f(-s, -s, -s), Vector3f(-1.0f, 0.0f, 0.0f));

    // TOP (Y = 0.5)
    addFace(Vector3f(-s, s, -s), Vector3f(-s, s, s), Vector3f(s, s, s), Vector3f(s, s, -s), Vector3f(0.0f, 1.0f, 0.0f));

    // BOTTOM (Y = -0.5)
    addFace(Vector3f(-s, -s, s), Vector3f(-s, -s, -s), Vector3f(s, -s, -s), Vector3f(s, -s, s), Vector3f(0.0f, -1.0f, 0.0f));
}