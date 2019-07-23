#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double elephantRotation = 68;
double elephantX = 0;
double elephantZ = -2;
bool up_arrow_down = false;
bool right_arrow_down = false;
bool left_arrow_down = false;
bool down_arrow_down = false;
bool elephantPOV = false;

enum game_state {
	playing,
	help,
	adjust_light
};

game_state current_state = playing;

void lighting()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	
	GLfloat light1PosType[] = { 0, 2, -14.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light1PosType);

	GLfloat red[] = { 1., 0., 0., 1. };
	GLfloat white[] = { .8, .8, .8, 1. };
	GLfloat black[] = { 0., 0., 0., 1. };
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
}

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

	// Bottom
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

void drawOtherStuff()
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

	glutSolidSphere(1, 100, 100);

	glTranslatef(-.8, .7, 0);
	glutSolidSphere(0.65, 20, 20);

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

	glPopMatrix();
	glPushMatrix();

	glTranslatef(.85, 0, 0);
	glRotatef(90, 0, 1., 0);
	glRotatef(-70, 1., 0, 0);
	
	glutSolidCone(.05, 1.3, 10, 10);

	glPopMatrix();
	glPushMatrix();

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	glTranslatef(-1.22, .72, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(80, 1, 0, 0);

	gluCylinder(quadratic, .2, .075, 1.015, 20, 20);

	glPopMatrix();
	glPushMatrix();

	quadratic = gluNewQuadric();

	glTranslatef(-1.4, -.24, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(50, 1, 0, 0);

	gluCylinder(quadratic, .08, .07, .13, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-1.1, 0.7, -.6);
	glScalef(.1, 1, .8);

	glutSolidSphere(0.7, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-1.1, 0.7, .6);
	glScalef(.1, 1, .8);

	glutSolidSphere(0.7, 20, 20);

	GLfloat ambientBlackCoeff[] = { 0., 0., 0., 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientBlackCoeff);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-1.35, .7, .22);

	glutSolidSphere(0.1, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-1.35, .7, -.22);

	glutSolidSphere(0.1, 20, 20);

	GLfloat ambientWhiteCoeff[] = { 1., 1., 1., 1. };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientWhiteCoeff);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-1.4, .72, .21);

	glutSolidSphere(0.05, 20, 20);

	glPopMatrix();
	glPushMatrix();

	glTranslatef(-1.4, .72, -.24);

	glutSolidSphere(0.05, 20, 20);

	glPopMatrix();
}

void writeText(GLfloat x, GLfloat y, void* font, const char* text)
{
	// Write a continuous segment of text in a certain font and location
	glRasterPos2f(x, y);
	while (*text)
	{
		glutBitmapCharacter(font, *text);
		text++;
	}
}

void set_projection(GLint width, GLint height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, (float)width / height, 0.1, 50);
}

void reshape(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	set_projection(newWidth, newHeight);
}


void display2D()
{
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, glutGet(GLUT_SCREEN_WIDTH), 0, glutGet(GLUT_SCREEN_HEIGHT));

	glColor3f(.95, .95, .95);
	writeText(25, SCREEN_HEIGHT - 50, GLUT_BITMAP_HELVETICA_18, "HELP");
	writeText(25, SCREEN_HEIGHT - 100, GLUT_BITMAP_HELVETICA_18, "ADJUST AMBIENT LIGHT");
	writeText(25, SCREEN_HEIGHT - 150, GLUT_BITMAP_HELVETICA_18, "QUIT");

	glBegin(GL_LINES);

	glVertex2d(35, SCREEN_HEIGHT - 67);
	glVertex2d(245, SCREEN_HEIGHT - 67);
	glVertex2d(35, SCREEN_HEIGHT - 117);
	glVertex2d(245, SCREEN_HEIGHT - 117);

	glEnd();

	glColor4f(.2, .2, .45, 0.35);
	glBegin(GL_POLYGON);

	glVertex2d(20, SCREEN_HEIGHT - 20);
	glVertex2d(300, SCREEN_HEIGHT - 20);
	glVertex2d(300, SCREEN_HEIGHT - 160);
	glVertex2d(20, SCREEN_HEIGHT - 160);

	glEnd();

	if (current_state == help)
	{
		glColor3f(.95, .95, .95);
		writeText(110, SCREEN_HEIGHT - 220, GLUT_BITMAP_HELVETICA_18, 
			"Use arrow keys to move: UP = forward, DOWN = backward, RIGHT / LEFT = turn");

		writeText(110, SCREEN_HEIGHT - 270, GLUT_BITMAP_HELVETICA_18, 
			"Press SPACE to toggle between fixed camera and first-elephant point of view");

		writeText(110, SCREEN_HEIGHT - 420, GLUT_BITMAP_HELVETICA_18, "Press ESC to return to game");

		glColor4f(.2, .2, .45, 0.55);
		glBegin(GL_POLYGON);

		glVertex2d(100, SCREEN_HEIGHT - 200);
		glVertex2d(950, SCREEN_HEIGHT - 200);
		glVertex2d(950, 100);
		glVertex2d(100, 100);

		glEnd();
	}
	else if (current_state == adjust_light)
	{
		glColor3f(.95, .95, .95);
		writeText(110, SCREEN_HEIGHT - 220, GLUT_BITMAP_HELVETICA_18,
			"Adjusting ambient light (press ESC to return to game)");

		writeText(110, SCREEN_HEIGHT - 270, GLUT_BITMAP_HELVETICA_18,
			"Use arrows: RIGHT / LEFT to choose color and UP / DOWN to adjust magnitude");

		glColor4f(.2, .2, .45, 0.55);
		glBegin(GL_POLYGON);

		glVertex2d(100, SCREEN_HEIGHT - 200);
		glVertex2d(950, SCREEN_HEIGHT - 200);
		glVertex2d(950, 100);
		glVertex2d(100, 100);

		glEnd();
	}

	glEnable(GL_LIGHTING);
}

