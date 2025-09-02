#pragma once
#include "Mesh.h"
// це екземпляр об'єкта в сцені. Це "конкретний" об'єкт,
// який має своє унікальне положення, поворот і масштаб.

// він і буде відображатися на екрані



class Object3D
{
public:
	Object3D(const int fileType = 1, const int materialType = 1); //змінити на енум
	~Object3D(void);

	//містить
	// Посилання на Mesh: Він "вказує" на конкретну сітку, яку потрібно відобразити.

	//Трансформації (Transformations): Позиція (Position) Поворот (Rotation) Масштаб (Scale)

	// Посилання на Material опціонно (покищо заглушка)
private:
	Mesh* pMash;  //мб створюваи у stack замість heap буде швидше але переповнення може бути

	//Meterial* pMaterial;
	//Light* pLight;



};

