#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>
#include "drawing.h"


// Produce checker-board style floor tiles
void drawFloor()
{
	GLfloat ambientWhiteCoeff[] = { 0.55, 0.55, 0.55, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientWhiteCoeff);
	GLfloat specularCoeff[] = { 0.9, 0.9, 0.9, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);

	const int TILES_SIDE = 20;
	double tile_length_x = 20 / TILES_SIDE;
	double tile_length_z = 15. / TILES_SIDE;
	const double FRAME_DEPTH = 0.1;
	const double TILE_LEVITATION = 0.05;

	// White tiles
	for (int i = 0; i < TILES_SIDE; i++)
	{
		for (int j = i % 2; j < TILES_SIDE; j += 2)
		{
			glNormal3f(0., 1., 0.);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glEnd();

			glNormal3f(-TILE_LEVITATION, FRAME_DEPTH, 0.);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glEnd();

			glNormal3f(0., FRAME_DEPTH, -TILE_LEVITATION);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glEnd();

			glNormal3f(TILE_LEVITATION, FRAME_DEPTH, 0.);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glEnd();

			glNormal3f(0., FRAME_DEPTH, TILE_LEVITATION);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glEnd();
		}
	}

	GLfloat ambientBlackCoeff[] = { 0.2, 0.2, 0.2, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientBlackCoeff);

	// Black tiles
	for (int i = 0; i < TILES_SIDE; i++)
	{
		for (int j = 1 - i % 2; j < TILES_SIDE; j += 2)
		{
			glNormal3f(0., 1., 0.);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glEnd();

			glNormal3f(-TILE_LEVITATION, FRAME_DEPTH, 0.);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glEnd();

			glNormal3f(0., FRAME_DEPTH, -TILE_LEVITATION);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glEnd();

			glNormal3f(TILE_LEVITATION, FRAME_DEPTH, 0.);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * (j + 1));
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * (j + 1) - FRAME_DEPTH);
			glEnd();

			glNormal3f(0., FRAME_DEPTH, TILE_LEVITATION);
			glBegin(GL_POLYGON);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i + FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glVertex3d(-10 + tile_length_x * i, -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * (i + 1), -5, -15 + tile_length_z * j);
			glVertex3d(-10 + tile_length_x * (i + 1) - FRAME_DEPTH, -5 + TILE_LEVITATION, -15 + tile_length_z * j + FRAME_DEPTH);
			glEnd();
		}
	}
}

void drawRoom()
{
	GLfloat ambientCoeff[] = { 0.408, 0.408, 0.387, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientCoeff);
	GLfloat specularCoeff[] = { 0.8, 0.8, 0., 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);


	glNormal3f(0., 0., -1.);
	glBegin(GL_POLYGON);
	glVertex3d(10, -5, 0);
	glVertex3d(10, 5, 0);
	glVertex3d(-10, 5, 0);
	glVertex3d(-10, -5, 0);
	glVertex3d(10, -5, 0);
	glEnd();

	glNormal3f(0., 0., 1.);
	glBegin(GL_POLYGON);
	glVertex3d(10, -5, -15);
	glVertex3d(10, 5, -15);
	glVertex3d(-10, 5, -15);
	glVertex3d(-10, -5, -15);
	glVertex3d(10, -5, -15);
	glEnd();

	// Left
	glNormal3f(-1., 0., 0.);
	glBegin(GL_POLYGON);
	glVertex3d(10, -5, -15);
	glVertex3d(10, 5, -15);
	glVertex3d(10, 5, 0);
	glVertex3d(10, -5, 0);
	glVertex3d(10, -5, -15);
	glEnd();

	// Right
	glNormal3f(1., 0., 0.);
	glBegin(GL_POLYGON);
	glVertex3d(-10, -5, -15);
	glVertex3d(-10, 5, -15);
	glVertex3d(-10, 5, 0);
	glVertex3d(-10, -5, 0);
	glVertex3d(-10, -5, -15);
	glEnd();

	// Top
	glNormal3f(0., -1., 0.);
	glBegin(GL_POLYGON);
	glVertex3d(10, 5, -15);
	glVertex3d(10, 5, 0);
	glVertex3d(-10, 5, 0);
	glVertex3d(-10, 5, -15);
	glVertex3d(10, 5, -15);
	glEnd();

	drawFloor();
}

void drawTeapot()
{
	glTranslatef(-2.5, -4.2, -2.);
	glRotatef(120, 0, 1, 0);

	GLfloat ambientCoeff[] = { 0.1, 0.3, 0.1, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientCoeff);
	GLfloat specularCoeff[] = { 0.8, 0.8, 0.8, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.);

	glutSolidTeapot(1.);
}

