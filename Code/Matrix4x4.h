#pragma once


#include "Vector3f.h"
#include <vector>

using Vector4x4 = std::vector<std::vector<float>>;

class Matrix4x4
{

public:

	Matrix4x4(const Vector4x4& v = Vector4x4(4, std::vector<float>(4, 0.0f)) );
	Matrix4x4(Vector4x4&& v) noexcept;
	
	virtual ~Matrix4x4();
	

	// Оператори присвоєння (копіювання та переміщення)
	Matrix4x4& operator=(const Matrix4x4& other);
	Matrix4x4& operator=(Matrix4x4&& other) noexcept;


	//оце крашить мало розумію чому
	friend Vector3f operator * (const Vector3f& v1, const Matrix4x4& m1);


	Vector4x4 cords;
private:

	
};
