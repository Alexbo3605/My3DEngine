#pragma once
#include <memory>
#include <vector>
#include "Vector3f.h"  

class Triangle
{
private:
    std::vector<Vector3f> trianglePoints;
    Vector3f normal;

public:
    Triangle();
    Triangle(std::vector<Vector3f> vertices);
    /*Triangle(const std::vector<Vector3f>& vertices) Тоді без move */

    Triangle(const Vector3f& v1, const Vector3f& v2, const Vector3f& v3);

   

    virtual ~Triangle(void);

    // TODO: реалізувати кліпінг
};
