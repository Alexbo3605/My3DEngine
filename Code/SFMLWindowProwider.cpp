#include "SFMLWindowProwider.h"

//                   //
//    ÊÎÍÑÒĞÓÊÒÎĞÈ   //
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
//    ²Í²Ö²ÀË²ÇÀÖ²ß  //
//                   // 
void SFMLWindowProwider::initVariables()
{
	this->window = nullptr;
}


void SFMLWindowProwider::initWindow()
{
	sf::VideoMode videoMode;
	sf::ContextSettings settings;   // çğîáèòè ïîêğàñèâ³øå

	videoMode.height = WindowSettings::windowHeight;  // êğàùå ôóë åêğàí õç !!!!!
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


void SFMLWindowProwider::update() //îíîâëåííÿ ôğåéìó
{
	this->pollEvents(); //îáğîáëÿºìî âñ³ ïîä³¿

}

//                      //
//    ÑÒÂÎĞÅÍÍß ÏÎÄ²É   //
//                      // 
void SFMLWindowProwider::pollEvents() //îáğîáêà ïîä³é
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
void SFMLWindowProwider::renderAll()
{
	//this->window->draw(*aaaaa);
}



void SFMLWindowProwider::render() //â³äìàëüîâêà â³êíà
{
	this->window->clear();

	this->renderAll();

	this->window->display();
}


