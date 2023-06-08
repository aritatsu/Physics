#include "AABB.h"

namespace myfx
{
//-----------------------------------------------------------------------------
AABB::AABB()
	: mMin { 0.f }
	, mMax { 0.f }
{}

//-----------------------------------------------------------------------------
AABB::AABB(const glm::vec3& min, const glm::vec3& max)
	: mMin { min }
	, mMax { max }
{}

//-----------------------------------------------------------------------------
AABB::AABB(const CubeShape& cube)
	: mMin { cube.getVertex(0)}
	, mMax { cube.getVertex(6)}
{}

}