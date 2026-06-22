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
#include "InputHandler.h"
#include "Commands.h"      // Підтягує конкретні класи команд (MoveCameraCommand, RotateObjectCommand)
#include "EngineInput.h"   // Підтягує визначення EngineEvent та EngineKey
#include "Constants.h"     // Підтягує налаштування чутливості (constants::kMouseSensitivity)

void InputHandler::handleInput(const std::vector<EngineEvent>& events, float deltaTime, std::vector<std::unique_ptr<ICommand>>& outCommands)
{
    // EN: Clear the buffer without deallocating capacity to prevent heap fragmentation.
    outCommands.clear();

    const float moveSpeed = 10.0f * deltaTime;

    // TODO: У майбутньому сюди варто передавати DeltaTime і множити хардкод-значення (0.005f) на нього.
    for (const auto& ev : events)
    {
        switch (ev.type)
        {
        case EngineKey::W:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, 0.0f, moveSpeed));
            break;

        case EngineKey::S:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, 0.0f, -moveSpeed));
            break;

        case EngineKey::A:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(-moveSpeed, 0.0f, 0.0f));
            break;

        case EngineKey::D:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(moveSpeed, 0.0f, 0.0f));
            break;

        case EngineKey::Space:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, -moveSpeed, 0.0f));
            break;

        case EngineKey::LShift:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, moveSpeed, 0.0f));
            break;

        case EngineKey::MouseDrag:
        {
            // Рух миші (пікселі) НЕ залежить від часу кадру, тому тут deltaTime відсутній.
            float rotX = ev.deltaY * constants::kMouseSensitivity;
            float rotY = ev.deltaX * constants::kMouseSensitivity;

            outCommands.push_back(std::make_unique<RotateObjectCommand>(rotX, rotY, 0.0f));
            break;
        }

        case EngineKey::MouseScroll:
        {
            // Скрол миші — це дискретні події (кліки колеса), тому deltaTime також не потрібен.
            float moveZ = ev.deltaY * 2 * constants::kZoomSpeed;

            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, 0.0f, moveZ));
            break;
        }

        case EngineKey::Unknown:
        default:
            break;
        }
    }
}