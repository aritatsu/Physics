#pragma once

#include <glm.hpp>

namespace myfx
{
//-----------------------------------------------------------------------------
// 平行移動・回転移動クラス
class Transform
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	Transform();
	~Transform() {};

	// 代入演算子
	Transform& operator=(const Transform& transform);

	//位置を設定する
	void setPosition(const glm::vec3& position)
	{
		mPosition = position;
	}

	// 位置を取得する
	const glm::vec3& getPosition() const
	{
		return mPosition;
	}

	// 回転行列を設定する
	void setRotation(const glm::mat3& rotation)
	{
		mRotation = rotation;
	}

	// 回転行列を取得する
	const glm::mat3& getRotation() const
	{
		return mRotation;
	}
#if 0
	/*!
		*	アフィン行列を設定する
		*/
	void setMatrix4(const glm::mat4& /*matrix*/) {};

	/*!
		*	平行移動と回転移動の行列を取得する
		*/
	const glm::mat4& getTranslationRotationMatrix() const;
#endif
private:
	glm::vec3 mPosition;
	glm::mat3 mRotation;
};

/*!
	*	4x4行列を出力する
	*/
void Print(glm::mat4 m);

/*!
	*	3x3行列を出力する
	*/
void Print(glm::mat3 m);

/*!
	*	4次元ベクトルを出力
	*/
void Print(const glm::vec4& v);

/*!
	*	3次元ベクトルを出力
	*/
void Print(const glm::vec3& v);

}