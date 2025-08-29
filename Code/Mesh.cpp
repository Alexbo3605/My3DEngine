#include "Mesh.h"

bool Mesh::serialize()
{


    return true;
}

//Mesh::Mesh() : trianglesVector(Triangle() ); короч пустий

Mesh::Mesh(const std::vector<Triangle>& trianglesVector) : trianglesVector(trianglesVector)
{}

void Mesh::define_as_cube()
{
    this->trianglesVector = {

        // SOUTH
        Triangle{ Vector3f(0.0f, 0.0f, 0.0f),    Vector3f(0.0f, 1.0f, 0.0f),    Vector3f(1.0f, 1.0f, 0.0f) },
        Triangle{ Vector3f(0.0f, 0.0f, 0.0f),    Vector3f(1.0f, 1.0f, 0.0f),    Vector3f(1.0f, 0.0f, 0.0f) },
        // EAST                                                                         
        Triangle(Vector3f(1.0f, 0.0f, 0.0f),    Vector3f(1.0f, 1.0f, 0.0f),    Vector3f(1.0f, 1.0f, 1.0f)),
        Triangle(Vector3f(1.0f, 0.0f, 0.0f),    Vector3f(1.0f, 1.0f, 1.0f),    Vector3f(1.0f, 0.0f, 1.0f)),
        // NORTH                                                                        
        Triangle(Vector3f(1.0f, 0.0f, 1.0f),    Vector3f(1.0f, 1.0f, 1.0f),    Vector3f(0.0f, 1.0f, 1.0f)),
        Triangle(Vector3f(1.0f, 0.0f, 1.0f),    Vector3f(0.0f, 1.0f, 1.0f),    Vector3f(0.0f, 0.0f, 1.0f)),
        // WEST                                                                         
        Triangle(Vector3f(0.0f, 0.0f, 1.0f),    Vector3f(0.0f, 1.0f, 1.0f),    Vector3f(0.0f, 1.0f, 0.0f)),
        Triangle(Vector3f(0.0f, 0.0f, 1.0f),    Vector3f(0.0f, 1.0f, 0.0f),    Vector3f(0.0f, 0.0f, 0.0f)),
        // TOP                                                                        
        Triangle(Vector3f(0.0f, 1.0f, 0.0f),    Vector3f(0.0f, 1.0f, 1.0f),    Vector3f(1.0f, 1.0f, 1.0f)),
        Triangle(Vector3f(0.0f, 1.0f, 0.0f),    Vector3f(1.0f, 1.0f, 1.0f),    Vector3f(1.0f, 1.0f, 0.0f)),
        // BOTTOM                                                                     
        Triangle(Vector3f(1.0f, 0.0f, 1.0f),    Vector3f(0.0f, 0.0f, 1.0f),    Vector3f(0.0f, 0.0f, 0.0f)),
        Triangle(Vector3f(1.0f, 0.0f, 1.0f),    Vector3f(0.0f, 0.0f, 0.0f),    Vector3f(1.0f, 0.0f, 0.0f)),
    };
}
