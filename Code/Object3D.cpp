#include "Object3D.h"


Object3D::Object3D(const int fileType, const int materialType) {

	this->pMash = new Mesh(fileType);

	//this->pMaterial = new ........;
	//this->pLight = new .....;

}

Object3D::~Object3D(void)
{
	delete this->pMash;

	//delete this->pMaterial;
	//delete this->pLight;
}
