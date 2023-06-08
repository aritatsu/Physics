#pragma once

// Collision Data
#include "CollisionDetector.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// 拘束解消クラス
class ConstraintSolver
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	ConstraintSolver() {};
	~ConstraintSolver() {};

	// 拘束を解消する
	void solveConstraint(RigidBody* body1, RigidBody* body2, const CollisionData& collision_data);
};

}
