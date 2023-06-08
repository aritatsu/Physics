#pragma once

#include <glm.hpp>

#include "CubeShape.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// AABB�N���X
class AABB
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	AABB();
	AABB(const glm::vec3& min, const glm::vec3& max);
	AABB(const CubeShape& cube);
	~AABB() {};

	//-------------------------------------------------------------------------
	// �����o�ϐ�
	glm::vec3	mMin;
	glm::vec3	mMax;

};

}