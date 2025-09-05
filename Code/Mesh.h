#pragma once
#include "Triangle.h"

//клас каркасу(сітки) 3Д обєкта буде містити вершини (або трикутрики) мб і матерали





class Mesh
{
public:

	Mesh(const std::vector<Triangle>& trianglesVector);
	Mesh(const int readWith = 1); //call ==> define_as_cube();
	~Mesh(void);

	

private:
	std::vector<Triangle> trianglesVector; //мб вказівники

	bool serialize(const int readWith);

	void define_as_cube();



	
};

