#pragma once

namespace myfx
{
//-----------------------------------------------------------------------------
// 形状の型
enum ShapeType
{
	ShapeTypeCube,
	ShapeTypeSphere
};

//-----------------------------------------------------------------------------
// 衝突形状インターフェイス
class ICollisionShape
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// 形状の型を返す
	virtual ShapeType getShapeType() const = 0;
};

}
