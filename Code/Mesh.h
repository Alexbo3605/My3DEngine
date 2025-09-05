#pragma once
#include "Triangle.h"

//���� �������(����) 3� ����� ���� ������ ������� (��� ����������) �� � ��������





class Mesh
{
public:

	Mesh(const std::vector<Triangle>& trianglesVector);
	Mesh(const int readWith = 1); //call ==> define_as_cube();
	~Mesh(void);

	

private:
	std::vector<Triangle> trianglesVector; //�� ���������

	bool serialize(const int readWith);

	void define_as_cube();



	
};

