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

#include <array>

 /**
  * Description:
  * EN: Specific configuration settings for the window provider and rendering context.
  */
namespace WindowSettings {

    // ==========================================
    // Dimensions & Title
    // ==========================================
    constexpr int kWindowWidth = 1536;
    constexpr int kWindowHeight = 864;
    constexpr const char* kWindowName = "My3DEngine";

    // ==========================================
    // Rendering Options
    // ==========================================
    constexpr int kFpsLimit = 100000;
    constexpr int kAntialiasingLevel = 5;

    // ==========================================
    // Global Colors
    // ==========================================
    // EN: Default color definition (R, G, B, A).
    constexpr float kDefaultColor[4] = { 255.0f, 255.0f, 255.0f, 255.0f };

}