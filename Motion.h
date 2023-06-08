#pragma once

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// ���x�E�p���x�N���X
class Motion
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	Motion();
	~Motion() {};

	// ������Z�q
	Motion& operator=(const Motion& motion);

	// ���x��ݒ肷��
	void setVelocity(const glm::vec3& velocity)
	{
		mVelocity = velocity;
	}

	// ���x���擾����
	const glm::vec3& getVelocity() const
	{
		return mVelocity;
	}

	// �p���x���擾����
	const glm::vec3& getAngularVelocity() const
	{
		return mAngularVelocity;
	}

private:
	//-------------------------------------------------------------------------
	// �����o�ϐ�
	glm::vec3 mVelocity;
	glm::vec3 mAngularVelocity;
};

}

