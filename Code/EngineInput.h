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

 /**
  * Description:
  * EN: Engine-agnostic key codes for hardware input abstraction.
  */
enum class EngineKey
{
    Unknown = 0,
    W, A, S, D,
    Space, LShift,
    MouseDrag,   // EN: Mouse movement with left button pressed 
    MouseScroll  // EN: Vertical mouse wheel scroll
};

/**
 * Description:
 * EN: Structure representing a single user input event, carrying optional payload data like mouse deltas.
 */
struct EngineEvent
{
    EngineKey type{ EngineKey::Unknown };

    // EN: Optional data payload for mouse events.
    float deltaX{ 0.0f };
    float deltaY{ 0.0f };

    /**
     * Description:
     * EN: Constructor for simple key press events.
     */
    explicit constexpr EngineEvent(EngineKey t) noexcept
        : type(t)
    {
    }

    /**
     * Description:
     * EN: Constructor for complex events (like mouse input) that require delta values.
     */
    constexpr EngineEvent(EngineKey t, float dx, float dy) noexcept
        : type(t), deltaX(dx), deltaY(dy)
    {
    }
};