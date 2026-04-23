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

#include "IWindowProvider.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

struct EngineEvent; // Forward declaration
class RenderingPipeline;

/**
 * Description:
 * EN: SFML implementation of the window provider interface. Manages the OS window, OpenGL context, and basic drawing.
 * UA: SFML-реалізація інтерфейсу вікна. Керує вікном ОС, контекстом OpenGL та базовим малюванням.
 */
class SFMLWindowProvider final : public IWindowProvider
{
public:
    SFMLWindowProvider();
    ~SFMLWindowProvider() override;

    /**
     * Description:
     * EN: Checks if the SFML window is open.
     * UA: Перевіряє, чи відкрите вікно SFML.
     */
    bool isRunning() const override;

    /**
     * Description:
     * EN: Clears the SFML render window buffers.
     * UA: Очищує буфери вікна рендеру SFML.
     */
    void clearAll() override;

    /**
     * Description:
     * EN: Swaps the buffers and displays the rendered frame.
     * UA: Перемикає буфери та виводить відрендерений кадр на екран.
     */
    void displayAll() override;

    /**
     * Description:
     * EN: Submits a vertex array for rendering via SFML.
     * UA: Передає масив вершин для рендерингу через SFML.
     */
    void renderAll(const std::vector<EngineVertex>& geometry) override;

    /**
     * Description:
     * EN: Polls SFML events and translates them into engine-agnostic EngineEvents.
     * UA: Збирає події SFML та перетворює їх на незалежні від рушія EngineEvents.
     */
    void pollEvents(std::vector<EngineEvent>& outEvents) override;

    /**
     * Description:
     * EN: Updates the window title with the current frames per second (FPS).
     * UA: Оновлює заголовок вікна з поточним значенням кадрів на секунду (FPS).
     */
    void updateFPS(const std::string& baseTitle) override;

private:
    /**
     * Description:
     * EN: Internal initialization of the sf::RenderWindow.
     * UA: Внутрішня ініціалізація sf::RenderWindow.
     */
    void initWindow() override;

private:
    // EN: Smart pointer to automatically manage window lifetime (RAII).
    // UA: Розумний вказівник для автоматичного керування життєвим циклом вікна (RAII).
    std::unique_ptr<sf::RenderWindow> m_window;

    sf::Clock m_fpsClock;
    int m_frameCount = 0;
};