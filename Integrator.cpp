#include "Integrator.h"

#include <gtx/rotate_vector.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
glm::mat3 Rotate(glm::mat3 m, glm::vec3 axis, glm::f32 rad)
{
	for (int idx = 0; idx < 3; idx++)
	{
		m[idx] = glm::rotate(m[idx], rad, axis);
		m[idx] = glm::normalize(m[idx]);
	}
	return m;
}

//-----------------------------------------------------------------------------
void Integrator::integrateRigidBody(RigidBody* body, glm::f32 dt)
{
	// •Ài‰^“®
	glm::vec3 acceleration{ body->getMassInverse()* body->getForce() };

	body->setVelocity(body->getVelcoity() + acceleration * dt);

	body->setPosition(body->getPosition() + body->getVelcoity() * dt);


	// ‰ñ“]‰^“®
	glm::vec3 angular_acceleration{ body->getMomentofInertiaInverse()* body->getTorque() };

	body->setAngularVelocity(body->getAngularVelocity() + angular_acceleration * dt);

	glm::vec3 axis{ glm::normalize(body->getAngularVelocity()) };
	const glm::f32 rad{ glm::length(body->getAngularVelocity())* dt };
	if (rad < 0.001f)
	{
		return;
	}
	//glm::mat3 rot = body->getRotation();
	//for (int idx = 0; idx < 3; idx++)
	//{
	//	rot[idx] = glm::rotate(rot[idx], rad, axis);
	//	rot[idx] = glm::normalize(rot[idx]);
	//}
	body->setRotation(Rotate(body->getRotation(), axis, rad));
}

}