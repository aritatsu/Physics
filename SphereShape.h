#pragma once
#include "ICollisionShape.h"

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// 球形状クラス
class SphereShape : public ICollisionShape
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	SphereShape(glm::f32 radius = 1.f);
	~SphereShape() {};

	// 図形の型を取得する
	ShapeType getShapeType() const override
	{
		return ShapeTypeSphere;
	}

	// 球の半径を取得する
	glm::f32 getRadius() const
	{
		return mRadius;
	}

private:
	glm::f32 mRadius;
};

}


