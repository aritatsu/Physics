#pragma once

#include <glm.hpp>

#include "CubeShape.h"

namespace myfx
{
//-----------------------------------------------------------------------------
// AABBクラス
class AABB
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	AABB();
	AABB(const glm::vec3& min, const glm::vec3& max);
	AABB(const CubeShape& cube);
	~AABB() {};

	//-------------------------------------------------------------------------
	// メンバ変数
	glm::vec3	mMin;
	glm::vec3	mMax;

};

}