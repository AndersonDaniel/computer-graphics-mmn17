#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double elephantRotation = 68;
double elephantX = 0;
double elephantZ = -2;

double lightX = 0;
double lightY = 2;
double lightZ = -14.5;
double lightRotationY = 90;
double lightRotationZ = 270;

bool up_arrow_down = false;
bool right_arrow_down = false;
bool left_arrow_down = false;
bool down_arrow_down = false;
bool space_down = false;
bool tail_up = false;
bool tail_down = false;
bool tail_right = false;
bool tail_left = false;
bool head_up = false;
bool head_down = false;
bool head_right = false;
bool head_left = false;
bool elephantPOV = false;

double ambientRed = .8;
double ambientGreen = .8;
double ambientBlue = .8;

double diffuseRed = .8;
double diffuseGreen = .8;
double diffuseBlue = .8;

double *targetRed, *targetGreen, *targetBlue;

double tailRotationY = 90;
double tailRotationX = -70;

double headRotationY = 0;
double headRotationZ = 0;

enum game_state {
	playing,
	help,
	adjust_light
};

enum color {
	red, green, blue
};

enum light_type {
	ambient,
	diffuse
};

game_state current_state = playing;
color adjusting_color = red;
light_type currently_adjusting_light = ambient;

void lighting()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	
	GLfloat light1PosType[] = { lightX, lightY, lightZ, 1.0 };
	GLfloat lightDirection[] = { cos(lightRotationY * M_PI / 180.), 
								 cos(lightRotationZ * M_PI / 180.),
								 sin(lightRotationY * M_PI / 180.) };
	glLightfv(GL_LIGHT0, GL_POSITION, light1PosType);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);

	GLfloat red[] = { 1., 0., 0., 1. };
	GLfloat white[] = { .8, .8, .8, 1. };
	GLfloat ambient[] = { ambientRed, ambientGreen, ambientBlue, 1. };
	GLfloat diffuse[] = { diffuseRed, diffuseGreen, diffuseBlue };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
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

void displayMenu(const int SCREEN_HEIGHT)
{
	glColor3f(.95, .95, .95);
	writeText(25, SCREEN_HEIGHT - 50, GLUT_BITMAP_HELVETICA_18, "HELP");
	writeText(25, SCREEN_HEIGHT - 100, GLUT_BITMAP_HELVETICA_18, "ADJUST AMBIENT LIGHT");
	writeText(25, SCREEN_HEIGHT - 150, GLUT_BITMAP_HELVETICA_18, "ADJUST LIGHT SOURCE");
	writeText(25, SCREEN_HEIGHT - 200, GLUT_BITMAP_HELVETICA_18, "QUIT");

	glBegin(GL_LINES);

	glVertex2d(35, SCREEN_HEIGHT - 67);
	glVertex2d(245, SCREEN_HEIGHT - 67);
	glVertex2d(35, SCREEN_HEIGHT - 117);
	glVertex2d(245, SCREEN_HEIGHT - 117);
	glVertex2d(35, SCREEN_HEIGHT - 167);
	glVertex2d(245, SCREEN_HEIGHT - 167);

	glEnd();

	glColor4f(.2, .2, .45, 0.35);
	glBegin(GL_POLYGON);

	glVertex2d(20, SCREEN_HEIGHT - 20);
	glVertex2d(300, SCREEN_HEIGHT - 20);
	glVertex2d(300, SCREEN_HEIGHT - 220);
	glVertex2d(20, SCREEN_HEIGHT - 220);

	glEnd();
}

