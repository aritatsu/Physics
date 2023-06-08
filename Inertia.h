#pragma once

#include <glm.hpp>

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
	}

	// ���ʂ��擾����
	glm::f32 getMass() const
	{
		return mMass;
	}

	// �������[�����g��ݒ肷��
	void setMomentofInertia(const glm::mat3& moment_of_inertia)
	{
		mMomentofInertia = moment_of_inertia;
	}

	// �������[�����g���擾����
	const glm::mat3& getMomentofInertia() const
	{
		return mMomentofInertia;
	}

private:
	//-------------------------------------------------------------------------
	// �����o�ϐ�
	glm::f32	mMass;
	glm::mat3	mMomentofInertia;
};

}