void drawPlate()
{
	GLfloat ambientCoeff[] = { 0.3, 0.1, 0.1, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientCoeff);
	GLfloat specularCoeff[] = { 0.9, 0.9, 0.9, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.);

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	glPushMatrix();

	glTranslatef(-2, -4.94, -12);
	glRotatef(-90, 1, 0, 0);

	gluDisk(quadratic, 0, .8, 20, 20);

	glPopMatrix();

	glTranslatef(-2, -4.64, -12);
	glRotatef(90, 1, 0, 0);

	quadratic = gluNewQuadric();
	gluQuadricOrientation(quadratic, GLU_INSIDE);
	gluCylinder(quadratic, 1.3, 0.8, 0.3, 20, 20);
}

void drawBowl()
{
	GLfloat ambientCoeff[] = { 0.1, 0.1, 0.3, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientCoeff);
	GLfloat specularCoeff[] = { 0.9, 0.9, 0.9, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.);

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	glPushMatrix();

	glTranslatef(4, -4.94, -6);
	glRotatef(-90, 1, 0, 0);

	gluDisk(quadratic, 0, .6, 20, 20);

	glPopMatrix();

	glTranslatef(4, -4.04, -6);
	glRotatef(90, 1, 0, 0);

	quadratic = gluNewQuadric();
	gluQuadricOrientation(quadratic, GLU_INSIDE);
	gluCylinder(quadratic, 0.9, 0.6, 0.9, 20, 20);
}

void drawChinaWares()
{
	glPushMatrix();

	drawTeapot();

	glPopMatrix();
	glPushMatrix();

	drawPlate();

	glPopMatrix();

	drawBowl();
}

void drawElephant()
{
	glTranslatef(elephantX, -3.9, elephantZ);
	glRotatef(elephantRotation, 0, 1, 0);

	glPushMatrix();

	GLfloat ambientCoeff[] = { 0.4, 0.35, 0.4, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientCoeff);
	GLfloat specularCoeff[] = { 0.5, 0.5, 0.5, 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.);

	glutSolidSphere(1, 100, 100); // Body

	 // Head
	glTranslatef(-.8, .7, 0);
	glRotatef(headRotationY, 0, 1, 0);
	glRotatef(headRotationZ, 0, 0, 1);

	glPushMatrix();

	glutSolidSphere(0.65, 20, 20);

	// Trunk
	glPopMatrix();
	glPushMatrix();

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	glTranslatef(-0.42, .02, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(80, 1, 0, 0);

	gluCylinder(quadratic, .2, .075, 1.015, 20, 20);

	glPopMatrix();
	glPushMatrix();

	quadratic = gluNewQuadric();

	glTranslatef(-0.6, -.94, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(50, 1, 0, 0);

	gluCylinder(quadratic, .08, .07, .13, 20, 20);

	glPopMatrix();
	glPushMatrix();

	// Ears
	glTranslatef(-0.3, 0., -.6);
	glScalef(.1, 1, .8);

	glutSolidSphere(0.7, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-0.3, 0., .6);
	glScalef(.1, 1, .8);

	glutSolidSphere(0.7, 20, 20);

	// Eyes
	GLfloat ambientBlackCoeff[] = { 0., 0., 0., 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientBlackCoeff);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-0.55, 0., .22);

	glutSolidSphere(0.1, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-0.55, 0., -.22);

	glutSolidSphere(0.1, 20, 20);

	GLfloat ambientWhiteCoeff[] = { 1., 1., 1., 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientWhiteCoeff);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-0.6, .02, .21);

	glutSolidSphere(0.05, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-0.6, .02, -.24);

	glutSolidSphere(0.05, 20, 20);

	glPopMatrix();

	// Legs
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientCoeff);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(.5, -.9, .4);
	glutSolidSphere(0.3, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-.5, -.9, .4);
	glutSolidSphere(0.3, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(.5, -.9, -.4);
	glutSolidSphere(0.3, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-.5, -.9, -.4);
	glutSolidSphere(0.3, 20, 20);

	// Tail
	glPopMatrix();
	glPushMatrix();

	glTranslatef(.85, 0, 0);
	glRotatef(tailRotationY, 0, 1, 0);
	glRotatef(tailRotationX, 1, 0, 0);

	glutSolidCone(.05, 1.3, 10, 10);

	glPopMatrix();
}

// Visualize light source as a sphere + line in the spotlight direction
void drawLight()
{
	glTranslatef(lightX, lightY, lightZ);

	glColor3f(1., 1., 1.);

	glutSolidSphere(1, 20, 20);

	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);

	glVertex3d(0, 0, 0);
	glVertex3d(4 * cos(lightRotationY * M_PI / 180.),
		4 * cos(lightRotationZ * M_PI / 180.),
		4 * sin(lightRotationY * M_PI / 180.));

	glEnd();

	glEnable(GL_LIGHTING);
}
