#pragma once

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// 速度・角速度クラス
class Motion
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	Motion();
	~Motion() {};

	// 代入演算子
	Motion& operator=(const Motion& motion);

	// 速度を設定する
	void setVelocity(const glm::vec3& velocity)
	{
		mVelocity = velocity;
	}

	// 速度を取得する
	const glm::vec3& getVelocity() const
	{
		return mVelocity;
	}

	// 角速度を取得する
	const glm::vec3& getAngularVelocity() const
	{
		return mAngularVelocity;
	}

private:
	//-------------------------------------------------------------------------
	// メンバ変数
	glm::vec3 mVelocity;
	glm::vec3 mAngularVelocity;
};

}

