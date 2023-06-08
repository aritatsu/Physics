#pragma once

// physics
#include "ICollisionShape.h"
#include "Inertia.h"
#include "Motion.h"
#include "Power.h"
#include "Transform.h"


namespace myfx
{
//-----------------------------------------------------------------------------
// ���̃N���X
class RigidBody
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	RigidBody();
	RigidBody(const RigidBody& body);
	~RigidBody() {};

	//������Z�q
	RigidBody& operator=(const RigidBody& body);

	//------------------------------------
	// �Z�b�^�[�E�Q�b�^�[
	
	// ���ʂ�ݒ肷��
	void setMass(glm::f32 mass)
	{
		mInertia.setMass(mass);
	}

	// ���ʂ��擾����
	glm::f32 getMass() const
	{
		return mInertia.getMass();
	}

	// �������[�����g��ݒ肷��
	void setMomentofInertia(const glm::mat3& moment_of_inertia)
	{
		mInertia.setMomentofInertia(moment_of_inertia);
	}

	// �������[�����g���擾����
	const glm::mat3& getMomentofInertia() const
	{
		return mInertia.getMomentofInertia();
	}

	// ���̂ɉ����O�͂�ݒ肷��
	void setForce(const glm::vec3& force)
	{
		mPower.setForce(force);
	}

	// ���̂ɉ����O�͂��擾����
	const glm::vec3& getForce() const
	{
		return mPower.getForce();
	}

	// ���x��ݒ肷��
	void setVelocity(const glm::vec3& velocity)
	{
		mMotion.setVelocity(velocity);
	}

	// ���x���擾����
	const glm::vec3& getVelcoity() const
	{
		return mMotion.getVelocity();
	}

	// �p���x���擾����
	const glm::vec3& getAngularVelcoity() const
	{
		return mMotion.getAngularVelocity();
	}

	// �ʒu��ݒ肷��
	void setPosition(const glm::vec3& position)
	{
		mTransform.setPosition(position);
	}

	// �ʒu���擾����
	const glm::vec3& getPosition() const
	{
		return mTransform.getPosition();
	}

	// ��]�s���ݒ肷��
	void setRotation(const glm::mat4& rotation)
	{
		mTransform.setRotation(rotation);
	}

	// ��]�s����擾����
	const glm::mat3& getRotation() const
	{
		return mTransform.getRotation();
	}

	// �Փˌ`���ݒ肷��
	void setCollisionShape(ICollisionShape* collision_shape)
	{
		mCollisionSpape = collision_shape;
	}

	// �Փˌ`����擾����
	ICollisionShape* getCollisionShape() const
	{
		return mCollisionSpape;
	}

	// �����W����ݒ肷��
	void setRestitution(glm::f32 restitution)
	{
		mRestitution = restitution;
	}

	// �����W�����擾����
	glm::f32 getRestitution() const
	{
		return mRestitution;
	}

	// ���C�W����ݒ肷��
	void setFriction(glm::f32 friction)
	{
		mFriction = friction;
	}

	// ���C�W�����擾����
	glm::f32 getFriction() const
	{
		return mFriction;
	}

	//------------------------------------
	// �����v�Z�֐�

	// �`��Ǝ��ʂ����Ɋ������[�����g���X�V����
	void updateMomentofInertia();

	// ������dt�i�߂�
	void stepTime(glm::f32 dt);

private:
	//-------------------------------------------------------------------------
	// �����o�ϐ�
	Inertia				mInertia;
	Power				mPower;
	Transform			mTransform;
	Motion				mMotion;
	ICollisionShape*	mCollisionSpape;
	glm::f32			mRestitution;
	glm::f32			mFriction;
};
}