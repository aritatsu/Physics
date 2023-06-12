#if 1

#include "PhysicsWorld.h"

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
myfx::RigidBody gRigidBox1;
myfx::RigidBody gRigidBox2;
mygx::Model gBoxModel1;
mygx::Model gBoxModel2;
myfx::PhysicsWorld gPhysicsWorld;
float camera_radius = 30.f;
float camera_latitude = glm::pi<glm::f32>() / 6;
float camera_longigtude = glm::pi<glm::f32>() / 4;


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
	gRigidSphere.setPosition({ 0.f, 1.f, 0.f });
	gRigidSphere.setMass(1.f);
	gRigidSphere.setCollisionShape(new myfx::SphereShape());
	gRigidSphere.updateMomentofInertia();
	gRigidSphere.setRestitution(0.5f);
	gRigidSphere.setFriction(0.4f);
	//gRigidSphere.setAngularVelocity({ 1.f, 0.f, 0.f });
	//gRigidSphere.setForce({50.f, 0.f, 0.f});
	gPhysicsWorld.addRigidBody(&gRigidSphere);
	gSphereModel.setModelType(mygx::Model::Sphere);
	const auto radius = dynamic_cast<myfx::SphereShape*>(gRigidSphere.getCollisionShape())->getRadius();
	gSphereModel.setScale({ radius, radius, radius });
	gSphereModel.updateMatrix();

	gRigidBox1.setPosition({ 0.f, -0.5f, 0.f });
	gRigidBox1.setRotation(myfx::Rotate(gRigidBox1.getRotation(), { 1.0, 0.f, 0.f }, glm::pi<glm::f32>() / 4));
	//gRigidBox.setAngularVelocity({ 1.f, 0.f, 0.f });
	gRigidBox1.setCollisionShape(new myfx::CubeShape({ 20.f, 1.f, 20.f }));
	gRigidBox1.setMass(0.f);
	gRigidBox1.updateMomentofInertia();
	gPhysicsWorld.addRigidBody(&gRigidBox1);
	gBoxModel1.setModelType(mygx::Model::Box);
	const auto scale1 = dynamic_cast<myfx::CubeShape*>(gRigidBox1.getCollisionShape())->getScale();
	gBoxModel1.setScale(scale1);
	gBoxModel1.updateMatrix();

	gRigidBox2.setPosition({ 0.f, -3.f, 3.f });
	gRigidBox2.setRotation(myfx::Rotate(gRigidBox2.getRotation(), { 1.0, 0.f, 0.f }, -glm::pi<glm::f32>() / 4));
	//gRigidBox.setAngularVelocity({ 1.f, 0.f, 0.f });
	gRigidBox2.setCollisionShape(new myfx::CubeShape({ 20.f, 1.f, 20.f }));
	gRigidBox2.setMass(0.f);
	gRigidBox2.updateMomentofInertia();
	gPhysicsWorld.addRigidBody(&gRigidBox2);
	gBoxModel2.setModelType(mygx::Model::Box);
	const auto scale2 = dynamic_cast<myfx::CubeShape*>(gRigidBox2.getCollisionShape())->getScale();
	gBoxModel2.setScale(scale2);
	gBoxModel2.updateMatrix();
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
	glm::f32 camera_x = camera_radius * glm::sin(camera_longigtude) * glm::cos(camera_latitude);
	glm::f32 camera_y = camera_radius * glm::sin(camera_latitude);
	glm::f32 camera_z = camera_radius * glm::cos(camera_longigtude) * glm::cos(camera_latitude);
	//camera_longigtude += glm::pi<glm::f32>() / 180.f;
	glm::vec3 eye = center + glm::vec3(camera_x, camera_y, camera_z) ;
	glm::vec3 up = { 0, 1, 0 };
	gluLookAt
	(
		eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z
	);


	// グリッドを描画
	//DrawGrid_(FIELD_SIZE);

	// 軸の描画
	DrawAxes_(FIELD_SIZE / 2);
	
	// モデルの描画
	gSphereModel.draw();
	gBoxModel1.draw();
	gBoxModel2.draw();

	glutSwapBuffers();
}

//-----------------------------------------------------------------------------
void Idle()
{
#if 0
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
#endif
	
	gPhysicsWorld.updateWorld();

	glm::mat4 sphere_trs{ glm::translate(glm::identity<glm::mat4>(), gRigidSphere.getPosition()) };
	glm::mat4 sphere_rot{ gRigidSphere.getRotation() };
	gSphereModel.setRTMatrix(sphere_trs * sphere_rot);
	gSphereModel.updateMatrix();

	glm::mat4 box_trs1{ glm::translate(glm::identity<glm::mat4>(), gRigidBox1.getPosition()) };
	glm::mat4 box_rot1{ gRigidBox1.getRotation() };
	gBoxModel1.setRTMatrix(box_trs1 * box_rot1);
	gBoxModel1.updateMatrix();

	glm::mat4 box_trs2{ glm::translate(glm::identity<glm::mat4>(), gRigidBox2.getPosition()) };
	glm::mat4 box_rot2{ gRigidBox2.getRotation() };
	gBoxModel2.setRTMatrix(box_trs2 * box_rot2);
	gBoxModel2.updateMatrix();

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