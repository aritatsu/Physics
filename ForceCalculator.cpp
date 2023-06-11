#include "ForceCalculator.h"

namespace myfx
{
//-----------------------------------------------------------------------------
glm::vec3 ForceCalculator::getImpulse(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data)
{
	// この関数が呼ばれている時点で、body1とbody2が衝突していることを想定している
	if (!collision_data.mIsColliding)
	{
		return glm::vec3{ 0.f, 0.f, 0.f };
	}

	const auto collision_point = collision_data.mTangent;
	const auto e = body1->getRestitution() * body2->getRestitution();
	const auto m1inv = body1->getMassInverse();
	const auto m2inv = body2->getMassInverse();
	const auto Inv1 = body1->getMomentofInertiaInverse();
	const auto Inv2 = body2->getMomentofInertiaInverse();
	const auto r1 = collision_point - body1->getPosition();
	const auto r2 = collision_point - body2->getPosition();
	const auto n = collision_data.mNormal;
	const auto v1 = body1->getVelcoity() + glm::cross(body1->getAngularVelocity(), r1);
	const auto v2 = body2->getVelcoity() + glm::cross(body2->getAngularVelocity(), r2);
	const auto v12 = v2 - v1;

	const auto impulse =
		(1.f + e) * glm::dot(v12, n) /
		(glm::dot((m1inv + m2inv) * n + glm::cross(Inv1 * glm::cross(r1, n), r1) + glm::cross(Inv2 * glm::cross(r2, n), r2), n));

	return impulse * n;
}

glm::vec3 ForceCalculator::getFrictionForce(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data, const glm::vec3& normal_force)
{
	// この関数が呼ばれている時点で、body1とbody2が衝突していることを想定している
	if (!collision_data.mIsColliding)
	{
		return glm::vec3{ 0.f, 0.f, 0.f };
	}
	const auto collision_point = collision_data.mTangent;
	const auto r1 = collision_point - body1->getPosition();
	const auto r2 = collision_point - body2->getPosition();
	const auto n = collision_data.mNormal;
	const auto v1 = body1->getVelcoity() + glm::cross(body1->getAngularVelocity(), r1);
	const auto v2 = body2->getVelcoity() + glm::cross(body2->getAngularVelocity(), r2);
	const auto v12 = v2 - v1;
	const auto mu = body1->getFriction() * body2->getFriction();
	auto dir = v12 - glm::dot(v12, n) * n;
	if (glm::length(dir) >= 0.01f)
	{
		dir = glm::normalize(dir);
	}
	const auto friction = dir * glm::length(normal_force) * mu;
	//const auto dir = v12 - glm::dot(v12, n) * n;
	//const auto friction = dir * glm::length(normal_force) * mu * 0.1f;
	return friction;
}
}