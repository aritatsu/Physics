#pragma once

#include <glm.hpp>

namespace myfx
{

//-----------------------------------------------------------------------------
// 質量・慣性モーメントクラス
class Inertia
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	Inertia();
	~Inertia() {};

	// 代入演算子
	Inertia& operator=(const Inertia& inertia);

	// 質量を設定する
	void setMass(glm::f32 mass)
	{
		mMass = mass;
	}

	// 質量を取得する
	glm::f32 getMass() const
	{
		return mMass;
	}

	// 慣性モーメントを設定する
	void setMomentofInertia(const glm::mat3& moment_of_inertia)
	{
		mMomentofInertia = moment_of_inertia;
	}

	// 慣性モーメントを取得する
	const glm::mat3& getMomentofInertia() const
	{
		return mMomentofInertia;
	}

private:
	//-------------------------------------------------------------------------
	// メンバ変数
	glm::f32	mMass;
	glm::mat3	mMomentofInertia;
};

}

