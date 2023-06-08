#include "CubeShape.h"

namespace myfx
{
//-----------------------------------------------------------------------------
const glm::u8 CubeShape::cCubeVertexNum = 8;
const std::vector<glm::vec3> CubeShape::cCubeVertices =
{
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3( 0.5f, -0.5f, -0.5f),
	glm::vec3( 0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3( 0.5f, -0.5f,  0.5f),
	glm::vec3( 0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f)
};

//-----------------------------------------------------------------------------
CubeShape::CubeShape(glm::vec3 scale)
	: cScale	{ scale }
	, mVerticies{ std::vector<glm::vec3>(cCubeVertexNum) }
{
	for (glm::int32 idx = 0; idx < cCubeVertexNum; idx++)
	{
		for (glm::int32 xyz_idx = 0; xyz_idx < 3; xyz_idx++)
		{
			mVerticies[idx][xyz_idx] = cCubeVertices[idx][xyz_idx] * cScale[xyz_idx];
		}
	}
}

}