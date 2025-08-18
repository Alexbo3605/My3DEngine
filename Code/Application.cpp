#include "Application.h"


//                   //
//    ²Í²Ö²ÀË²ÇÀÖ²ß  //
//                   // 
void Application::initVariables()
{
	this->window = nullptr;
}

void Application::initWindow()
{
	sf::VideoMode videoMode;
	sf::ContextSettings settings;   // çğîáèòè ïîêğàñèâ³øå

	videoMode.height = 800;  // êğàùå ôóë åêğàí õç !!!!!
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


void Application::update() //îíîâëåííÿ ôğåéìó
{
	this->pollEvents(); //îáğîáëÿºìî âñ³ ïîä³¿

}

//                      //
//    ÑÒÂÎĞÅÍÍß ÏÎÄ²É   //
//                      // 
void Application::pollEvents() //îáğîáêà ïîä³é
{
	while (this->window->pollEvent(this->ev)) //ïîêè º ïîä³¿
	{
		if (this->ev.type == sf::Event::Closed)//çàêğèòòÿ â³êííà
		{
			this->window->close();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

		}
		
	}
}

//                //
//    ÎÍÎÂËÅÍÍß   //
//                // 



//                  //
//    Â²ÄÌÀËÜÎÂÊÀ   //
//                  // 
void Application::renderAll()
{
	//this->window->draw(*aaaaa);
}



void Application::render() //â³äìàëüîâêà â³êíà
{
	this->window->clear();

	this->renderAll();

	this->window->display();
}


