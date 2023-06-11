// header
#include "CollisionDetector.h"


namespace myfx
{
//-----------------------------------------------------------------------------
CollisionData::CollisionData()
	: mIsColliding	{ false }
	, mTangent		{ glm::zero<glm::vec3>() }
	, mNormal		{ glm::zero<glm::vec3>() }
{ }

//-----------------------------------------------------------------------------
CollisionData::CollisionData(bool is_colliding, const glm::vec3& tangent, const glm::vec3& normal)
	: mIsColliding	{ is_colliding }
	, mTangent		{ tangent }
	, mNormal		{ normal }
{ }

//-----------------------------------------------------------------------------
glm::vec3 CollisionDetector::getNormal(const AABB& box, const glm::vec3& point)
{
	auto tangent = getTangentOrSelf_(box, point);

	if (tangent != point)
	{
		auto normal = glm::normalize(point - tangent);
		return normal;
	}
	else
	{
		return getNormalFromInside_(box, point);
	}
}

//-----------------------------------------------------------------------------
glm::vec3 CollisionDetector::getTangent(const AABB& box, const glm::vec3& point)
{
	auto tangent = getTangentOrSelf_(box, point);

	if (tangent != point)
	{
		return tangent;
	}
	else
	{
		return getTangentFromInside_(box, point);
	}
}

//-----------------------------------------------------------------------------
CollisionData CollisionDetector::getCollisionData(const AABB& box, const glm::vec3& point)
{
	return CollisionData{ point == getTangentOrSelf_(box, point), getTangent(box, point), getNormal(box, point) };
}

//-----------------------------------------------------------------------------
CollisionData CollisionDetector::getCollisionData(const RigidBody& body1, const RigidBody& body2)
{
	// 直方体と球の衝突判定
	if (body1.getCollisionShape()->getShapeType() == ShapeType::ShapeTypeSphere && body2.getCollisionShape()->getShapeType() == ShapeType::ShapeTypeCube)
	{
		// PhysicsDispatcherクラスがbody1に直方体を、body2に球を割り当てているはずである。
		assert(false);

		return getCollisionData(body2, body1);
#if 0
		// 直方体の形状からAABBを作る
		const auto* p_cubeshape = dynamic_cast<CubeShape*>(body2.getCollisionShape());
		const auto box = AABB(*p_cubeshape);

		// body1（球）の座標をbody2（直方体）の座標系に変換する
		const auto sphere_pos = (body1.getPosition() - body2.getPosition()) * glm::inverse(body2.getRotation());

		// 衝突データを計算し、body2（直方体の）座標系からグローバル座標系に直す
		auto collision_data = getCollisionData(box, sphere_pos);
		collision_data.mTangent = collision_data.mTangent * body2.getRotation() + body2.getPosition();
		collision_data.mNormal = glm::normalize(collision_data.mNormal * body2.getRotation());

		return collision_data;
#endif
	}
	if (body1.getCollisionShape()->getShapeType() == ShapeType::ShapeTypeCube && body2.getCollisionShape()->getShapeType() == ShapeType::ShapeTypeSphere)
	{
		// 直方体の形状からAABBを作る
		const auto* p_cubeshape = dynamic_cast<CubeShape*>(body1.getCollisionShape());
		const auto box = AABB(*p_cubeshape);

		// body2（球）の座標をbody1（直方体）の座標系に変換する
		const auto sphere_pos = glm::inverse(body1.getRotation()) * (body2.getPosition() - body1.getPosition());
		const auto p_sphereshape = dynamic_cast<SphereShape*>(body2.getCollisionShape());

		// 衝突データを計算し、body1（直方体の）座標系からグローバル座標系に直す
		auto collision_data = getCollisionData(box, sphere_pos);
		collision_data.mIsColliding = glm::dot(collision_data.mNormal, sphere_pos - collision_data.mTangent) - p_sphereshape->getRadius() <= 0.f;
		collision_data.mTangent = body1.getRotation() * collision_data.mTangent + body1.getPosition();
		collision_data.mNormal = glm::normalize(body1.getRotation() * -collision_data.mNormal);

		return collision_data;
	}

	return CollisionData{ false, { glm::zero<glm::vec3>() }, { glm::zero<glm::vec3>() }};
}

//-----------------------------------------------------------------------------
glm::vec3 CollisionDetector::getTangentOrSelf_(const AABB& box, const glm::vec3& point)
{
	auto tangent = point;
	for (glm::int32 xyz_idx = 0; xyz_idx < 3; xyz_idx++)
	{
		tangent[xyz_idx] = glm::max(tangent[xyz_idx], box.mMin[xyz_idx]);
		tangent[xyz_idx] = glm::min(tangent[xyz_idx], box.mMax[xyz_idx]);
	}

	return tangent;
}

//-----------------------------------------------------------------------------
glm::vec3 CollisionDetector::getNormalFromInside_(const AABB& box, const glm::vec3& inside)
{
	glm::f32 min_dist = FLT_MAX;
	for (glm::int32 xyz_idx = 0; xyz_idx < 3; xyz_idx++)
	{
		min_dist = glm::min(min_dist, box.mMax[xyz_idx] - inside[xyz_idx]);
		min_dist = glm::min(min_dist, inside[xyz_idx] - box.mMin[xyz_idx]);
	}

	for (glm::int32 xyz_idx = 0; xyz_idx < 3; xyz_idx++)
	{
		if (box.mMax[xyz_idx] - inside[xyz_idx] == min_dist)
		{
			if (xyz_idx == 0)
			{
				return glm::vec3{ 1.f, 0.f, 0.f };
			}
			else if (xyz_idx == 1)
			{
				return glm::vec3{ 0.f, 1.f, 0.f };
			}
			else 
			{
				return glm::vec3{ 0.f, 0.f, 1.f };
			}
		}
		if (inside[xyz_idx] - box.mMin[xyz_idx] == min_dist)
		{
			if (xyz_idx == 0)
			{
				return glm::vec3{ -1.f, 0.f, 0.f };
			}
			else if (xyz_idx == 1)
			{
				return glm::vec3{ 0.f, -1.f, 0.f };
			}
			if (xyz_idx == 2)
			{
				return glm::vec3{ 0.f, 0.f, -1.f };
			}
		}
	}
	return glm::vec3{ 0.f, 0.f, 0.f };
}

//-----------------------------------------------------------------------------
glm::vec3 CollisionDetector::getTangentFromInside_(const AABB& box, const glm::vec3& inside)
{
	const auto normal = getNormalFromInside_(box, inside);
	auto tangent = inside;

	if (normal == glm::vec3{ 1.f, 0.f, 0.f })
	{
		tangent.x = box.mMax.x;
	}
	if (normal == glm::vec3{ 0.f, 1.f, 0.f })
	{
		tangent.y = box.mMax.y;
	}
	if (normal == glm::vec3{ 0.f, 0.f, 1.f })
	{
		tangent.z = box.mMax.z;
	}
	if (normal == glm::vec3{ -1.f, 0.f, 0.f })
	{
		tangent.x = box.mMin.x;
	}
	if (normal == glm::vec3{ 0.f, -1.f, 0.f })
	{
		tangent.y = box.mMin.y;
	}
	if (normal == glm::vec3{ 0.f, 0.f, -1.f })
	{
		tangent.z = box.mMin.z;
	}

	return tangent;
}

}