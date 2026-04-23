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
#include <atomic>

#include "Scene.h"
#include "TVector.h" // Для векторної математики
#include "RenderTypes.h"


/**
 * Description:
 * EN: Core software rasterization pipeline. Transforms 3D models into 2D screen-space vertices.
 * UA: Основний конвеєр програмної растеризації. Перетворює 3D моделі у 2D вершини екранного простору.
 */
class RenderingPipeline final
{
public:
    RenderingPipeline();
    ~RenderingPipeline() = default;

    /**
     * Description:
     * EN: Executes the rendering pipeline for the active scene.
     * UA: Виконує конвеєр рендерингу для активної сцени.
     * * Returns:
     * EN: A constant reference to the processed 2D vertex buffer (Zero-copy).
     * UA: Константне посилання на оброблений буфер 2D вершин (Без копіювання).
     */
    [[nodiscard]] const std::vector<EngineVertex>& render(Scene& scene);

private:
    /**
     * Description:
     * EN: Structure of Arrays (SoA) for cache-friendly parallel geometry processing.
     * UA: Структура масивів (SoA) для паралельної обробки геометрії з ефективним використанням кешу.
     */
    struct TrianglesSoA
    {
        std::vector<Vector3f> v0; // NDC Coordinates
        std::vector<Vector3f> v1;
        std::vector<Vector3f> v2;

        std::vector<EngineColor> colors;
        std::vector<float> depths;
        std::vector<uint32_t> drawOrder;

        void resize(size_t size)
        {
            v0.resize(size);
            v1.resize(size);
            v2.resize(size);
            colors.resize(size);
            depths.resize(size);
            drawOrder.resize(size);
        }
    };

    // Внутрішні буфери
    std::vector<EngineVertex> m_vertexArrayBuffer;
    TrianglesSoA m_triangles;
    size_t m_activeTrianglesCount{ 0 };

    // ==========================================
    // Етапи конвеєра (Pipeline Stages)
    // ==========================================

    /**
     * Description:
     * EN: Calculates world coordinates, performs back-face culling, and prepares data for clipping.
     * UA: Обчислює світові координати, виконує відсікання задніх граней (culling) та готує дані для кліпінгу.
     */
    void processGeometry(const Object3D& obj, const Camera& camera);

    /**
     * Description:
     * EN: Clips polygons against the 6 frustum planes (Sutherland-Hodgman) and safely writes to SoA.
     * UA: Відсікає полігони відносно 6 площин фрустума та безпечно записує в SoA.
     */
    void clipAndWritePolygon(
        const Vector4f& p0_clip,
        const Vector4f& p1_clip,
        const Vector4f& p2_clip,
        const EngineColor& shadedColor,
        std::atomic<size_t>& writeIndex
    );

    /**
     * Description:
     * EN: Sorts the processed triangles from back to front (Painter's Algorithm).
     * UA: Сортує оброблені трикутники від найдальшого до найближчого (Алгоритм Художника).
     */
    void sortTrianglesDepth();

    /**
     * Description:
     * EN: Converts sorted NDC triangles into final 2D screen-space vertices.
     * UA: Перетворює відсортовані NDC трикутники у фінальні 2D вершини екранного простору.
     */
    void buildRenderBuffer();

    // Зарезервовано на майбутнє:
    // void applyTransformations();
    // void calculateLighting();
    // void projectTo2D();
};