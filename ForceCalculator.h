#pragma once

#include "CollisionDetector.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// 衝突時の力を計算するクラス
class ForceCalculator
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	ForceCalculator() {}
	~ForceCalculator() {}

	// body1がbody2から受け取る力積を返す
	glm::vec3 getImpulse(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data);

	// body1がbody2から受け取る摩擦力を返す
	glm::vec3 getFrictionForce(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data, const glm::vec3& normal_force);
};

}
