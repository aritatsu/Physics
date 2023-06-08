#pragma once

// graphics
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

namespace mygx
{
//-----------------------------------------------------------------------------
// モデルクラス
class Model
{
public:
	//-------------------------------------------------------------------------
	// モデルタイプ型
	enum ModelType
	{
		None,
		Sphere,
		Box,
		ZXPlane
	};

	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	Model();
	~Model() {};

	// モデルタイプを設定する
	void setModelType(ModelType model_type)
	{
		mModelType = model_type;
	}

	// スケールを設定する
	void setScale(const glm::vec3& scale)
	{
		mSMatrix = glm::scale(glm::identity<glm::mat4>(), scale);
	}

	// RT行列を設定する
	void setRTMatrix(const glm::mat4& matrix)
	{
		mRTMatrix = matrix;
	}

	// SRT行列を更新する
	void updateMatrix()
	{
		mSRTMatrix = mSMatrix * mRTMatrix;
	}

	// 色を設定する
	void setColor(const glm::vec3 color)
	{
		mColor = color;
	}

	// モデルを描画する
	void draw();


private:
	//---------------------------------------------------------------------------
	// メンバ変数
	ModelType	mModelType;
	glm::mat4	mSRTMatrix;
	glm::mat4	mSMatrix;
	glm::mat4	mRTMatrix;
	glm::vec3	mColor;
};
}

