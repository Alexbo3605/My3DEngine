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

#include <memory>
#include <vector>
#include <string>

#include "EngineInput.h"

 // Forward declarations (уникаємо зайвих #include для прискорення компіляції)
class SFMLWindowProvider;
class Scene;
class RenderingPipeline;
class ICommand;

/**
 * Description:
 * EN: Core engine class responsible for the main game loop, subsystem initialization, and state orchestration.
 * UA: Головний клас рушія, що відповідає за основний ігровий цикл, ініціалізацію підсистем та оркестрацію станів.
 */
class Application
{
public:
    Application(std::string& modelPath);

    // Деструктор реалізовано в .cpp для підтримки std::unique_ptr з Forward Declarations
    ~Application();

    /**
     * Description:
     * EN: Starts the main engine loop (Input -> Update -> Render). Blocking call.
     * UA: Запускає основний цикл рушія (Ввід -> Оновлення -> Рендер). Блокуючий виклик.
     */
    void run();

private:
    /**
     * Description:
     * EN: Polls hardware events and dispatches them to the InputHandler.
     * UA: Збирає апаратні події та передає їх до InputHandler.
     */
    void processInput(float deltaTime);

    /**
     * Description:
     * EN: Executes the rendering pipeline and swaps window buffers.
     * UA: Виконує конвеєр рендерингу та перемикає буфери вікна.
     */
    void render();

    // void updateLogic(); // Зарезервовано для фізики/анімацій

private:
    std::unique_ptr<SFMLWindowProvider> m_window;
    std::unique_ptr<Scene> m_scene;
    std::unique_ptr<RenderingPipeline> m_pipeline;

    std::vector<EngineEvent> m_eventBuffer;
    std::vector<std::unique_ptr<ICommand>> m_commandBuffer;

    size_t m_renderedVertices{ 0 };
    size_t m_totalVertices{ 0 };
};