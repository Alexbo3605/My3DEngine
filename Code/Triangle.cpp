#include "Triangle.h"

Triangle::Triangle()
    : trianglePoints() {
}

Triangle::Triangle(std::vector<std::unique_ptr<Vector3f>>&& trianglePoints)
    : trianglePoints(std::move(trianglePoints)) {
}

Triangle::Triangle(std::unique_ptr<Vector3f>&& t1,
    std::unique_ptr<Vector3f>&& t2,
    std::unique_ptr<Vector3f>&& t3)
    : trianglePoints{}
{
    trianglePoints.push_back(std::move(t1));
    trianglePoints.push_back(std::move(t2));
    trianglePoints.push_back(std::move(t3));
}

Triangle::~Triangle(void) {}
