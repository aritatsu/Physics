#pragma once

#include "RigidBody.h"

namespace myfx
{

//-----------------------------------------------------------------------------
// ���̂̐ϕ��v�Z���s���N���X
class Integrator
{
public:
    //-------------------------------------------------------------------------
    // �����o�֐�

    // �R���X�g���N�^�E�f�X�g���N�^
    Integrator() {}
    ~Integrator() {}

    // ���̂̐ϕ��v�Z���s��
    void integrateRigidBody(RigidBody* body, glm::f32 dt);
};

//-----------------------------------------------------------------------------
glm::mat3 Rotate(glm::mat3 m, glm::vec3 axis, glm::f32 rad);

}
