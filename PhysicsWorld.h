#pragma once

#include "ConstraintSolver.h"
#include "ForceCalculator.h"
#include "Integrator.h"

#include <vector>

namespace myfx
{

//-----------------------------------------------------------------------------
// 物理世界クラス
class PhysicsWorld
{
public:
    //-------------------------------------------------------------------------
    // メンバ関数
    
    // コンストラクタ・デストラクタ
    PhysicsWorld();
    ~PhysicsWorld() {}

    // 剛体を世界に追加する
    bool addRigidBody(RigidBody* body);

    // 剛体を世界から削除する
    bool removeRigidBody(RigidBody* body);

    // 物理世界を更新する
    void updateWorld();

private:
    //-------------------------------------------------------------------------
    // メンバ関数

    // ブロードフェイズの処理を行い、衝突候補を求める
    void doBroadPhase_();

    // 衝突候補をもとにナローフェーズの処理を行い、衝突データを求める
    void doNarrowPhase_();

    // 衝突データをもとに拘束を解消する
    void doSolveConstraintPhase_();

    // 力とトルクを加える
    void doAddForceTorque_();

    // 剛体の積分計算を行う
    void doIntegrate_();

    // 剛体に加わる力をリセットする
    void doResetForceTorque_();

    //-------------------------------------------------------------------------
    // メンバ変数
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