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

#include "Camera.h"
#include "Constants.h" 
#include <cmath>

Camera::Camera(Vector3f startPos)
    : m_position{ startPos }
    , m_forward{ 0.0f, 0.0f, 1.0f }
    , m_up{ 0.0f, 1.0f, 0.0f }
    , m_right{ 1.0f, 0.0f, 0.0f }
    , m_worldUp{ 0.0f, 1.0f, 0.0f }
    , m_yaw{ -constants::kPi * 0.5f } // -90 градусів: початковий погляд вздовж осі -Z
    , m_pitch{ 0.0f }
{
    updateCameraVectors();
}

Matrix4x4 Camera::getViewMatrix() const
{
    const Vector3f target = m_position + m_forward;
    return Matrix4x4::getViewMatrix(m_position, target, m_up);
}

void Camera::processKeyboard(CameraMovement direction, float speed)
{
    switch (direction)
    {
    case CameraMovement::Forward:  m_position += m_forward * speed; break;
    case CameraMovement::Backward: m_position -= m_forward * speed; break;
    case CameraMovement::Left:     m_position -= m_right * speed; break;
    case CameraMovement::Right:    m_position += m_right * speed; break;
    case CameraMovement::Up:       m_position += m_up * speed; break;
    case CameraMovement::Down:     m_position -= m_up * speed; break;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset)
{

    m_yaw += xOffset * constants::kMouseSensitivity;
    m_pitch -= yOffset * constants::kMouseSensitivity;

    // EN: Constrain pitch to avoid Gimbal Lock (~89 degrees in radians).
    // UA: Обмеження нахилу для уникнення Gimbal Lock (~89 градусів у радіанах).
    const float pitchLimit = constants::kPi * 0.49f;
    if (m_pitch > pitchLimit)  m_pitch = pitchLimit;
    if (m_pitch < -pitchLimit) m_pitch = -pitchLimit;

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    Vector3f front;
    front.x = std::cos(m_yaw) * std::cos(m_pitch);
    front.y = std::sin(m_pitch);
    front.z = std::sin(m_yaw) * std::cos(m_pitch);

    m_forward = front.normalize();

    // Порядок векторного добутку (Cross) визначає напрямок (Right-hand rule)
    m_right = m_forward.cross(m_worldUp).normalize();
    m_up = m_right.cross(m_forward).normalize();
}