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


#include "Scene.h"

Scene::Scene() = default;

Scene::Scene(const std::string& fileName, int fileType, int materialType)
    : m_camera()
{
    if (!fileName.empty())
    {
        // EN: Construct the object directly inside the vector memory.
        // This implicitly calls Object3D(fileName, fileType, materialType).
        m_objects.emplace_back(fileName, fileType, materialType);
    }
}

// ==========================================
//  ¿Ã≈–¿ “¿ —¬≤“ÀŒ
// ==========================================

Camera& Scene::getCamera()
{
    return m_camera;
}

const DirectionalLight& Scene::getGlobalLight() const
{
    return m_globalLight;
}

// ==========================================
// –Œ¡Œ“¿ « Œ¡'™ “¿Ã»
// ==========================================

void Scene::addObject(Object3D&& obj)
{
    m_objects.push_back(std::move(obj));
}

const std::vector<Object3D>& Scene::getObjects() const
{
    return m_objects;
}

Object3D* Scene::getObject3D()
{
    if (m_objects.empty()) {
        return nullptr;
    }

    return &m_objects.front();
}