void display()
{
	set_projection(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (!elephantPOV)
	{
		gluLookAt(4, 3.5, -14.5, elephantX, -3.9, elephantZ, 0, 1, 0);
	}
	else
	{
		double lookAtX = elephantX - cos(elephantRotation * M_PI / 180);
		double lookAtZ = elephantZ + sin(elephantRotation * M_PI / 180);
		gluLookAt(elephantX, -2, elephantZ, lookAtX, -2, lookAtZ, 0, 1, 0);
	}
	
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();
	lighting();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	drawRoom();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	drawOtherStuff();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	drawElephant();

	display2D();

	glFlush();
}


void timer(int v)
{
	double step_size = 0.2;

	if (up_arrow_down || down_arrow_down)
	{
		int coeff = down_arrow_down ? -1 : 1;
		elephantX -= coeff * step_size * cos(elephantRotation * M_PI / 180);
		elephantZ += coeff * step_size * sin(elephantRotation * M_PI / 180);

		if (elephantX <= -8.5)
		{
			elephantX = -8.5;
		}

		if (elephantX >= 8.5)
		{
			elephantX = 8.5;
		}

		if (elephantZ <= -13.5)
		{
			elephantZ = -13.5;
		}

		if (elephantZ >= -1.5)
		{
			elephantZ = -1.5;
		}
	}

	if (right_arrow_down)
	{
		elephantRotation -= 4;
	}

	if (left_arrow_down)
	{
		elephantRotation += 4;
	}

	glutPostRedisplay();
	glutTimerFunc(25, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (current_state == playing)
	{
		if (key == ' ')
		{
			elephantPOV = !elephantPOV;
		}
	}
	else if ((current_state == help || current_state == adjust_light) && (int)key == 27) // ESC key
	{
		current_state = playing;
	}
}

void special_keyboard_down(int key, int x, int y)
{
	if (current_state == playing)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			up_arrow_down = true;
			break;
		case GLUT_KEY_RIGHT:
			right_arrow_down = true;
			break;
		case GLUT_KEY_LEFT:
			left_arrow_down = true;
			break;
		case GLUT_KEY_DOWN:
			down_arrow_down = true;
			break;
		default:

			break;
		}
	}
}

void special_keyboard_up(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		up_arrow_down = false;
		break;
	case GLUT_KEY_RIGHT:
		right_arrow_down = false;
		break;
	case GLUT_KEY_LEFT:
		left_arrow_down = false;
		break;
	case GLUT_KEY_DOWN:
		down_arrow_down = false;
		break;
	default:

		break;
	}
}

void mouse(GLint button, GLint action, GLint x, GLint y)
{
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	y = SCREEN_HEIGHT - y;
	if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 150 && y < SCREEN_HEIGHT - 100)
	{
		exit(0);
	}
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 50)
	{
		current_state = help;
	}
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 100 && y < SCREEN_HEIGHT - 50)
	{
		current_state = adjust_light;
	}
}

int main(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 700);
	glutInitWindowPosition(50, 50);
	glutInit(&argc, argv);
	glutCreateWindow("Elephant in a china shop");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRange(0.0f, 1.0f);
	
	glEnable(GL_NORMALIZE);

	glClearColor(0.98, 0.98, 0.93, 0.);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(25, timer, 0);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard_down);
	glutSpecialUpFunc(special_keyboard_up);
	glutMouseFunc(mouse);

	glutMainLoop();

	return 0;
}


/*

TODO
====

Tuesday:
- menus: adjust ambient light - 5h

Wednesday:
- move elephant head by keyboard - 3h
- move tail by keyboard - 2h

Weekend:
- light direction - 1h
- allow user to adjust light magnitude, location and direction - 3h
- allow use to control camera location - 2h
- doc - 3h

*/