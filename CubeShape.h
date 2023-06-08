#pragma once
#include "ICollisionShape.h"

#include <glm.hpp>
#include <vector>

namespace myfx
{
//-----------------------------------------------------------------------------
// �����̌`��N���X
class CubeShape : public ICollisionShape
{

public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	CubeShape(glm::vec3 scale = { 1.f, 1.f, 1.f });
	~CubeShape() {};

	// �}�`�̌^���擾����
	ShapeType getShapeType() const override
	{
		return ShapeTypeCube;
	}

	// �X�P�[�����擾����
	const glm::vec3& getScale() const
	{
		return cScale;
	}

	// ���_�̍��W���擾����
	const glm::vec3 getVertex(glm::int32 idx) const
	{
		return mVerticies[idx];
	}

private:
	//----------------------------------------------------------------------------
	// �����o�ϐ�
	static const glm::u8				cCubeVertexNum;
	static const std::vector<glm::vec3> cCubeVertices;
	const glm::vec3						cScale;
	std::vector<glm::vec3>				mVerticies;
};

void PrintCubeVertices(std::vector<glm::vec4>);
}
