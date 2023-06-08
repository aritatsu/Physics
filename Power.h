#pragma once

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// �́E�g���N�N���X
class Power
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	Power();
	~Power() {};

	// ������Z�q
	Power& operator=(const Power& power);

	// �͂�ݒ肷��
	void setForce(const glm::vec3& force)
	{
		mForce = force;
	}

	// �͂��擾����
	const glm::vec3& getForce() const
	{
		return mForce;
	}

private:
	//-------------------------------------------------------------------------
	// �����o�ϐ�
	glm::vec3	mForce;
	glm::vec3	mTorque;

};

}
