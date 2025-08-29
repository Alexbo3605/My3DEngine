#pragma once
#include "Triangle.h"

//клас каркасу(сітки) 3Д обєкта буде містити вершини (або трикутрики) мб і матерали

class Mesh
{
public:

	Mesh(); // call ==> define_as_cube();
	Mesh(const std::vector<Triangle>& trianglesVector);

	bool serialize();

private:
	std::vector<Triangle> trianglesVector; //мб вказівники

	void define_as_cube();



	
};

