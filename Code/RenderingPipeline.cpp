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

#include "RenderingPipeline.h"
#include "Constants.h"

#include <execution>
#include <algorithm>
#include <numeric>
#include <array>
#include <iostream>

RenderingPipeline::RenderingPipeline()
{
    // Резервуємо пам'ять заздалегідь, щоб уникнути реалокацій на перших кадрах
    m_vertexArrayBuffer.reserve(30000);
    m_triangles.resize(10000);
}

const std::vector<EngineVertex>& RenderingPipeline::render(Scene& scene)
{
    // 1. Очищуємо буфери (clear() не звільняє capacity пам'яті, що є Best Practice)
    m_vertexArrayBuffer.clear();
    m_activeTrianglesCount = 0;

    // 2. Отримуємо об'єкт (у майбутньому тут буде цикл for по всіх об'єктах сцени)
    Object3D* p_obj = scene.getObject3D();

    if (!p_obj || p_obj->isEmpty()) {
        return m_vertexArrayBuffer;
    }

    const Camera& camera = scene.getCamera();

    // 3. Виконуємо етапи пайплайну
    processGeometry(*p_obj, camera);
    sortTrianglesDepth();
    buildRenderBuffer();

    // Дебаг-вивід (можна закоментувати для Release-білду)
    // std::cout << "m_vertexArray "  << m_vertexArrayBuffer.size() << std::endl;

    return m_vertexArrayBuffer;
}

// =======================================================================
// ПРИВАТНІ МЕТОДИ (Логіка пайплайну)
// =======================================================================

void RenderingPipeline::processGeometry(const Object3D& obj, const Camera& camera)
{
    const Matrix4x4 modelMatrix = obj.getModelMatrix();
    const Matrix4x4 viewMatrix = camera.getViewMatrix();
    static const Matrix4x4 projectionMatrix = Matrix4x4::getProjectionMatrix();

    const Matrix4x4 viewProjMatrix = viewMatrix * projectionMatrix;

    const Mesh& mesh = obj.getMesh();
    const auto& positions = mesh.getPositions();
    const auto& indices = mesh.getIndices();

    const Vector3f cameraPos = camera.getPosition();
    const size_t numTriangles = indices.size() / 3;

    // Резервуємо пам'ять під SoA масиви
    const size_t maxPossibleTriangles = indices.size();
    if (m_triangles.v0.size() < maxPossibleTriangles) {
        m_triangles.resize(maxPossibleTriangles);
    }

    std::atomic<size_t> writeIndex{ 0 };

    // OPTIMIZATION: Використовуємо static вектор, щоб уникнути виділення пам'яті (new/delete) на кожному кадри.
    static std::vector<size_t> loopIndices;
    if (loopIndices.size() < numTriangles) {
        loopIndices.resize(numTriangles);
        std::iota(loopIndices.begin(), loopIndices.end(), 0);
    }

    // --- ПАРАМЕТРИ СВІТЛА ТА МАТЕРІАЛУ ---
    const EngineColor baseColor{ 200, 200, 200, 255 };
    const float ambient = 0.15f;

    // Паралельний цикл по індексах трикутників
    std::for_each(std::execution::par_unseq, loopIndices.begin(), loopIndices.begin() + numTriangles,
        [&](size_t triIdx)
        {
            size_t i = triIdx * 3;

            const Vector3f v0_world = positions[indices[i]] * modelMatrix;
            const Vector3f v1_world = positions[indices[i + 1]] * modelMatrix;
            const Vector3f v2_world = positions[indices[i + 2]] * modelMatrix;

            // Back-Face Culling
            const Vector3f edge1 = v1_world - v0_world;
            const Vector3f edge2 = v2_world - v0_world;
            const Vector3f normal = edge1.cross(edge2).normalize();
            const Vector3f cameraRay = v0_world - cameraPos;

            if (normal.dot(cameraRay) >= 0.0f) {
                return;
            }

            // ОБЧИСЛЕННЯ ОСВІТЛЕННЯ (Світло з камери)
            const Vector3f toLight = (cameraPos - v0_world).normalize();
            float diffuse = std::max(0.0f, normal.dot(toLight));
            float intensity = ambient + (diffuse * (1.0f - ambient));

            const EngineColor shadedColor{
                static_cast<uint8_t>(baseColor.r * intensity),
                static_cast<uint8_t>(baseColor.g * intensity),
                static_cast<uint8_t>(baseColor.b * intensity),
                255
            };

            // Перехід у Clip Space (W != 1.0f)
            const Vector4f p0_clip = Vector4f(v0_world, 1.0f) * viewProjMatrix;
            const Vector4f p1_clip = Vector4f(v1_world, 1.0f) * viewProjMatrix;
            const Vector4f p2_clip = Vector4f(v2_world, 1.0f) * viewProjMatrix;

            clipAndWritePolygon(p0_clip, p1_clip, p2_clip, shadedColor, writeIndex);
        });

    m_activeTrianglesCount = writeIndex.load(std::memory_order_acquire);
}

