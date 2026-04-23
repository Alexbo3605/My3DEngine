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


#include "ObjLoader.h"
#include "Mesh.h"


#include <fstream>
#include <sstream>
#include <iostream>
#include <charconv> // Для std::from_chars (швидкий парсинг)

 // ==========================================
 // Внутрішні структури для дедуплікації
 // ==========================================

struct ObjIndex {
    int v{ 0 }, vt{ 0 }, vn{ 0 };

    bool operator==(const ObjIndex& other) const {
        return v == other.v && vt == other.vt && vn == other.vn;
    }
};

struct ObjIndexHash {
    std::size_t operator()(const ObjIndex& k) const {
        // Швидка хеш-функція за допомогою побітових зсувів
        return ((std::hash<int>()(k.v) ^ (std::hash<int>()(k.vt) << 1)) >> 1) ^ (std::hash<int>()(k.vn) << 1);
    }
};

// ==========================================
// Реалізація
// ==========================================

bool ObjLoader::load(const std::string& filepath, Mesh& outMesh)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "[ObjLoader] Failed to open file: " << filepath << '\n';
        return false;
    }

    // Резервуємо базову кількість пам'яті для зменшення реалокацій
    std::vector<Vector3f> tempPositions; tempPositions.reserve(10000);
    std::vector<Vector2f> tempUVs;       tempUVs.reserve(10000);
    std::vector<Vector3f> tempNormals;   tempNormals.reserve(10000);

    std::unordered_map<ObjIndex, uint32_t, ObjIndexHash> uniqueVertices;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream stream(line);
        std::string prefix;
        stream >> prefix;

        if (prefix == "v") {
            parseVertex(stream, tempPositions);
        }
        else if (prefix == "vt") {
            parseTexCoord(stream, tempUVs);
        }
        else if (prefix == "vn") {
            parseNormal(stream, tempNormals);
        }
        else if (prefix == "f") {
            parseFace(stream, tempPositions, tempUVs, tempNormals, uniqueVertices, outMesh);
        }
    }

    file.close();
    return true;
}

void ObjLoader::parseVertex(std::istringstream& stream, std::vector<Vector3f>& tempPositions)
{
    Vector3f vertex(0.0f);
    stream >> vertex.x >> vertex.y >> vertex.z;
    tempPositions.push_back(vertex);
}

void ObjLoader::parseTexCoord(std::istringstream& stream, std::vector<Vector2f>& tempUVs)
{
    Vector2f uv(0.0f, 0.0f);
    stream >> uv.x >> uv.y;
    // Часто в OBJ координата V перевернута. Розкоментуйте, якщо текстури догори дригом:
    // uv.y = 1.0f - uv.y;
    tempUVs.push_back(uv);
}

void ObjLoader::parseNormal(std::istringstream& stream, std::vector<Vector3f>& tempNormals)
{
    Vector3f normal(0.0f);
    stream >> normal.x >> normal.y >> normal.z;
    tempNormals.push_back(normal.normalize());
}

void ObjLoader::parseFace(std::istringstream& stream,
    const std::vector<Vector3f>& tempPositions,
    const std::vector<Vector2f>& tempUVs,
    const std::vector<Vector3f>& tempNormals,
    std::unordered_map<ObjIndex, uint32_t, ObjIndexHash>& uniqueVertices,
    Mesh& outMesh)
{
    std::string token;
    std::vector<uint32_t> faceIndices;
    faceIndices.reserve(4); // Зазвичай грані - це трикутники (3) або квади (4)

    auto resolveIndex = [](int index, size_t arraySize) -> int {
        if (index == 0) return 0;
        if (index < 0) return static_cast<int>(arraySize) + index;
        return index - 1;
        };

    // Швидкий парсер числа (без аллокацій підрядків)
    auto fastParseInt = [](std::string_view str) -> int {
        int val = 0;
        std::from_chars(str.data(), str.data() + str.size(), val);
        return val;
        };

    while (stream >> token)
    {
        ObjIndex objIdx;
        std::string_view tokenView(token);

        size_t firstSlash = tokenView.find('/');
        size_t secondSlash = (firstSlash == std::string_view::npos) ?
            std::string_view::npos : tokenView.find('/', firstSlash + 1);

        // 1. Вершина (v)
        objIdx.v = fastParseInt(tokenView.substr(0, firstSlash));

        // 2. Текстура (vt)
        if (firstSlash != std::string_view::npos && secondSlash != firstSlash + 1) {
            objIdx.vt = fastParseInt(tokenView.substr(firstSlash + 1, secondSlash - firstSlash - 1));
        }

        // 3. Нормаль (vn)
        if (secondSlash != std::string_view::npos) {
            objIdx.vn = fastParseInt(tokenView.substr(secondSlash + 1));
        }

        // Пошук дублікатів (дедуплікація)
        auto it = uniqueVertices.find(objIdx);

        if (it != uniqueVertices.end())
        {
            faceIndices.push_back(it->second);
        }
        else
        {
            int vIdx = resolveIndex(objIdx.v, tempPositions.size());
            int vtIdx = resolveIndex(objIdx.vt, tempUVs.size());
            int vnIdx = resolveIndex(objIdx.vn, tempNormals.size());

            Vector3f pos = (vIdx >= 0 && vIdx < tempPositions.size()) ? tempPositions[vIdx] : Vector3f(0.0f);
            Vector2f uv = (vtIdx >= 0 && vtIdx < tempUVs.size()) ? tempUVs[vtIdx] : Vector2f(0.0f, 0.0f);
            Vector3f normal = (vnIdx >= 0 && vnIdx < tempNormals.size()) ? tempNormals[vnIdx] : Vector3f(0.0f);

            outMesh.addVertexData(pos, uv, normal);

            uint32_t newIndex = outMesh.getVertexCount() - 1;
            uniqueVertices[objIdx] = newIndex;
            faceIndices.push_back(newIndex);
        }
    }

    // Тріангуляція (Triangle Fan Algorithm) для N-кутників
    if (faceIndices.size() >= 3)
    {
        for (size_t i = 1; i < faceIndices.size() - 1; ++i) {
            outMesh.addTriangle(faceIndices[0], faceIndices[i], faceIndices[i + 1]);
        }
    }
}