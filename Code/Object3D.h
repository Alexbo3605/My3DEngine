#pragma once
#include "Mesh.h"
// �� ��������� ��'���� � ����. �� "����������" ��'���,
// ���� �� ��� �������� ���������, ������� � �������.

// �� � ���� ������������ �� �����



class Object3D
{
public:
	Object3D(const int fileType = 1, const int materialType = 1); //������ �� ����
	~Object3D(void);

	//������
	// ��������� �� Mesh: ³� "�����" �� ��������� ����, ��� ������� ����������.

	//������������� (Transformations): ������� (Position) ������� (Rotation) ������� (Scale)

	// ��������� �� Material �������� (������ ��������)
private:
	Mesh* pMash;  //�� ��������� � stack ������ heap ���� ������ ��� ������������ ���� ����

	//Meterial* pMaterial;
	//Light* pLight;



};

