#pragma once

#include "CollisionDetector.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// �Փˎ��̗͂��v�Z����N���X
class ForceCalculator
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	ForceCalculator() {}
	~ForceCalculator() {}

	// body1��body2����󂯎��͐ς�Ԃ�
	glm::vec3 getImpulse(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data);

	// body1��body2����󂯎�門�C�͂�Ԃ�
	glm::vec3 getFrictionForce(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data, const glm::vec3& normal_force);
};

}
