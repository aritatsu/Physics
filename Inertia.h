#pragma once

#include <glm.hpp>
#include <gtc/constants.hpp>

namespace myfx
{

//-----------------------------------------------------------------------------
// ���ʁE�������[�����g�N���X
class Inertia
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	Inertia();
	~Inertia() {};

	// ������Z�q
	Inertia& operator=(const Inertia& inertia);

	// ���ʂ�ݒ肷��
	void setMass(glm::f32 mass)
	{
		mMass = mass;
		if (mMass)
		{
			mMassInverse = 1.f / mMass;
		}
		else
		{
			mMassInverse = 0.f;
		}
	}

	// ���ʂ��擾����
	glm::f32 getMass() const
	{
		return mMass;
	}

	// ���ʂ̋t�����擾����
	glm::f32 getMassInverse() const
	{
		return mMassInverse;
	}

	// �������[�����g��ݒ肷��
	void setMomentofInertia(const glm::mat3& moment_of_inertia)
	{
		mMomentofInertia = moment_of_inertia;
		if (mMomentofInertia != glm::zero<glm::mat3>())
		{
			mMomentofInertiaInverse = glm::inverse(mMomentofInertia);
		}
		else
		{
			mMomentofInertiaInverse = glm::zero<glm::mat3>();
		}
	}

	// �������[�����g���擾����
	const glm::mat3& getMomentofInertia() const
	{
		return mMomentofInertia;
	}

	// �������[�����g�̋t�s����擾����
	const glm::mat3& getMomentofInertiaInverse() const
	{
		return mMomentofInertiaInverse;
	}

private:
	//-------------------------------------------------------------------------
	// �����o�ϐ�
	glm::f32	mMass;
	glm::f32	mMassInverse;
	glm::mat3	mMomentofInertia;
	glm::mat3	mMomentofInertiaInverse;
};

}

