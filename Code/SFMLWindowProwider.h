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
	void render();  //���� � �������� ������� �� �������


	//���� � ��� ��������� ���� ���� �� ���������������� �� ������ ���'���
	sf::RenderWindow* window;

	sf::Event ev; // �� ������� �������� ��� �������������
};

