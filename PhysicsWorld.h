#pragma once

#include "ConstraintSolver.h"
#include "ForceCalculator.h"
#include "Integrator.h"

#include <vector>

namespace myfx
{

//-----------------------------------------------------------------------------
// �������E�N���X
class PhysicsWorld
{
public:
    //-------------------------------------------------------------------------
    // �����o�֐�
    
    // �R���X�g���N�^�E�f�X�g���N�^
    PhysicsWorld();
    ~PhysicsWorld() {}

    // ���̂𐢊E�ɒǉ�����
    bool addRigidBody(RigidBody* body);

    // ���̂𐢊E����폜����
    bool removeRigidBody(RigidBody* body);

    // �������E���X�V����
    void updateWorld();

private:
    //-------------------------------------------------------------------------
    // �����o�֐�

    // �u���[�h�t�F�C�Y�̏������s���A�Փˌ������߂�
    void doBroadPhase_();

    // �Փˌ������ƂɃi���[�t�F�[�Y�̏������s���A�Փ˃f�[�^�����߂�
    void doNarrowPhase_();

    // �Փ˃f�[�^�����ƂɍS������������
    void doSolveConstraintPhase_();

    // �͂ƃg���N��������
    void doAddForceTorque_();

    // ���̂̐ϕ��v�Z���s��
    void doIntegrate_();

    // ���̂ɉ����͂����Z�b�g����
    void doResetForceTorque_();

    //-------------------------------------------------------------------------
    // �����o�ϐ�
    glm::f32                                        mDeltaTime;
    const glm::vec3                                 cGravityAcceleration;

    std::vector<RigidBody*>                         mRigidBodies;
    std::vector<std::pair<RigidBody*, RigidBody*>>  mCollisionCandidates;
    std::vector<CollisionData>                      mCollisionDataArray;

    CollisionDetector                               mCollisionDetector;
    ConstraintSolver                                mConstraintSolver;
    ForceCalculator                                 mForceCalculator;
    Integrator                                      mIntegrator;
};

}