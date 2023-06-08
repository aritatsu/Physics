#include "RigidBody.h"

#include "CubeShape.h"
#include "SphereShape.h"

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

//-----------------------------------------------------------------------------
void RigidBody::stepTime(glm::f32 dt)
{
	glm::vec3 acceleration{ 0.f };
	if (getMass())
	{
		acceleration = getForce() / getMass();
	}

	setVelocity(getVelcoity() + acceleration * dt);

	setPosition(getPosition() + getVelcoity() * dt);
}

}