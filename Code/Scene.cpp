#include "Scene.h"

Scene::Scene()
{
}


void Scene::addObject(std::unique_ptr<Object3D> object) {
    objects.push_back(std::move(object));
}

void Scene::render() {

    
    // ���� ��� ���������� ��� � Sfml provider ��� 
    // ������ ����� � �����

}