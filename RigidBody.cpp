#include "RigidBody.h"

#include "CubeShape.h"
#include "SphereShape.h"

#include <gtx/rotate_vector.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
RigidBody::RigidBody()
	: mInertia			{ }
	, mPower			{ }
	, mTransform		{ }
	, mMotion			{ }
	, mCollisionSpape	{ nullptr }
	, mRestitution		{ 1.f }
	, mFriction			{ 1.f }
{}

//-----------------------------------------------------------------------------
RigidBody::RigidBody(const RigidBody& body)
	: mInertia			{ body.mInertia }
	, mPower			{ body.mPower }
	, mTransform		{ body.mTransform }
	, mMotion			{ body.mMotion }
	, mCollisionSpape	{ body.mCollisionSpape }
	, mRestitution		{ body.mRestitution }
	, mFriction			{ body.mFriction }
{}

//-----------------------------------------------------------------------------
RigidBody& RigidBody::operator=(const RigidBody& body)
{
	mInertia = body.mInertia;
	mPower = body.mPower;
	mTransform = body.mTransform;
	mMotion = body.mMotion;
	mCollisionSpape = body.mCollisionSpape;
	mRestitution = body.mRestitution;
	mFriction = body.mFriction;
	return *this;
}

//-----------------------------------------------------------------------------
void RigidBody::updateMomentofInertia()
{
	if (mCollisionSpape->getShapeType() == ShapeType::ShapeTypeCube)
	{
		const auto scale = dynamic_cast<CubeShape*>(mCollisionSpape)->getScale();
		const auto moment_of_inertia = glm::mat3
		{
			(scale.y * scale.y + scale.z * scale.z) * getMass() / 12.f, 0.f, 0.f,
			0.f, (scale.z * scale.z + scale.x * scale.x) * getMass() / 12.f, 0.f,
			0.f, 0.f, (scale.x * scale.x + scale.y * scale.y) * getMass() / 12.f,
		};
		setMomentofInertia(moment_of_inertia);
	}

	if (mCollisionSpape->getShapeType() == ShapeType::ShapeTypeSphere)
	{
		const auto r = dynamic_cast<SphereShape*>(mCollisionSpape)->getRadius();
		const auto moment_of_inertia = glm::mat3{ 2.f / 5.f * getMass() * r * r };
		setMomentofInertia(moment_of_inertia);
	}
}

#if 0
//-----------------------------------------------------------------------------
void RigidBody::stepTime(glm::f32 dt)
{
	// ï¿êiâ^ìÆ
	glm::vec3 acceleration{ getMassInverse() * getForce() };

	setVelocity(getVelcoity() + acceleration * dt);

	setPosition(getPosition() + getVelcoity() * dt);


	// âÒì]â^ìÆ
	glm::vec3 angular_acceleration{ getMomentofInertiaInverse() * getTorque() };
	
	setAngularVelocity(getAngularVelocity() + angular_acceleration * dt);
	
	glm::vec3 axis{ glm::normalize(getAngularVelocity()) };
	const glm::f32 rad{ glm::length(getAngularVelocity()) * dt };
	if (rad < 0.001f)
	{
		return;
	}
	glm::mat3 rot = getRotation();
	for (int idx = 0; idx < 3; idx++)
	{
		rot[idx] = glm::rotate(rot[idx], rad, axis);
		rot[idx] = glm::normalize(rot[idx]);
	}
	setRotation(rot);
}
#endif

}