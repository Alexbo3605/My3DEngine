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

#include "Matrix4x4.h"

  /**
   * Description:
   * EN: Defines possible movement directions for the camera.
   */
enum class CameraMovement
{
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down
};

/**
 * Description:
 * EN: A free-look (FPS style) camera using Euler angles.
 */
class Camera final
{
public:
    /**
     * Description:
     * EN: Initializes the camera at a given world position.
     */
    explicit Camera(Vector3f startPos = Vector3f(0.0f, 0.0f, -5.0f));
    ~Camera() = default;

    [[nodiscard]] inline Vector3f getPosition() const { return m_position; }

    /**
     * Description:
     * EN: Returns the LookAt matrix for the rendering pipeline.
     */
    [[nodiscard]] Matrix4x4 getViewMatrix() const;

    /**
     * Description:
     * EN: Translates the camera based on local axes.
     */
    void processKeyboard(CameraMovement direction, float speed);

    /**
     * Description:
     * EN: Updates Euler angles based on mouse deltas.
     */
    void processMouseMovement(float xOffset, float yOffset);

private:
    /**
     * Description:
     * EN: Recalculates Forward, Right, and Up vectors from current Yaw and Pitch.
     */
    void updateCameraVectors();

private:
   
    Vector3f m_position;

    // Вектори напрямку (осі локального простору камери)
    Vector3f m_forward;
    Vector3f m_up;
    Vector3f m_right;
    Vector3f m_worldUp;

    // Кути Ейлера (в радіанах)
    float m_yaw;   // Поворот вліво-вправо
    float m_pitch; // Нахил вгору-вниз
};