#pragma once

namespace myfx
{
//-----------------------------------------------------------------------------
// �`��̌^
enum ShapeType
{
	ShapeTypeCube,
	ShapeTypeSphere
};

//-----------------------------------------------------------------------------
// �Փˌ`��C���^�[�t�F�C�X
class ICollisionShape
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �`��̌^��Ԃ�
	virtual ShapeType getShapeType() const = 0;
};

}
