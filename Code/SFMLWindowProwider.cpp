#include "SFMLWindowProwider.h"

//                   //
//    ������������   //
//                   // 
SFMLWindowProwider::SFMLWindowProwider()
{
	this->initVariables();
	this->initWindow();
}
SFMLWindowProwider::~SFMLWindowProwider(void)
{
	delete this->window;
}

//                   //
//    �Ͳֲ�˲��ֲ�  //
//                   // 
void SFMLWindowProwider::initVariables()
{
	this->window = nullptr;
}


void SFMLWindowProwider::initWindow()
{
	sf::VideoMode videoMode;
	sf::ContextSettings settings;   // ������� ����������

	videoMode.height = WindowSettings::windowHeight;  // ����� ��� ����� �� !!!!!
	videoMode.width = WindowSettings::windowWidth;
	settings.antialiasingLevel = WindowSettings::antialiasingLevel;

	this->window = new sf::RenderWindow(videoMode, WindowSettings::windowName, sf::Style::Titlebar | sf::Style::Close, settings);
	this->window->setFramerateLimit(WindowSettings::FPS);

}

const bool SFMLWindowProwider::isRunning() const
{
	return this->window->isOpen();
}

/// ///////////////////////////////////////////////////////////////////////////////////

const int SFMLWindowProwider::runWindow()
{
	while (this->isRunning()) {

		this->update();
		this->render();
	}
	return 0;
}


void SFMLWindowProwider::update() //��������� ������
{
	this->pollEvents(); //���������� �� ��䳿

}

//                      //
//    ��������� ��Ĳ�   //
//                      // 
void SFMLWindowProwider::pollEvents() //������� ����
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
void SFMLWindowProwider::renderAll()
{
	//this->window->draw(*aaaaa);
}



void SFMLWindowProwider::render() //���������� ����
{
	this->window->clear();

	this->renderAll();

	this->window->display();
}


