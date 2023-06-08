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
	const auto m1inv = body1->getMass() ? 1.f / body1->getMass() : 0.f;
	const auto m2inv = body2->getMass() ? 1.f / body2->getMass() : 0.f;
	const auto Inv1 = body1->getMomentofInertia() != glm::mat3{ 0.f } ? glm::inverse(body1->getMomentofInertia()) : glm::mat3{ 0.f };
	const auto Inv2 = body2->getMomentofInertia() != glm::mat3{ 0.f } ? glm::inverse(body2->getMomentofInertia()) : glm::mat3{ 0.f };
	const auto r1 = collision_point - body1->getPosition();
	const auto r2 = collision_point - body2->getPosition();
	const auto n = collision_data.mNormal;
	const auto v1 = body1->getVelcoity() + glm::cross(r1, body1->getAngularVelcoity());
	const auto v2 = body2->getVelcoity() + glm::cross(r2, body2->getAngularVelcoity());
	const auto v12 = v2 - v1;

	const auto impulse =
		(1.f + e) * glm::dot(v12, n) /
		((m1inv + m2inv) * n +
			glm::cross(Inv1 * glm::cross(r1, n), r1) +
			glm::cross(Inv2 * glm::cross(r2, n), r2)
			);

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
	const auto v1 = body1->getVelcoity() + glm::cross(r1, body1->getAngularVelcoity());
	const auto v2 = body2->getVelcoity() + glm::cross(r2, body2->getAngularVelcoity());
	const auto v12 = v2 - v1;
	const auto mu = body1->getFriction() * body2->getFriction();
	const auto dir = glm::normalize(v12 - glm::dot(v12, n) * n);
	return dir * glm::length(normal_force) * mu;
}
}