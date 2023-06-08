#if 1

#include "ConstraintSolver.h"
#include "CollisionDetector.h"
#include "ForceCalculator.h"

#include "CubeShape.h"
#include "RigidBody.h"
#include "SphereShape.h"

#include "Model.h"

#include <stdio.h>

#include <glm.hpp>
#include <freeglut.h>

#define WINDOW_WIDTH	(1200)
#define WINDOW_HEIGHT	(800)

#define FIELD_SIZE		(10)

#define BALL_RADIUS		(1)

//-----------------------------------------------------------------------------
// 関数の宣言
void Init();
void Display();
void Idle();
void Exit();

void DrawAxes_(glm::f32 length);
void DrawGrid_(glm::f32 size);

//-----------------------------------------------------------------------------
// グローバル変数
myfx::RigidBody gRigidSphere;
mygx::Model gSphereModel;
myfx::RigidBody gRigidBox;
mygx::Model gBoxModel;
myfx::CollisionDetector gCollisionDetector;
myfx::ConstraintSolver gConstraintSolver;
myfx::ForceCalculator gForceCalculator;


//-----------------------------------------------------------------------------
// メイン関数
int main(int argc, char* argv[])
{
	printf("main()\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Many Cubes");
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	Init();
	glutMainLoop();

	return 0;
}

//-----------------------------------------------------------------------------
// 関数の定義
void Init()
{
	gRigidSphere.setPosition({ 0.f, 10.f, 0.f });
	gRigidSphere.setCollisionShape(new myfx::SphereShape());
	gRigidSphere.updateMomentofInertia();
	gSphereModel.setModelType(mygx::Model::Sphere);
	const auto radius = dynamic_cast<myfx::SphereShape*>(gRigidSphere.getCollisionShape())->getRadius();
	gSphereModel.setScale({ radius, radius, radius });
	gSphereModel.updateMatrix();

	gRigidBox.setPosition({ 0.f, -0.5f, 0.f });
	gRigidBox.setCollisionShape(new myfx::CubeShape({ 10.f, 1.f, 10.f }));
	gRigidBox.setMass(0.f);
	gRigidBox.updateMomentofInertia();
	gBoxModel.setModelType(mygx::Model::Box);
	const auto scale = dynamic_cast<myfx::CubeShape*>(gRigidBox.getCollisionShape())->getScale();
	gBoxModel.setScale(scale);
	gBoxModel.updateMatrix();
}


//-----------------------------------------------------------------------------
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	// プロジェクション行列の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1, 100);

	// カメラの設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::vec3 center = { 0, 0, 0 };
	glm::vec3 eye = center + glm::vec3(5, 8, 9) * 2.f;
	glm::vec3 up = { 0, 1, 0 };
	gluLookAt
	(
		eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z
	);


	// グリッドを描画
	DrawGrid_(FIELD_SIZE);

	// 軸の描画
	DrawAxes_(FIELD_SIZE / 2);
	
	// モデルの描画
	gSphereModel.draw();
	gBoxModel.draw();

	glutSwapBuffers();
}

//-----------------------------------------------------------------------------
void Idle()
{
	const glm::f32 dt = 1.f / 60.f;

	gRigidSphere.setForce(glm::zero<glm::vec3>());
	gRigidSphere.setForce(gRigidSphere.getForce() + gRigidSphere.getMass() * glm::vec3{ 0.f, -9.8f, 0.f });

	gRigidBox.setForce(glm::zero<glm::vec3>());
	gRigidSphere.setForce(gRigidSphere.getForce() + gRigidSphere.getMass() * glm::vec3{ 0.f, -9.8f, 0.f });

	const auto collision_data = gCollisionDetector.getCollisionData(gRigidBox, gRigidSphere);
	gConstraintSolver.solveConstraint(&gRigidBox, &gRigidSphere, collision_data);

	const auto impulse = gForceCalculator.getImpulse(&gRigidBox, &gRigidSphere, collision_data);
	gRigidSphere.setForce(gRigidSphere.getForce() + impulse / dt);

	gRigidSphere.stepTime(dt);
	gRigidBox.stepTime(dt);

	glm::mat4 sphere_trs = glm::translate(glm::identity<glm::mat4>(), gRigidSphere.getPosition());
	gSphereModel.setRTMatrix(sphere_trs);
	gSphereModel.updateMatrix();

	glm::mat4 box_trs = glm::translate(glm::identity<glm::mat4>(), gRigidBox.getPosition());
	gBoxModel.setRTMatrix(box_trs);
	gBoxModel.updateMatrix();

	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
void Exit()
{
	delete gRigidSphere.getCollisionShape();
}

//-----------------------------------------------------------------------------
void DrawAxes_(glm::f32 length)
{
	constexpr glm::f32	x_color[] = { 1.f, 0.f, 0.f };
	constexpr glm::f32	y_color[] = { 0.f, 1.f, 0.f };
	constexpr glm::f32	z_color[] = { 0.f, 0.f, 1.f };


	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glBegin(GL_LINES);

	glColor3fv(x_color);
	glVertex3f(0.f, 0.15f, 0.f);
	glVertex3f(length, 0.15f, 0.f);

	glColor3fv(y_color);
	glVertex3f(0.f, 0.15f, 0.f);
	glVertex3f(0.f, length, 0.f);

	glColor3fv(z_color);
	glVertex3f(0.f, 0.15f, 0.f);
	glVertex3f(0.f, 0.2f, length);

	glEnd();
}

//-----------------------------------------------------------------------------
void DrawGrid_(glm::f32 size)
{
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glBegin(GL_LINES);
	{
		glColor3f(1, 1, 1);
		for (int x = -size / 2; x <= size / 2; x++)
		{
			glVertex3f(x, 0.1f, -size / 2);
			glVertex3f(x, 0.1f, size / 2);
		}
		for (int z = -size / 2; z <= size / 2; z++)
		{
			glVertex3f(-size / 2, 0.1f, z);
			glVertex3f(size / 2, 0.1f, z);
		}
	}
	glEnd();
}

#endif