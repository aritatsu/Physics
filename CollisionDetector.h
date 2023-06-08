#pragma once

// shape
#include "AABB.h"
#include "SphereShape.h"

// rigid body
#include "RigidBody.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// 衝突データ型
struct CollisionData {
	bool		mIsColliding;
	glm::vec3	mTangent;
	glm::vec3	mNormal;
};

//-----------------------------------------------------------------------------
// 衝突検出クラス
class CollisionDetector
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	CollisionDetector() {};
	~CollisionDetector() {};

	// AABBから点に向かう法線ベクトルを取得する
	// 点が内部にあるときは最も近い面の法線ベクトルを取得する
	glm::vec3 getNormal(const AABB& box, const glm::vec3& point);

	// 点からAABBに向かって垂線を下ろした時の交点を取得する
	// 点が内部にあるときは最も近い面へ垂線を下ろした時の交点を取得する
	glm::vec3 getTangent(const AABB& box, const glm::vec3& point);

	// AABBと点の衝突データを取得する
	CollisionData getCollisionData(const AABB& box, const glm::vec3& point);

	// オブジェクト同士の衝突データを返す
	CollisionData getCollisionData(const RigidBody& body1, const RigidBody& body2);

private:
	//----------------------------------------------------------------------------
	// クラス外には非公開のメンバ関数

	// 点からAABBに向かって垂線を下ろした時の交点を取得する
	// 点が内部にあるときはその点自身を取得する
	glm::vec3 getTangentOrSelf_(const AABB& box, const glm::vec3& point);
	
	// AABBの内部にある点から最も近い面の法線ベクトルを取得する
	glm::vec3 getNormalFromInside_(const AABB& box, const glm::vec3& inside);

	// AABBの内部にある点から最も近い面へ垂線を下ろした時の交点を取得する
	glm::vec3 getTangentFromInside_(const AABB& box, const glm::vec3& inside);


};

}
