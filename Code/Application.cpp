#include "Application.h"


Application::Application()
{
	this->obj = new Object3D(CREATE_WITH_DEFAULT, 1);
}

Application::~Application(void)
{
	delete this->obj;
}


void Application::run() 
{
	SFMLWindowProwider app;

	app.runWindow();
}