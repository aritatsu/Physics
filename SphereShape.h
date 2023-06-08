#pragma once
#include "ICollisionShape.h"

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// ���`��N���X
class SphereShape : public ICollisionShape
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	SphereShape(glm::f32 radius = 1.f);
	~SphereShape() {};

	// �}�`�̌^���擾����
	ShapeType getShapeType() const override
	{
		return ShapeTypeSphere;
	}

	// ���̔��a���擾����
	glm::f32 getRadius() const
	{
		return mRadius;
	}

private:
	glm::f32 mRadius;
};

}


