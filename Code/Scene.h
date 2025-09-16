#pragma once
#include "Object3D.h"

#include <memory>

class Scene
{
public:


	Scene();
	void render();

private:
	std::vector<std::unique_ptr<Object3D>> objects;

	void addObject(std::unique_ptr<Object3D> object);

};


