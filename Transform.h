#pragma once

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// ���s�ړ��E��]�ړ��N���X
class Transform
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	Transform();
	~Transform() {};

	// ������Z�q
	Transform& operator=(const Transform& transform);

	//�ʒu��ݒ肷��
	void setPosition(const glm::vec3& position)
	{
		mPosition = position;
	}

	// �ʒu���擾����
	const glm::vec3& getPosition() const
	{
		return mPosition;
	}

	// ��]�s���ݒ肷��
	void setRotation(const glm::mat3& rotation)
	{
		mRotation = rotation;
	}

	// ��]�s����擾����
	const glm::mat3& getRotation() const
	{
		return mRotation;
	}
#if 0
	/*!
		*	�A�t�B���s���ݒ肷��
		*/
	void setMatrix4(const glm::mat4& /*matrix*/) {};

	/*!
		*	���s�ړ��Ɖ�]�ړ��̍s����擾����
		*/
	const glm::mat4& getTranslationRotationMatrix() const;
#endif
private:
	glm::vec3 mPosition;
	glm::mat3 mRotation;
};

/*!
	*	4x4�s����o�͂���
	*/
void Print(glm::mat4 m);

/*!
	*	3x3�s����o�͂���
	*/
void Print(glm::mat3 m);

/*!
	*	4�����x�N�g�����o��
	*/
void Print(const glm::vec4& v);

/*!
	*	3�����x�N�g�����o��
	*/
void Print(const glm::vec3& v);

}