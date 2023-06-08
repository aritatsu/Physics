#pragma once
#include "ICollisionShape.h"

#include <glm.hpp>
#include <vector>

namespace myfx
{
//-----------------------------------------------------------------------------
// 直方体形状クラス
class CubeShape : public ICollisionShape
{

public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	CubeShape(glm::vec3 scale = { 1.f, 1.f, 1.f });
	~CubeShape() {};

	// 図形の型を取得する
	ShapeType getShapeType() const override
	{
		return ShapeTypeCube;
	}

	// スケールを取得する
	const glm::vec3& getScale() const
	{
		return cScale;
	}

	// 頂点の座標を取得する
	const glm::vec3 getVertex(glm::int32 idx) const
	{
		return mVerticies[idx];
	}

private:
	//----------------------------------------------------------------------------
	// メンバ変数
	static const glm::u8				cCubeVertexNum;
	static const std::vector<glm::vec3> cCubeVertices;
	const glm::vec3						cScale;
	std::vector<glm::vec3>				mVerticies;
};

void PrintCubeVertices(std::vector<glm::vec4>);
}
