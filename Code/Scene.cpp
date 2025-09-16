#include "Scene.h"

Scene::Scene()
{
}


void Scene::addObject(std::unique_ptr<Object3D> object) {
    objects.push_back(std::move(object));
}

void Scene::render() {

    
    // отут або передавати дані в Sfml provider або 
    // писати логіку в ручну

}