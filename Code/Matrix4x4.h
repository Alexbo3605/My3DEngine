#pragma once


#include "Vector3f.h"
#include <vector>
using Vector4x4 = std::vector<std::vector<float>>;

class Matrix4x4
{
	

public:
	Matrix4x4();
	Matrix4x4(const Vector4x4& v);
	Matrix4x4(Vector4x4&& other_matrix) noexcept;

	Matrix4x4(const Matrix4x4& other) = default;
	
	~Matrix4x4(void);
	

	//отримання матриці прекції
	static Matrix4x4 getProjectionMatrix(
		const int width = 1920,
		const int height = 1080,
		const float zNear = 0.1,
		const float zFar = 1000,
		const float FOV = 90);

	//матриці ротації
	static Matrix4x4 getRotationX(const float angle);
	static Matrix4x4 getRotationY(const float angle);
	static Matrix4x4 getRotationZ(const float angle);

	// Оператори присвоєння (копіювання та переміщення)
	Matrix4x4& operator=(const Matrix4x4& other);
	Matrix4x4& operator=(Matrix4x4&& other) noexcept;


	friend Vector3f operator * (const Vector3f& v1, const Matrix4x4& m1);


	
private:
	Vector4x4 cords;
	
};
