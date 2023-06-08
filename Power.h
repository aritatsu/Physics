#pragma once

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// 力・トルククラス
class Power
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	Power();
	~Power() {};

	// 代入演算子
	Power& operator=(const Power& power);

	// 力を設定する
	void setForce(const glm::vec3& force)
	{
		mForce = force;
	}

	// 力を取得する
	const glm::vec3& getForce() const
	{
		return mForce;
	}

private:
	//-------------------------------------------------------------------------
	// メンバ変数
	glm::vec3	mForce;
	glm::vec3	mTorque;

};

}
