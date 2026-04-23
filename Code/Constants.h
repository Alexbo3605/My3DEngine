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
  * Global engine configuration constants.
  */
namespace constants {

    // ==========================================
    // Math
    // ==========================================
    constexpr float kPi = 3.1415926535f;

    // ==========================================
    // Screen / Window
    // ==========================================
    constexpr int kWidth = 1920;
    constexpr int kHeight = 1080;

    // ==========================================
    // Camera & Projection
    // ==========================================
    constexpr float kZNear = 0.1f;
    constexpr float kZFar = 1000.0f;
    constexpr float kFov = 90.0f;

    // ==========================================
    // Input / Controls
    // ==========================================
    constexpr float kMouseSensitivity = 0.007f;
    constexpr float kZoomSpeed = 0.2f;

}