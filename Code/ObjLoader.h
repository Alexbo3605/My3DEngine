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

#include "IMeshLoader.h"
#include "TVector.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iosfwd> // Forward declaration для std::istringstream

 // Forward declaration
class Mesh;
struct ObjIndex;
struct ObjIndexHash;

/**
 * Description:
 * EN: Parses Wavefront .obj files and populates a Mesh object. Handles vertex deduplication and n-gon triangulation.
 */
class ObjLoader final : public IMeshLoader
{
public:
    ObjLoader() = default;
    ~ObjLoader() override = default;

    [[nodiscard]] bool load(const std::string& filepath, Mesh& outMesh) override;

private:
    void parseVertex(std::istringstream& stream, std::vector<Vector3f>& tempPositions);
    void parseTexCoord(std::istringstream& stream, std::vector<Vector2f>& tempUVs);
    void parseNormal(std::istringstream& stream, std::vector<Vector3f>& tempNormals);

    void parseFace(std::istringstream& stream,
        const std::vector<Vector3f>& tempPositions,
        const std::vector<Vector2f>& tempUVs,
        const std::vector<Vector3f>& tempNormals,
        std::unordered_map<ObjIndex, uint32_t, ObjIndexHash>& uniqueVertices,
        Mesh& outMesh
    );
};