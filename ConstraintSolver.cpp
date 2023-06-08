// header file
#include "ConstraintSolver.h"

namespace myfx
{
//-----------------------------------------------------------------------------
void ConstraintSolver::solveConstraint(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data)
{
	// この関数が呼ばれている時点で、body1とbody2が衝突していることを想定している
	if (!collision_data.mIsColliding)
	{
		return;
	}

	if (body1->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeSphere && body2->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeCube)
	{
		// PhysicsDispatcherクラスがbody1に直方体を、body2に球を割り当てているはずである。
		assert(false);
	}

	if (body1->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeCube && body2->getCollisionShape()->getShapeType() == ShapeType::ShapeTypeSphere)
	{
		const auto radius = dynamic_cast<SphereShape*>(body2->getCollisionShape())->getRadius();
		const auto sphere_shift = -collision_data.mNormal * (glm::dot(collision_data.mNormal, body2->getPosition() - collision_data.mTangent) - radius);

		if (body1->getMass() && body2->getMass())
		{
			body1->setPosition(body1->getPosition() - sphere_shift / 2.f);
			body2->setPosition(body2->getPosition() + sphere_shift / 2.f);
		}

		else if (body1->getMass() && !body2->getMass())
		{
			body1->setPosition(body1->getPosition() - sphere_shift);
		}

		else if (!body1->getMass() && body2->getMass())
		{
			body2->setPosition(body2->getPosition() + sphere_shift);
		}
	}
}

}