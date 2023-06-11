// header file
#include "ConstraintSolver.h"

namespace myfx
{
//-----------------------------------------------------------------------------
void ConstraintSolver::solveConstraint(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data)
{
	// ���̊֐����Ă΂�Ă��鎞�_�ŁAbody1��body2���Փ˂��Ă��邱�Ƃ�z�肵�Ă���
	if (!collision_data.mIsColliding)
	{
		return;
	}

	if (body1->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeSphere && body2->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeCube)
	{
		// PhysicsDispatcher�N���X��body1�ɒ����̂��Abody2�ɋ������蓖�ĂĂ���͂��ł���B
		assert(false);
	}

	if (body1->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeCube && body2->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeSphere)
	{
		const auto radius = dynamic_cast<SphereShape*>(body2->getCollisionShape())->getRadius();
		const auto box_shift = collision_data.mNormal * (radius - glm::dot(collision_data.mNormal, collision_data.mTangent - body2->getPosition()));

		if (body1->getMass() && body2->getMass())
		{
			body1->setPosition(body1->getPosition() + box_shift / 2.f);
			body2->setPosition(body2->getPosition() - box_shift / 2.f);
		}

		else if (body1->getMass() && !body2->getMass())
		{
			body1->setPosition(body1->getPosition() + box_shift);
		}

		else if (!body1->getMass() && body2->getMass())
		{
			body2->setPosition(body2->getPosition() - box_shift);
		}
	}
}

}