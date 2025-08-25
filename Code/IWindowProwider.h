#pragma once
#include "WindowSettings.h"

class IWindowProwider
{
public:
	//выкна створюються у конструкторах тому метод не потрыбен
	virtual const int runWindow() = 0;


	IWindowProwider(void);
	virtual ~IWindowProwider(void);

private:
	
	virtual void initWindow() = 0;
	virtual const bool isRunning() const = 0;

};

