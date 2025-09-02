#pragma once

#include "SFMLWindowProwider.h"
//#include "GLFWWindowProwider.h" ������� ������� ����������
#include "Object3D.h"


//������ � ����������� �������� ��� �� �� ���� ����
enum {
	CREATE_WITH_DEFAULT = 1,
	CREATE_WITH_OBJ = 2,
	CREATE_WITH_GLB = 3

};


class Application
{
public:
	Application();
	~Application(void);

	void run();

private:

	Object3D* obj;

};

