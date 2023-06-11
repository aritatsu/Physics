#pragma once

#include "RigidBody.h"

namespace myfx
{

//-----------------------------------------------------------------------------
// 剛体の積分計算を行うクラス
class Integrator
{
public:
    //-------------------------------------------------------------------------
    // メンバ関数

    // コンストラクタ・デストラクタ
    Integrator() {}
    ~Integrator() {}

    // 剛体の積分計算を行う
    void integrateRigidBody(RigidBody* body, glm::f32 dt);
};

//-----------------------------------------------------------------------------
glm::mat3 Rotate(glm::mat3 m, glm::vec3 axis, glm::f32 rad);

}
