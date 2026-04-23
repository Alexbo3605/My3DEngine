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
#include <string>
#include "Object3D.h"
#include "Camera.h"

 /**
  * Description:
  * EN: Defines the data source mode for scene/mesh initialization.
  */
enum class SceneLoadMode
{
    CREATE_WITH_DEFAULT = 1,
    CREATE_WITH_OBJ = 2,
    CREATE_WITH_GLB = 3
};

/**
 * Description:
 * EN: Global directional light properties (e.g., Sun).
 */
struct DirectionalLight
{
    Vector3f direction{ Vector3f(1.0f, -1.0f, 1.0f).normalize() };
    float ambientIntensity{ 0.15f };
    Vector3f color{ 1.0f, 1.0f, 1.0f }; // White light
};

/**
 * Description:
 * EN: Manages the global state of the 3D world, including the camera, lights, and entity list (Object3D).
 */
class Scene final
{
public:
    Scene();

    /**
     * Description:
     * EN: Initializes the scene and automatically loads a primary 3D object.
     *
     * Arguments:
     * fileName     (I) - EN: Model path 
     * fileType     (I) - EN: Parsing mode (SceneLoadMode) 
     * materialType (I) - EN: Material preset 
     */
    explicit Scene(const std::string& fileName, int fileType = 1, int materialType = 1);

    ~Scene() = default;

    // ==========================================
    //  ¿Ã≈–¿ “¿ —¬≤“ÀŒ
    // ==========================================
    [[nodiscard]] Camera& getCamera();
    [[nodiscard]] const DirectionalLight& getGlobalLight() const;

    // ==========================================
    // –Œ¡Œ“¿ « Œ¡'™ “¿Ã»
    // ==========================================

    /**
     * Description:
     * EN: Moves a pre-constructed 3D object into the scene's contiguous array.
     */
    void addObject(Object3D&& obj);

    /**
     * Description:
     * EN: Returns the array of all objects for the Rendering Pipeline.
     */
    [[nodiscard]] const std::vector<Object3D>& getObjects() const;

    /**------------------Depricated
     * Description:
     * EN: Temporary method to get the first active object for legacy commands.
     *
     * Returns:
     * EN: Pointer to the first object, or nullptr if scene is empty.
     */
    [[nodiscard]] Object3D* getObject3D();

    // --- ÀŒ√≤ ¿ ---
    // void update(float deltaTime);

private:
    Camera m_camera;
    DirectionalLight m_globalLight;

    // EN: Contiguous memory storage for cache locality during the render loop.
    std::vector<Object3D> m_objects;
};