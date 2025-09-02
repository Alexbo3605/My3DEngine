#include "Mesh.h"

Mesh::Mesh(const std::vector<Triangle>& trianglesVector) : trianglesVector(trianglesVector)
{}

Mesh::Mesh(const int readWith)
{
    if (!this->serialize(readWith)) {
        //ok
    
    }
    else {
        //error throw ReadError(id) ;
    }


}

Mesh::~Mesh(void)
{}



bool Mesh::serialize(const int readWith)
{


    return true;
}

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
