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

void InputHandler::handleInput(const std::vector<EngineEvent>& events, std::vector<std::unique_ptr<ICommand>>& outCommands)
{
    // EN: Clear the buffer without deallocating capacity to prevent heap fragmentation.
    outCommands.clear();

    // TODO: У майбутньому сюди варто передавати DeltaTime і множити хардкод-значення (0.005f) на нього.
    for (const auto& ev : events)
    {
        switch (ev.type)
        {
        case EngineKey::W:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, 0.0f, 0.005f));
            break;

        case EngineKey::S:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, 0.0f, -0.005f));
            break;

        case EngineKey::A:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(-0.005f, 0.0f, 0.0f));
            break;

        case EngineKey::D:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.005f, 0.0f, 0.0f));
            break;

        case EngineKey::Space:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, -0.005f, 0.0f));
            break;

        case EngineKey::LShift:
            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, 0.005f, 0.0f));
            break;

        case EngineKey::MouseDrag:
        {
            // EN: Map pixel deltas to rotation angles using sensitivity constants.
            float rotX = ev.deltaY * constants::kMouseSensitivity;
            float rotY = ev.deltaX * constants::kMouseSensitivity;

            outCommands.push_back(std::make_unique<RotateObjectCommand>(rotX, rotY, 0.0f));
            break;
        }

        case EngineKey::MouseScroll:
        {
            // EN: Map scroll wheel delta to Z-axis movement.
            float moveZ = ev.deltaY * constants::kZoomSpeed;

            outCommands.push_back(std::make_unique<MoveCameraCommand>(0.0f, 0.0f, moveZ));
            break;
        }

        case EngineKey::Unknown:
        default:
            break;
        }
    }
}