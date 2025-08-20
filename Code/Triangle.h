#pragma once
#include <memory>
#include <vector>
#include "Vector3f.h"  

class Triangle
{
private:
    std::vector<std::unique_ptr<Vector3f>> trianglePoints;
    std::unique_ptr<Vector3f> normal;

public:
    Triangle();
    Triangle(std::vector<std::unique_ptr<Vector3f>>&& trianglePoints);
    Triangle(std::unique_ptr<Vector3f>&& t1,
        std::unique_ptr<Vector3f>&& t2,
        std::unique_ptr<Vector3f>&& t3);

    virtual ~Triangle(void);

    // TODO: реалізувати кліпінг
};