void displayHelp(const int SCREEN_HEIGHT)
{
	glColor3f(.95, .95, .95);
	writeText(110, SCREEN_HEIGHT - 320, GLUT_BITMAP_HELVETICA_18,
		"Use arrow keys to move: UP = forward, DOWN = backward, RIGHT / LEFT = turn");

	writeText(110, SCREEN_HEIGHT - 370, GLUT_BITMAP_HELVETICA_18,
		"Press SPACE to toggle between fixed camera and first-elephant point of view");

	writeText(110, SCREEN_HEIGHT - 420, GLUT_BITMAP_HELVETICA_18,
		"Head movement: use ASDW; w = up, s = down, a = left, d = right");

	writeText(110, SCREEN_HEIGHT - 470, GLUT_BITMAP_HELVETICA_18,
		"Tail movement: use JKLI; i = up, k = down, j = left, l = right");

	writeText(110, SCREEN_HEIGHT - 520, GLUT_BITMAP_HELVETICA_18, "Press ESC to return to game");

	glColor4f(.2, .2, .45, 0.55);
	glBegin(GL_POLYGON);

	glVertex2d(100, SCREEN_HEIGHT - 300);
	glVertex2d(950, SCREEN_HEIGHT - 300);
	glVertex2d(950, 50);
	glVertex2d(100, 50);

	glEnd();
}

void displayAdjustLight(const int SCREEN_HEIGHT)
{
	glColor3f(.95, .95, .95);

	if (currently_adjusting_light == ambient)
	{
		writeText(110, SCREEN_HEIGHT - 320, GLUT_BITMAP_HELVETICA_18,
			"Adjusting ambient light (press ESC to return to game)");
	}
	else
	{
		writeText(110, SCREEN_HEIGHT - 320, GLUT_BITMAP_HELVETICA_18,
			"Adjusting light source (press ESC to return to game)");
	}
	

	writeText(110, SCREEN_HEIGHT - 370, GLUT_BITMAP_HELVETICA_18,
		"Use arrows: RIGHT / LEFT to choose color and UP / DOWN to adjust magnitude");

	if (currently_adjusting_light == diffuse)
	{
		writeText(110, SCREEN_HEIGHT - 420, GLUT_BITMAP_HELVETICA_18,
			"Use ASDW to adjust light direction and SPACE to move light in its direction");
	}

	glColor3f(.9, .9, .9);

	glBegin(GL_LINE_LOOP);

	glVertex2d(300, 250);
	glVertex2d(300, 370);
	glVertex2d(350, 370);
	glVertex2d(350, 250);

	glEnd();

	glBegin(GL_LINE_LOOP);

	glVertex2d(500, 250);
	glVertex2d(500, 370);
	glVertex2d(550, 370);
	glVertex2d(550, 250);

	glEnd();

	glBegin(GL_LINE_LOOP);

	glVertex2d(700, 250);
	glVertex2d(700, 370);
	glVertex2d(750, 370);
	glVertex2d(750, 250);

	glEnd();

	glColor4f(1., 0., 0., .6);

	glBegin(GL_POLYGON);

	int maxRedY = 251 + (int)(*targetRed * 118);
	glVertex2d(300, 250);
	glVertex2d(300, maxRedY);
	glVertex2d(350, maxRedY);
	glVertex2d(350, 250);

	glEnd();

	glColor4f(0., 1., 0., .6);

	glBegin(GL_POLYGON);

	int maxGreenY = 251 + (int)(*targetGreen * 118);
	glVertex2d(500, 250);
	glVertex2d(500, maxGreenY);
	glVertex2d(550, maxGreenY);
	glVertex2d(550, 250);

	glEnd();

	glColor4f(0., 0., 1., .6);

	glBegin(GL_POLYGON);

	int maxBlueY = 251 + (int)(*targetBlue * 118);
	glVertex2d(700, 250);
	glVertex2d(700, maxBlueY);
	glVertex2d(750, maxBlueY);
	glVertex2d(750, 250);

	glEnd();

	glColor3f(.9, .9, .9);

	glBegin(GL_POLYGON);

	int colorSelectionX = 300 + 200 * (adjusting_color == red ? 0 : adjusting_color == green ? 1 : 2);
	glVertex2d(colorSelectionX, 190);
	glVertex2d(colorSelectionX + 50, 190);
	glVertex2d(colorSelectionX + 25, 240);

	glEnd();

	glColor4f(.2, .2, .45, 0.4);
	glBegin(GL_POLYGON);

	glVertex2d(100, SCREEN_HEIGHT - 300);
	glVertex2d(950, SCREEN_HEIGHT - 300);
	glVertex2d(950, 50);
	glVertex2d(100, 50);

	glEnd();

	
}

