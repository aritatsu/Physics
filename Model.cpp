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
	// ���f���r���[�s��ɐݒ�
	glMatrixMode(GL_MODELVIEW);

	// �[�x�e�X�g�E���C�e�B���O��L��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPushMatrix();
	{
		glColor3f(mColor.x, mColor.y, mColor.z);

		glMultMatrixf((const GLfloat*)&mSRTMatrix);

		// �`����e�́A���f���^�C�v�ɂ���ĈقȂ�
		switch (mModelType)
		{
		// ���`
		case mygx::Model::None:
			break;
		// ��
		case mygx::Model::Sphere:
			glutSolidSphere(1.0, 32, 32);
			break;
		// ������
		case mygx::Model::Box:
			glutSolidCube(2.f);
			break;
		// ZX����
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