#pragma once

// graphics
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

namespace mygx
{
//-----------------------------------------------------------------------------
// ���f���N���X
class Model
{
public:
	//-------------------------------------------------------------------------
	// ���f���^�C�v�^
	enum ModelType
	{
		None,
		Sphere,
		Box,
		ZXPlane
	};

	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	Model();
	~Model() {};

	// ���f���^�C�v��ݒ肷��
	void setModelType(ModelType model_type)
	{
		mModelType = model_type;
	}

	// �X�P�[����ݒ肷��
	void setScale(const glm::vec3& scale)
	{
		mSMatrix = glm::scale(glm::identity<glm::mat4>(), scale);
	}

	// RT�s���ݒ肷��
	void setRTMatrix(const glm::mat4& matrix)
	{
		mRTMatrix = matrix;
	}

	// SRT�s����X�V����
	void updateMatrix()
	{
		mSRTMatrix = mSMatrix * mRTMatrix;
	}

	// �F��ݒ肷��
	void setColor(const glm::vec3 color)
	{
		mColor = color;
	}

	// ���f����`�悷��
	void draw();


private:
	//---------------------------------------------------------------------------
	// �����o�ϐ�
	ModelType	mModelType;
	glm::mat4	mSRTMatrix;
	glm::mat4	mSMatrix;
	glm::mat4	mRTMatrix;
	glm::vec3	mColor;
};
}

