#pragma once

// physics
#include "ICollisionShape.h"
#include "Inertia.h"
#include "Motion.h"
#include "Power.h"
#include "Transform.h"


namespace myfx
{
//-----------------------------------------------------------------------------
// 剛体クラス
class RigidBody
{
public:
	//-------------------------------------------------------------------------
	// メンバ関数

	// コンストラクタ・デストラクタ
	RigidBody();
	RigidBody(const RigidBody& body);
	~RigidBody() {};

	//代入演算子
	RigidBody& operator=(const RigidBody& body);

	//------------------------------------
	// セッター・ゲッター
	
	// 質量を設定する
	void setMass(glm::f32 mass)
	{
		mInertia.setMass(mass);
	}

	// 質量を取得する
	glm::f32 getMass() const
	{
		return mInertia.getMass();
	}

	// 慣性モーメントを設定する
	void setMomentofInertia(const glm::mat3& moment_of_inertia)
	{
		mInertia.setMomentofInertia(moment_of_inertia);
	}

	// 慣性モーメントを取得する
	const glm::mat3& getMomentofInertia() const
	{
		return mInertia.getMomentofInertia();
	}

	// 剛体に加わる外力を設定する
	void setForce(const glm::vec3& force)
	{
		mPower.setForce(force);
	}

	// 剛体に加わる外力を取得する
	const glm::vec3& getForce() const
	{
		return mPower.getForce();
	}

	// 速度を設定する
	void setVelocity(const glm::vec3& velocity)
	{
		mMotion.setVelocity(velocity);
	}

	// 速度を取得する
	const glm::vec3& getVelcoity() const
	{
		return mMotion.getVelocity();
	}

	// 角速度を取得する
	const glm::vec3& getAngularVelcoity() const
	{
		return mMotion.getAngularVelocity();
	}

	// 位置を設定する
	void setPosition(const glm::vec3& position)
	{
		mTransform.setPosition(position);
	}

	// 位置を取得する
	const glm::vec3& getPosition() const
	{
		return mTransform.getPosition();
	}

	// 回転行列を設定する
	void setRotation(const glm::mat4& rotation)
	{
		mTransform.setRotation(rotation);
	}

	// 回転行列を取得する
	const glm::mat3& getRotation() const
	{
		return mTransform.getRotation();
	}

	// 衝突形状を設定する
	void setCollisionShape(ICollisionShape* collision_shape)
	{
		mCollisionSpape = collision_shape;
	}

	// 衝突形状を取得する
	ICollisionShape* getCollisionShape() const
	{
		return mCollisionSpape;
	}

	// 反発係数を設定する
	void setRestitution(glm::f32 restitution)
	{
		mRestitution = restitution;
	}

	// 反発係数を取得する
	glm::f32 getRestitution() const
	{
		return mRestitution;
	}

	// 摩擦係数を設定する
	void setFriction(glm::f32 friction)
	{
		mFriction = friction;
	}

	// 摩擦係数を取得する
	glm::f32 getFriction() const
	{
		return mFriction;
	}

	//------------------------------------
	// 物理計算関数

	// 形状と質量を元に慣性モーメントを更新する
	void updateMomentofInertia();

	// 時刻をdt進める
	void stepTime(glm::f32 dt);

private:
	//-------------------------------------------------------------------------
	// メンバ変数
	Inertia				mInertia;
	Power				mPower;
	Transform			mTransform;
	Motion				mMotion;
	ICollisionShape*	mCollisionSpape;
	glm::f32			mRestitution;
	glm::f32			mFriction;
};
}