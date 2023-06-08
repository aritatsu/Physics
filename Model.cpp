// header
#include "Model.h"

// graphics
#include <freeglut.h>

namespace mygx
{
//----------------------------------------------------------------------------
Model::Model()
	: mModelType{ ModelType::None }
	, mSRTMatrix	{ 1.f }
	, mSMatrix		{ 1.f }
	, mRTMatrix		{ 1.f }
	, mColor		{ 1.f }
{
}

//----------------------------------------------------------------------------
void Model::draw()
{
	// モデルビュー行列に設定
	glMatrixMode(GL_MODELVIEW);

	// 深度テスト・ライティングを有効
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPushMatrix();
	{
		glColor3f(mColor.x, mColor.y, mColor.z);

		glMultMatrixf((const GLfloat*)&mSRTMatrix);

		// 描画内容は、モデルタイプによって異なる
		switch (mModelType)
		{
		// 無形
		case mygx::Model::None:
			break;
		// 球
		case mygx::Model::Sphere:
			glutSolidSphere(1.0, 32, 32);
			break;
		// 直方体
		case mygx::Model::Box:
			glutSolidCube(2.f);
			break;
		// ZX平面
		case mygx::Model::ZXPlane:
			glBegin(GL_QUADS);
				
			glVertex3f( 0.5f, 0.f,  0.5f);
			glVertex3f( 0.5f, 0.f, -0.5f);
			glVertex3f(-0.5f, 0.f, -0.5f);
			glVertex3f(-0.5f, 0.f,  0.5f);

			glEnd();
			break;
		default:
			break;
		}
	}
	glPopMatrix();
}
}