void RenderingPipeline::clipAndWritePolygon(
    const Vector4f& p0_clip,
    const Vector4f& p1_clip,
    const Vector4f& p2_clip,
    const EngineColor& shadedColor,
    std::atomic<size_t>& writeIndex)
{
    std::array<Vector4f, 9> clipPolygon = { p0_clip, p1_clip, p2_clip };
    size_t polySize = 3;

    auto getClipDistance = [](const Vector4f& v, int plane) -> float {
        switch (plane) {
        case 0: return v.w + v.x; // Ліва
        case 1: return v.w - v.x; // Права
        case 2: return v.w + v.y; // Нижня
        case 3: return v.w - v.y; // Верхня
        case 4: return v.w + v.z; // Ближня
        case 5: return v.w - v.z; // Дальня
        default: return 0.0f;
        }
        };

    // Алгоритм Сазерленда-Ходжмана
    for (int p = 0; p < 6; ++p) {
        if (polySize < 3) return;

        std::array<Vector4f, 9> nextPolygon;
        size_t nextSize = 0;

        for (size_t currIdx = 0; currIdx < polySize; ++currIdx) {
            size_t prevIdx = (currIdx == 0) ? polySize - 1 : currIdx - 1;

            const Vector4f& curr = clipPolygon[currIdx];
            const Vector4f& prev = clipPolygon[prevIdx];

            float dCurr = getClipDistance(curr, p);
            float dPrev = getClipDistance(prev, p);

            if (dCurr >= 0.0f) {
                if (dPrev < 0.0f) {
                    float t = dPrev / (dPrev - dCurr);
                    nextPolygon[nextSize++] = Vector4f::lerp(prev, curr, t);
                }
                nextPolygon[nextSize++] = curr;
            }
            else if (dPrev >= 0.0f) {
                float t = dPrev / (dPrev - dCurr);
                nextPolygon[nextSize++] = Vector4f::lerp(prev, curr, t);
            }
        }

        clipPolygon = nextPolygon;
        polySize = nextSize;
    }

    if (polySize < 3) return;

    // Тріангуляція (Triangle Fan) та Perspective Divide
    const Vector3f ndc0 = clipPolygon[0].toNDC();

    for (size_t j = 1; j < polySize - 1; ++j) {
        const Vector3f ndc1 = clipPolygon[j].toNDC();
        const Vector3f ndc2 = clipPolygon[j + 1].toNDC();

        size_t idx = writeIndex.fetch_add(1, std::memory_order_relaxed);

        if (idx < m_triangles.v0.size()) {
            m_triangles.v0[idx] = ndc0;
            m_triangles.v1[idx] = ndc1;
            m_triangles.v2[idx] = ndc2;
            m_triangles.depths[idx] = (ndc0.z + ndc1.z + ndc2.z) * 0.3333333f;
            m_triangles.colors[idx] = shadedColor;
        }
        else {
            writeIndex.fetch_sub(1, std::memory_order_relaxed);
            break;
        }
    }
}

void RenderingPipeline::sortTrianglesDepth()
{
    if (m_activeTrianglesCount == 0) return;

    std::iota(m_triangles.drawOrder.begin(), m_triangles.drawOrder.begin() + m_activeTrianglesCount, 0);

    std::sort(std::execution::par_unseq,
        m_triangles.drawOrder.begin(),
        m_triangles.drawOrder.begin() + m_activeTrianglesCount,
        [&](uint32_t a, uint32_t b) {
            return m_triangles.depths[a] > m_triangles.depths[b];
        });
}

void RenderingPipeline::buildRenderBuffer()
{
    if (m_activeTrianglesCount == 0) return;

    const float halfWidth = constants::kWidth * 0.5f;
    const float halfHeight = constants::kHeight * 0.5f;

    m_vertexArrayBuffer.resize(m_activeTrianglesCount * 3);

    // OPTIMIZATION: Знову ж таки, уникаємо алокації масиву щокадру
    static std::vector<size_t> loopIndices;
    if (loopIndices.size() < m_activeTrianglesCount) {
        loopIndices.resize(m_activeTrianglesCount);
        std::iota(loopIndices.begin(), loopIndices.end(), 0);
    }

    std::for_each(std::execution::par_unseq, loopIndices.begin(), loopIndices.begin() + m_activeTrianglesCount,
        [&](size_t i)
        {
            const uint32_t realIdx = m_triangles.drawOrder[i];
            const size_t v_idx = i * 3;

            const Vector3f& p0 = m_triangles.v0[realIdx];
            const Vector3f& p1 = m_triangles.v1[realIdx];
            const Vector3f& p2 = m_triangles.v2[realIdx];
            const EngineColor& color = m_triangles.colors[realIdx];

            // Screen Space Mapping (NDC -> Screen)
            const float x1 = (p0.x + 1.0f) * halfWidth;
            const float y1 = (1.0f - p0.y) * halfHeight;

            const float x2 = (p1.x + 1.0f) * halfWidth;
            const float y2 = (1.0f - p1.y) * halfHeight;

            const float x3 = (p2.x + 1.0f) * halfWidth;
            const float y3 = (1.0f - p2.y) * halfHeight;

            // Безпосередній запис у власну структуру
            m_vertexArrayBuffer[v_idx] = { Vector2f(x1, y1), color };
            m_vertexArrayBuffer[v_idx + 1] = { Vector2f(x2, y2), color };
            m_vertexArrayBuffer[v_idx + 2] = { Vector2f(x3, y3), color };
        });
}