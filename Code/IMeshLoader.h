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

#include <string>

 // EN: Forward declaration to minimize include dependencies.
 // UA: Випереджаюче оголошення для мінімізації залежностей.
class Mesh;

/**
 * Description:
 * EN: Abstract interface for loading 3D model data from various file formats (.obj, .glb, etc.).
 * UA: Абстрактний інтерфейс для завантаження даних 3D моделей з різних форматів файлів (.obj, .glb тощо).
 */
class IMeshLoader
{
public:
    virtual ~IMeshLoader() = default;

    /**
     * Description:
     * EN: Parses a file and populates the provided Mesh object.
     * UA: Парсить файл та заповнює наданий об'єкт Mesh.
     *
     * Arguments:
     * filePath (I) - EN: Path to the 3D model file | UA: Шлях до файлу 3D моделі
     * outMesh  (O) - EN: Target mesh to populate   | UA: Цільова сітка для заповнення
     *
     * Returns:
     * EN: True if loading was successful, false otherwise.
     * UA: True, якщо завантаження було успішним, інакше false.
     */
    [[nodiscard]] virtual bool load(const std::string& filePath, Mesh& outMesh) = 0;
};