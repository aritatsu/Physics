#pragma once

// Collision Data
#include "CollisionDetector.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// �S�������N���X
class ConstraintSolver
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	ConstraintSolver() {};
	~ConstraintSolver() {};

	// �S������������
	void solveConstraint(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data);
};

}
