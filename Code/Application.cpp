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


#include "Application.h"

#include "SFMLWindowProvider.h"
#include "RenderingPipeline.h"
#include "InputHandler.h"
#include "Scene.h" 
#include "ICommand.h"

#include <chrono>

Application::Application(std::string& modelPath)
    : m_window(std::make_unique<SFMLWindowProvider>())
    , m_scene(std::make_unique<Scene>(modelPath, static_cast<int>(SceneLoadMode::CREATE_WITH_OBJ), 1))
    , m_pipeline(std::make_unique<RenderingPipeline>())
{
    // EN: Pre-allocate memory to prevent heap fragmentation during the main loop.
    m_eventBuffer.reserve(20);
    m_commandBuffer.reserve(10);

    if (auto* p_obj = m_scene->getObject3D()) {
        p_obj->setPosition(0.0f, 0.0f, -3.0f);

        m_totalVertices = p_obj->getMesh().getIndices().size();
    }



}

// Дефолтна реалізація повинна бути тут, де компілятор бачить повні визначення класів для unique_ptr
Application::~Application() = default;

void Application::run()
{
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (m_window->isRunning())
    {
        // 1. Обчислення Delta Time
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - lastTime;
        lastTime = currentTime;

        // Отримуємо час у секундах
        float deltaTime = elapsedTime.count();

        // 2. Обробка вводу (передаємо deltaTime, як ми зробили в попередньому кроці)
        processInput(deltaTime);
        /* updateLogic(); */
        render();

        m_window->updateFPS("My 3D Engine", m_renderedVertices, m_totalVertices);
    }
}

void Application::processInput(float deltaTime)
{
    m_eventBuffer.clear();
    m_commandBuffer.clear();

    m_window->pollEvents(m_eventBuffer);

    if (!m_eventBuffer.empty())
    {
        InputHandler::handleInput(m_eventBuffer, deltaTime, m_commandBuffer);

        for (const auto& p_cmd : m_commandBuffer)
        {
            p_cmd->execute(*m_scene);
        }
    }
}

void Application::render()
{
    m_window->clearAll();

    // EN: Fetch strictly visible geometry from the pipeline.
    const auto& frameGeometry = m_pipeline->render(*m_scene);

    // Зберігаємо кількість відрендерених вершин (після culling та clipping)
    m_renderedVertices = frameGeometry.size();

    m_window->renderAll(frameGeometry);
    m_window->displayAll();
}