void display2D()
{
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, glutGet(GLUT_SCREEN_WIDTH), 0, SCREEN_HEIGHT);

	displayMenu(SCREEN_HEIGHT);

	if (current_state == help)
	{
		displayHelp(SCREEN_HEIGHT);
	}
	else if (current_state == adjust_light)
	{
		displayAdjustLight(SCREEN_HEIGHT);
	}

	glEnable(GL_LIGHTING);
}

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

void display()
{
	set_projection(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double lookAtX = elephantX;
	double lookAtY = -3.9;
	double lookAtZ = elephantZ;

	double cameraX;
	double cameraY;
	double cameraZ;

	if (!elephantPOV)
	{
		cameraX = 4;
		cameraY = 3.5;
		cameraZ = -14.5;
	}
	else
	{
		lookAtX = elephantX - cos((elephantRotation + headRotationY) * M_PI / 180);
		lookAtY = -2 - sin(headRotationZ * M_PI / 180);
		lookAtZ = elephantZ + sin((elephantRotation + headRotationY) * M_PI / 180);

		cameraX = elephantX + 4.5 * (lookAtX - elephantX) / 12.;
		cameraY = -2 + 4.5 * (lookAtY + 2) / 12.;
		cameraZ = elephantZ + 4.5 * (lookAtZ - elephantZ) / 12.;
	}

	if (current_state == adjust_light && currently_adjusting_light == diffuse)
	{
		lookAtX = lightX;
		lookAtY = lightY;
		lookAtZ = lightZ;
	}

	gluLookAt(cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, 0, 1, 0);
	
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();
	lighting();
	

	glPopMatrix();
	glPushMatrix();

	drawRoom();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	drawOtherStuff();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPushMatrix();

	drawElephant();

	if (current_state == adjust_light && currently_adjusting_light == diffuse)
	{
		glPopMatrix();
		glPushMatrix();
		drawLight();
	}

	glPopMatrix();

	display2D();

	glFlush();
}


void timer(int v)
{
	if (current_state == playing)
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
		else if (left_arrow_down)
		{
			elephantRotation += 4;
		}

		if (tail_up)
		{
			tailRotationX -= 2;
			if (tailRotationX < -80)
			{
				tailRotationX = -80;
			}
		}
		else if (tail_down)
		{
			tailRotationX += 2;
			if (tailRotationX > 45)
			{
				tailRotationX = 45;
			}
		}

		if (tail_right)
		{
			tailRotationY += 2;
			if (tailRotationY > 135)
			{
				tailRotationY = 135;
			}
		}
		else if (tail_left)
		{
			tailRotationY -= 2;
			if (tailRotationY < 45)
			{
				tailRotationY = 45;
			}
		}

		if (head_up)
		{
			headRotationZ -= 2;
			if (headRotationZ < -60)
			{
				headRotationZ = -60;
			}
		}
		else if (head_down)
		{
			headRotationZ += 2;
			if (headRotationZ > 20)
			{
				headRotationZ = 20;
			}
		}

		if (head_right)
		{
			headRotationY -= 2;
			if (headRotationY < -45)
			{
				headRotationY = -45;
			}

		}
		else if (head_left)
		{
			headRotationY += 2;
			if (headRotationY > 45)
			{
				headRotationY = 45;
			}
		}
	}
	else if (current_state == adjust_light)
	{
		double light_step_size = 0.01;
		double* adjusting_color_variable = adjusting_color == red ? targetRed : adjusting_color == green ? targetGreen : targetBlue;
		if (up_arrow_down)
		{
			*adjusting_color_variable += light_step_size;
			if (*adjusting_color_variable > 1)
			{
				*adjusting_color_variable = 1.;
			}
		}
		else if (down_arrow_down)
		{
			*adjusting_color_variable -= light_step_size;
			if (*adjusting_color_variable < 0)
			{
				*adjusting_color_variable = 0;
			}
		}

		if (head_down)
		{
			lightRotationZ -= 2;
			if (lightRotationZ < 225)
			{
				lightRotationZ = 225;
			}
		}
		else if (head_up)
		{
			lightRotationZ += 2;
			if (lightRotationZ > 305)
			{
				lightRotationZ = 305;
			}
		}

		if (head_right)
		{
			lightRotationY += 2;
		}
		else if (head_left)
		{
			lightRotationY -= 2;
		}

		if (space_down)
		{
			double light_movement_step_size = 0.1;
			lightX += light_movement_step_size * cos(lightRotationY * M_PI / 180.);
			lightY += light_movement_step_size * cos(lightRotationZ * M_PI / 180.);
			lightZ += light_movement_step_size * sin(lightRotationY * M_PI / 180.);

			if (lightX < -10)
			{
				lightX = 10;
			}
			else if (lightX > 10)
			{
				lightX = -10;
			}

			if (lightY < -5)
			{
				lightY = 5;
			}
			else if (lightY > 5)
			{
				lightY = -5;
			}

			if (lightZ < -15)
			{
				lightZ = 0;
			}
			else if (lightZ > 0)
			{
				lightZ = -15;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(25, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (current_state == playing || (current_state == adjust_light && currently_adjusting_light == diffuse))
	{
		switch (key)
		{
		case ' ':
			if (current_state == playing)
			{
				elephantPOV = !elephantPOV;
			}
			
			space_down = true;
			break;
		case 'i':
			tail_up = true;
			break;
		case 'k':
			tail_down = true;
			break;
		case 'j':
			tail_left = true;
			break;
		case 'l':
			tail_right = true;
			break;
		case 'w':
			head_up = true;
			break;
		case 's':
			head_down = true;
			break;
		case 'a':
			head_left = true;
			break;
		case 'd':
			head_right = true;
			break;
		default:
			break;
		}
	}

	if ((current_state == help || current_state == adjust_light) && (int)key == 27) // ESC key
	{
		current_state = playing;
	}
}

void keyboard_up(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		space_down = false;
		break;
	case 'i':
		tail_up = false;
		break;
	case 'k':
		tail_down = false;
		break;
	case 'j':
		tail_left = false;
		break;
	case 'l':
		tail_right = false;
		break;
	case 'w':
		head_up = false;
		break;
	case 's':
		head_down = false;
		break;
	case 'a':
		head_left = false;
		break;
	case 'd':
		head_right = false;
		break;
	default:
		break;
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
	else if (current_state == adjust_light)
	{
		int current_color = adjusting_color == red ? 0 : adjusting_color == green ? 1 : 2;
		switch (key)
		{
		case GLUT_KEY_RIGHT:
			current_color += 1;
			break;
		case GLUT_KEY_LEFT:
			current_color -= 1;
			break;
		case GLUT_KEY_UP:
			up_arrow_down = true;
			break;
		case GLUT_KEY_DOWN:
			down_arrow_down = true;
			break;
		default:
			break;
		}

		current_color = current_color % 3;
		adjusting_color = current_color == 0 ? red : current_color == 1 ? green : blue;
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
	if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 180 && y < SCREEN_HEIGHT - 140)
	{
		exit(0);
	}
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 60 && y < SCREEN_HEIGHT - 20)
	{
		current_state = help;
	}
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 100 && y < SCREEN_HEIGHT - 60)
	{
		current_state = adjust_light;
		currently_adjusting_light = ambient;
		targetRed = &ambientRed;
		targetGreen = &ambientGreen;
		targetBlue = &ambientBlue;
	}
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 140 && y < SCREEN_HEIGHT - 100)
	{
		current_state = adjust_light;
		currently_adjusting_light = diffuse;
		targetRed = &diffuseRed;
		targetGreen = &diffuseGreen;
		targetBlue = &diffuseBlue;
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
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(special_keyboard_down);
	glutSpecialUpFunc(special_keyboard_up);
	glutMouseFunc(mouse);

	glutMainLoop();

	return 0;
}


/*

TODO
====

Weekend:
- allow use to control camera location - 2h
- doc - 3h

*/