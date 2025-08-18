#include "Application.h"


//                   //
//    �Ͳֲ�˲��ֲ�  //
//                   // 
void Application::initVariables()
{
	this->window = nullptr;
}

void Application::initWindow()
{
	sf::VideoMode videoMode;
	sf::ContextSettings settings;   // ������� ����������

	videoMode.height = 800;  // ����� ��� ����� �� !!!!!
	videoMode.width = 1000;


	settings.antialiasingLevel = antialiasingLevel;

	this->window = new sf::RenderWindow(videoMode, "Application", sf::Style::Titlebar | sf::Style::Close, settings);
	this->window->setFramerateLimit(FPS);

}

/// ///////////////////////////////////////////////////////////////////////////////////
Application::Application()
{
	this->initVariables();
	this->initWindow();
}

Application::~Application() {
	delete this->window;
}

const bool Application::isRunning() const
{
	return this->window->isOpen();
}

const int Application::run() 
{
	while (this->isRunning()) {
	
		this->update();
		this->render();
	}
	return 0;
}


void Application::update() //��������� ������
{
	this->pollEvents(); //���������� �� ��䳿

}

//                      //
//    ��������� ��Ĳ�   //
//                      // 
void Application::pollEvents() //������� ����
{
	while (this->window->pollEvent(this->ev)) //���� � ��䳿
	{
		if (this->ev.type == sf::Event::Closed)//�������� �����
		{
			this->window->close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

		}
		
	}
}

//                //
//    ���������   //
//                // 



//                  //
//    ²���������   //
//                  // 
void Application::renderAll()
{
	//this->window->draw(*aaaaa);
}



void Application::render() //���������� ����
{
	this->window->clear();

	this->renderAll();

	this->window->display();
}


