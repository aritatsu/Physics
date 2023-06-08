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
	*	�A�t�B���s����擾����
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
	*	4x4�s���`�悷��
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
	*	3x3�s���`�悷��
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
	*	4�����x�N�g�����o��
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
	*	3�����x�N�g�����o��
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