#pragma once
#pragma once

#include <cstdint>
#include "TVector.h" // Потрібен для Vector2f

// ==========================================
// Незалежні від платформи типи для рендеру
// ==========================================

 /**
  * Description:
  * EN: Engine-agnostic color structure (RGBA, 1 byte per channel).
  * UA: Незалежна від рушія структура кольору (RGBA, 1 байт на канал).
  */
struct EngineColor {
    uint8_t r{ 255 }, g{ 255 }, b{ 255 }, a{ 255 };
};


/**
 * Description:
 * EN: Final 2D vertex structure ready for screen-space rasterization by the Window Provider.
 * UA: Фінальна 2D вершина, готова до растеризації в екранному просторі через Window Provider.
 */
struct EngineVertex {
    Vector2f position;
    EngineColor color;
};