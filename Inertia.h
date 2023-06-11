#pragma once

#include <glm.hpp>
#include <gtc/constants.hpp>

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
		if (mMass)
		{
			mMassInverse = 1.f / mMass;
		}
		else
		{
			mMassInverse = 0.f;
		}
	}

	// 質量を取得する
	glm::f32 getMass() const
	{
		return mMass;
	}

	// 質量の逆数を取得する
	glm::f32 getMassInverse() const
	{
		return mMassInverse;
	}

	// 慣性モーメントを設定する
	void setMomentofInertia(const glm::mat3& moment_of_inertia)
	{
		mMomentofInertia = moment_of_inertia;
		if (mMomentofInertia != glm::zero<glm::mat3>())
		{
			mMomentofInertiaInverse = glm::inverse(mMomentofInertia);
		}
		else
		{
			mMomentofInertiaInverse = glm::zero<glm::mat3>();
		}
	}

	// 慣性モーメントを取得する
	const glm::mat3& getMomentofInertia() const
	{
		return mMomentofInertia;
	}

	// 慣性モーメントの逆行列を取得する
	const glm::mat3& getMomentofInertiaInverse() const
	{
		return mMomentofInertiaInverse;
	}

private:
	//-------------------------------------------------------------------------
	// メンバ変数
	glm::f32	mMass;
	glm::f32	mMassInverse;
	glm::mat3	mMomentofInertia;
	glm::mat3	mMomentofInertiaInverse;
};

}

