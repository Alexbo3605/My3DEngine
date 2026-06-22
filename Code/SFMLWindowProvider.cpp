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

#include "SFMLWindowProvider.h"
#include "EngineInput.h"
#include "WindowSettings.h" // Якщо ви перенесли ці змінні у constants, замініть на "Constants.h"
#include "RenderingPipeline.h"
#include <cstdio>

 // =======================================================================
 // КОНСТРУКТОР ТА ДЕСТРУКТОР
 // =======================================================================

SFMLWindowProvider::SFMLWindowProvider()
{
    initWindow();
}

// EN: Default destructor is sufficient because std::unique_ptr handles m_window automatically.
// UA: Дефолтного деструктора достатньо, оскільки std::unique_ptr автоматично керує m_window.
SFMLWindowProvider::~SFMLWindowProvider() = default;

// =======================================================================
// ІНІЦІАЛІЗАЦІЯ
// =======================================================================

void SFMLWindowProvider::initWindow()
{
    sf::VideoMode videoMode;
    sf::ContextSettings settings;

    videoMode.height = WindowSettings::kWindowHeight;
    videoMode.width = WindowSettings::kWindowWidth;
    settings.antialiasingLevel = WindowSettings::kAntialiasingLevel;

    // EN: Safe dynamic allocation using smart pointers.
    // UA: Безпечне динамічне виділення пам'яті за допомогою розумних вказівників.
    m_window = std::make_unique<sf::RenderWindow>(
        videoMode,
        WindowSettings::kWindowName,
        sf::Style::Titlebar | sf::Style::Close,
        settings
    );

    m_window->setFramerateLimit(WindowSettings::kFpsLimit);
}

// =======================================================================
// МЕТОДИ ВІКНА ТА РЕНДЕРУ
// =======================================================================

bool SFMLWindowProvider::isRunning() const
{
    return m_window->isOpen();
}

void SFMLWindowProvider::clearAll()
{
    m_window->clear();
}

void SFMLWindowProvider::renderAll(const std::vector<EngineVertex>& geometry)
{
    if (geometry.empty()) return;

    // EN: Static buffer avoids reallocating SFML vertices every frame.
    // UA: Статичний буфер уникає перерозподілу пам'яті для вершин SFML кожного кадру.
    static sf::VertexArray sfmlVertices(sf::Triangles);

    // Встановлюємо розмір відповідно до кількості вершин у цьому кадрі
    sfmlVertices.resize(geometry.size());

    // Конвертуємо EngineVertex у sf::Vertex
    // Завдяки оптимізації компілятора (O2/Release) цей цикл виконується практично миттєво
    for (size_t i = 0; i < geometry.size(); ++i)
    {
        const auto& engVert = geometry[i];

        sfmlVertices[i].position.x = engVert.position.x;
        sfmlVertices[i].position.y = engVert.position.y;

        sfmlVertices[i].color.r = engVert.color.r;
        sfmlVertices[i].color.g = engVert.color.g;
        sfmlVertices[i].color.b = engVert.color.b;
        sfmlVertices[i].color.a = engVert.color.a;
    }

    m_window->draw(sfmlVertices);
}

void SFMLWindowProvider::displayAll()
{
    m_window->display();
}

void SFMLWindowProvider::updateFPS(const std::string& baseTitle, size_t renderedVerts, size_t totalVerts)
{
    float dt = m_fpsClock.restart().asSeconds();

    if (dt > 0.0f)
    {
        static float timeSinceLastUpdate = 0.0f;
        timeSinceLastUpdate += dt;

        // Оновлюємо заголовок кожні 0.5 секунди, щоб текст не "мерехтів"
        if (timeSinceLastUpdate >= 0.5f)
        {
            int fps = static_cast<int>(1.0f / dt);

            // Збільшуємо буфер, щоб вмістити всі нові дані
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "%s | FPS: %d | Verts: %zu / %zu",
                baseTitle.c_str(), fps, renderedVerts, totalVerts);

            m_window->setTitle(buffer);
            timeSinceLastUpdate = 0.0f;
        }
    }
}

// =======================================================================
// ОБРОБКА ПОДІЙ
// =======================================================================

void SFMLWindowProvider::pollEvents(std::vector<EngineEvent>& outEvents)
{
    outEvents.clear();

    // EN: Local event structure. Extremely fast, zero heap allocation.
    // UA: Локальна структура події. Вкрай швидка, нульова алокація в купі.
    sf::Event ev;

    // 1. ОБРОБКА ДИСКРЕТНИХ ПОДІЙ ВІКНА
    while (m_window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;

        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) {
                m_window->close();
            }
            break;

        case sf::Event::MouseWheelScrolled:
            if (ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                // emplace_back конструює об'єкт одразу в пам'яті вектора
                outEvents.emplace_back(EngineKey::MouseScroll, 0.0f, ev.mouseWheelScroll.delta);
            }
            break;

        default:
            break;
        }
    }

    // 2. ОБРОБКА БЕЗПЕРЕРВНОГО ВВОДУ (Клавіатура)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) outEvents.emplace_back(EngineKey::W);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) outEvents.emplace_back(EngineKey::A);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) outEvents.emplace_back(EngineKey::S);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) outEvents.emplace_back(EngineKey::D);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) outEvents.emplace_back(EngineKey::Space);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) outEvents.emplace_back(EngineKey::LShift);

    // 3. ОБРОБКА БЕЗПЕРЕРВНОГО ВВОДУ (Миша - Drag)
    static sf::Vector2i lastMousePos = sf::Mouse::getPosition(*m_window);
    sf::Vector2i currentMousePos = sf::Mouse::getPosition(*m_window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        float dX = static_cast<float>(currentMousePos.x - lastMousePos.x);
        float dY = static_cast<float>(currentMousePos.y - lastMousePos.y);

        if (dX != 0.0f || dY != 0.0f) {
            outEvents.emplace_back(EngineKey::MouseDrag, dX, dY);
        }
    }

    lastMousePos = currentMousePos;
}