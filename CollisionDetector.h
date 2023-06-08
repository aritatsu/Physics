#pragma once

// shape
#include "AABB.h"
#include "SphereShape.h"

// rigid body
#include "RigidBody.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// �Փ˃f�[�^�^
struct CollisionData {
	bool		mIsColliding;
	glm::vec3	mTangent;
	glm::vec3	mNormal;
};

//-----------------------------------------------------------------------------
// �Փˌ��o�N���X
class CollisionDetector
{
public:
	//-------------------------------------------------------------------------
	// �����o�֐�

	// �R���X�g���N�^�E�f�X�g���N�^
	CollisionDetector() {};
	~CollisionDetector() {};

	// AABB����_�Ɍ������@���x�N�g�����擾����
	// �_�������ɂ���Ƃ��͍ł��߂��ʂ̖@���x�N�g�����擾����
	glm::vec3 getNormal(const AABB& box, const glm::vec3& point);

	// �_����AABB�Ɍ������Đ��������낵�����̌�_���擾����
	// �_�������ɂ���Ƃ��͍ł��߂��ʂ֐��������낵�����̌�_���擾����
	glm::vec3 getTangent(const AABB& box, const glm::vec3& point);

	// AABB�Ɠ_�̏Փ˃f�[�^���擾����
	CollisionData getCollisionData(const AABB& box, const glm::vec3& point);

	// �I�u�W�F�N�g���m�̏Փ˃f�[�^��Ԃ�
	CollisionData getCollisionData(const RigidBody& body1, const RigidBody& body2);

private:
	//----------------------------------------------------------------------------
	// �N���X�O�ɂ͔���J�̃����o�֐�

	// �_����AABB�Ɍ������Đ��������낵�����̌�_���擾����
	// �_�������ɂ���Ƃ��͂��̓_���g���擾����
	glm::vec3 getTangentOrSelf_(const AABB& box, const glm::vec3& point);
	
	// AABB�̓����ɂ���_����ł��߂��ʂ̖@���x�N�g�����擾����
	glm::vec3 getNormalFromInside_(const AABB& box, const glm::vec3& inside);

	// AABB�̓����ɂ���_����ł��߂��ʂ֐��������낵�����̌�_���擾����
	glm::vec3 getTangentFromInside_(const AABB& box, const glm::vec3& inside);


};

}
