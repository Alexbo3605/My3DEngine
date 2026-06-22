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
#include "RenderTypes.h"

 // Forward declarations для зменшення залежностей
struct EngineEvent;

/**
 * Description:
 * EN: Abstract base class (Interface) for window and context creation (SFML, GLFW, etc.).
 * UA: Абстрактний базовий клас (Інтерфейс) для створення вікна та контексту (SFML, GLFW тощо).
 */
class IWindowProvider
{
public:
    IWindowProvider() = default;
    virtual ~IWindowProvider() = default;

    /**
     * Description:
     * EN: Checks if the window is currently open and running.
     * UA: Перевіряє, чи вікно наразі відкрите та працює.
     *
     * Returns:
     * EN: True if window is active, false otherwise.
     * UA: True, якщо вікно активне, інакше false.
     */
    virtual bool isRunning() const = 0;

    /**
     * Description:
     * EN: Polls hardware/OS events and populates the provided buffer.
     * UA: Збирає апаратні/ОС події та заповнює наданий буфер.
     *
     * Arguments:
     * outEvents (O) - EN: Buffer to store new events | UA: Буфер для збереження нових подій
     */
    virtual void pollEvents(std::vector<EngineEvent>& outEvents) = 0;

    /**
     * Description:
     * EN: Clears the back buffer (color and depth).
     * UA: Очищує задній буфер (колір та глибину).
     */
    virtual void clearAll() = 0;

    /**
     * Description:
     * EN: Draws the provided geometry to the back buffer.
     * UA: Малює передану геометрію у задній буфер.
     *
     * Arguments:
     * geometry (I) - EN: Triangles to render | UA: Трикутники для рендеру
     */
    virtual void renderAll(const std::vector<EngineVertex>& geometry) = 0;

    /**
     * Description:
     * EN: Swaps the back buffer with the front buffer (displays the frame).
     * UA: Перемикає задній буфер з переднім (показує кадр на екран).
     */
    virtual void displayAll() = 0;

    /**
     * Description:
     * EN: Calculates and updates the window title with the current FPS.
     * UA: Розраховує та оновлює заголовок вікна з поточним FPS.
     *
     * Arguments:
     * windowTitle (I) - EN: Base title of the window | UA: Базовий заголовок вікна
     */
    virtual void updateFPS(const std::string& baseTitle, size_t renderedVerts, size_t totalVerts) = 0;

protected:
    /**
     * Description:
     * EN: Internal initialization logic. Must be called by derived constructors.
     * UA: Внутрішня логіка ініціалізації. Має викликатися конструкторами похідних класів.
     */
    virtual void initWindow() = 0;
};