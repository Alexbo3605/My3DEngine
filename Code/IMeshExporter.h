#pragma once

#include "Mesh.h"

// Інтерфейс для збереження (закладемо на майбутнє)
class IMeshExporter {
public:
    virtual ~IMeshExporter() = default;

    virtual bool save(const std::string& filepath, const Mesh& mesh) = 0;
};