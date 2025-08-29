#pragma once
#include "Triangle.h"

//���� �������(����) 3� ����� ���� ������ ������� (��� ����������) �� � ��������

class Mesh
{
public:

	Mesh(); // call ==> define_as_cube();
	Mesh(const std::vector<Triangle>& trianglesVector);

	bool serialize();

private:
	std::vector<Triangle> trianglesVector; //�� ���������

	void define_as_cube();



	
};

