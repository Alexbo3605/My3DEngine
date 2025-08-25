#pragma once
#include "IWindowProwider.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <stack>
#include <iostream>

class SFMLWindowProwider : public IWindowProwider
{
public:
	SFMLWindowProwider();
	virtual ~SFMLWindowProwider(void);

	virtual const int runWindow() override;

private:
	virtual const bool isRunning() const override;

	// initialization
	void initVariables();
	virtual void initWindow() override;

	//update
	void update();
	void pollEvents();

	//render
	void renderAll();
	void render();  //один з рендерыз зробити не видимим


	//деякі з цих параметрів після ініту не використовуються та жеруть пам'ять
	sf::RenderWindow* window;

	sf::Event ev; // мб зробити поінтером або смартпоінтером
};

