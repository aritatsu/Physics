#include "Transform.h"

namespace myfx
{
//-------------------------------------------------------------------------
Transform::Transform()
	: mPosition{ 0.f }
	, mRotation{ 1.f }
{}

//-------------------------------------------------------------------------
Transform& Transform::operator=(const Transform& transform)
{
	mPosition = transform.mPosition;
	mRotation = transform.mRotation;
	return *this;
}
	
#if 0
/*!
	*	アフィン行列を取得する
	*/
const glm::mat4& Transform::getTranslationRotationMatrix() const
{
	glm::mat4 mtx(1.f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mtx[i][j] = mRotation[i][j];
		}
	}
	for (int j = 0; j < 3; j++)
	{
		mtx[3][j] = mPosition[j];
	}
	return mtx;
}
#endif
	
/*!
	*	4x4行列を描画する
	*/
void Print(glm::mat4 m)
{
	printf("matrix4x4 : \n");
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			printf("%.2f\t", m[i][j]);
		}
		printf("\n");
	}
}
	
/*!
	*	3x3行列を描画する
	*/
void Print(glm::mat3 m)
{
	printf("matrix3x3 : \n");
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			printf("%.2f\t", m[i][j]);
		}
		printf("\n");
	}
}
	
/*!
	*	4次元ベクトルを出力
	*/
void Print(const glm::vec4& v)
{
	printf("vec4 : \n");
	for (int i = 0; i < 4; i++)
	{
		printf("%.2f\n", v[i]);
	}
}
	
/*!
	*	3次元ベクトルを出力
	*/
void Print(const glm::vec3& v)
{
	printf("vec3 : \n");
	for (int i = 0; i < 3; i++)
	{
		printf("%.2f\n", v[i]);
	}
}

}