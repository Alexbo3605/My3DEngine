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

#include "ICommand.h"
#include "Scene.h"
#include <iostream> 

 /**
  * Description:
  * EN: Command to move the active object (and in the future, the Camera) in 3D space.
  * UA: Команда для переміщення активного об'єкта (а в майбутньому - камери) у 3D просторі.
  */
class MoveCameraCommand final : public ICommand
{
public:
    MoveCameraCommand(float x, float y, float z)
        : m_velocity(x, y, z)
    {
    }

    void execute(Scene& scene) override
    {
        try
        {
            auto* p_object = scene.getObject3D();

            if (p_object != nullptr && !p_object->isEmpty())
            {
                p_object->move(m_velocity);
            }

            // TODO: В майбутньому тут буде виклик методів камери (WASD)
            // Camera* p_camera = scene.getCamera();
            // p_camera->processKeyboard(...);
        }
        catch (const std::exception& e)
        {
            std::cerr << "[MoveCameraCommand Error]: " << e.what() << '\n';
        }
        catch (...)
        {
            std::cerr << "[MoveCameraCommand Error]: Unknown exception occurred.\n";
        }
    }

private:
    Vector3f m_velocity;
};

/**
 * Description:
 * EN: Command to rotate the active 3D object using Euler angles.
 * UA: Команда для обертання активного 3D об'єкта за допомогою кутів Ейлера.
 */
class RotateObjectCommand final : public ICommand
{
public:
    RotateObjectCommand(float x, float y, float z)
        : m_rotation(x, y, z)
    {
    }

    void execute(Scene& scene) override
    {
        try
        {
            auto* p_object = scene.getObject3D();

            if (p_object != nullptr && !p_object->isEmpty())
            {
                p_object->rotate(m_rotation);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "[RotateObjectCommand Error]: " << e.what() << '\n';
        }
        catch (...)
        {
            std::cerr << "[RotateObjectCommand Error]: Unknown exception occurred.\n";
        }
    }

private:
    Vector3f m_rotation;
};