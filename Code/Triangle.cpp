#include "Triangle.h"

Triangle::Triangle()
    : trianglePoints() {
}

Triangle::Triangle(std::vector<Vector3f> vertices) : trianglePoints(std::move(vertices))
{}


Triangle::Triangle(const Vector3f& v1, const Vector3f& v2, const Vector3f& v3) : trianglePoints( {v1,v2,v3} ) 
{}



Triangle::~Triangle(void) {}
