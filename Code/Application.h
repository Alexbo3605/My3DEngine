#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <stack>
#include <iostream>


class Application
{
private:


	//деякі з цих параметрів після ініту не використовуються та жеруть пам'ять
	sf::RenderWindow* window;

	sf::Event ev; // мб зробити поінтером або смартпоінтером


	const bool isRunning() const;

	// initialization
	void initVariables();
	void initWindow();

	//update
	void update();
	void pollEvents();

	//render
	void renderAll();
	void render();  //один з рендерыз зробити не видимим



;

	//dependencies

	const int FPS = 30;
	const unsigned int antialiasingLevel = 5;

	const sf::Color fillColorVoid = sf::Color(0, 0, 0, 0);


public:
	Application();
	virtual ~Application();

	const int run();
	
};

