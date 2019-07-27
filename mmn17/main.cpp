#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "enums.h"
#include "drawing.h"
#include "menus.h"

// Global definitions
double elephantRotation = 68;
double elephantX = 0;
double elephantZ = -2;

double tailRotationY = 90;
double tailRotationX = -70;

double headRotationY = 0;
double headRotationZ = 0;

double lightX = 0;
double lightY = 2;
double lightZ = -14.5;
double lightRotationY = 90;
double lightRotationZ = 270;

double cameraX = 4;
double cameraY = 3.5;
double cameraZ = -14.5;
double cameraRotationY = 90;
double cameraRotationZ = 225;

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

bool autofocus = true;
bool elephantPOV = false;

double ambientRed = .8;
double ambientGreen = .8;
double ambientBlue = .8;

double diffuseRed = .8;
double diffuseGreen = .8;
double diffuseBlue = .8;

double *targetRed, *targetGreen, *targetBlue;

game_state current_state = playing;
color adjusting_color = red;
light_type currently_adjusting_light = ambient;

// Define light: ambient + spotlight (diffuse + specular)
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
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 75.);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);

	GLfloat white[] = { .8, .8, .8, 1. };
	GLfloat ambient[] = { ambientRed, ambientGreen, ambientBlue, 1. };
	GLfloat diffuse[] = { diffuseRed, diffuseGreen, diffuseBlue };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
}

// Set view projection with perspective transform
void set_projection(GLint width, GLint height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, (float)width / height, 0.1, 50);
}

// Handle screen resize
void reshape(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	set_projection(newWidth, newHeight);
}

void setupCamera()
{
	double lookAtX = elephantX;
	double lookAtY = -3.9;
	double lookAtZ = elephantZ;

	double local_cameraX;
	double local_cameraY;
	double local_cameraZ;

	if (!elephantPOV)
	{
		local_cameraX = cameraX;
		local_cameraY = cameraY;
		local_cameraZ = cameraZ;

		if (!autofocus)
		{
			lookAtX = cameraX + cos(cameraRotationY * M_PI / 180.);
			lookAtY = cameraY + cos(cameraRotationZ * M_PI / 180.);
			lookAtZ = cameraZ + sin(cameraRotationY * M_PI / 180.);
		}
	}
	else
	{
		lookAtX = elephantX - cos((elephantRotation + headRotationY) * M_PI / 180);
		lookAtY = -2 - sin(headRotationZ * M_PI / 180);
		lookAtZ = elephantZ + sin((elephantRotation + headRotationY) * M_PI / 180);

		local_cameraX = elephantX + 4.5 * (lookAtX - elephantX) / 12.;
		local_cameraY = -2 + 4.5 * (lookAtY + 2) / 12.;
		local_cameraZ = elephantZ + 4.5 * (lookAtZ - elephantZ) / 12.;
	}

	if (current_state == adjust_light && currently_adjusting_light == diffuse)
	{
		lookAtX = lightX;
		lookAtY = lightY;
		lookAtZ = lightZ;
	}

	gluLookAt(local_cameraX, local_cameraY, local_cameraZ, lookAtX, lookAtY, lookAtZ, 0, 1, 0);
}

// Render scene + menus
void display()
{
	set_projection(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setupCamera();
	
	glPushMatrix();

	lighting();
	
	glPopMatrix();
	glPushMatrix();

	drawRoom();
	
	glPopMatrix();
	glPushMatrix();

	drawChinaWares();
	
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

// Manage "game" mechanisms - movement, value updates, etc.
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
			// Move a little in the light's current orientation
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
	else if (current_state == adjust_camera)
	{
		if (up_arrow_down || down_arrow_down || right_arrow_down || left_arrow_down || space_down)
		{
			autofocus = false;
		}

		if (down_arrow_down)
		{
			cameraRotationZ -= 2;
			if (cameraRotationZ < 225)
			{
				cameraRotationZ = 225;
			}
		}
		else if (up_arrow_down)
		{
			cameraRotationZ += 2;
			if (cameraRotationZ > 305)
			{
				cameraRotationZ = 305;
			}
		}

		if (right_arrow_down)
		{
			cameraRotationY += 2;
		}
		else if (left_arrow_down)
		{
			cameraRotationY -= 2;
		}

		if (space_down)
		{
			// Move a little in the camera's current orientation
			double camera_step_size = 0.5;
			cameraX += camera_step_size * cos(cameraRotationY * M_PI / 180.);
			cameraY += camera_step_size * cos(cameraRotationZ * M_PI / 180.);
			cameraZ += camera_step_size * sin(cameraRotationY * M_PI / 180.);

			if (cameraX < -9.5)
			{
				cameraX = 9.5;
			}
			else if (cameraX > 9.5)
			{
				cameraX = -9.5;
			}

			if (cameraY < -4.5)
			{
				cameraY = 4.5;
			}
			else if (cameraY > 4.5)
			{
				cameraY = -4.5;
			}

			if (cameraZ < -14.5)
			{
				cameraZ = 0.5;
			}
			else if (cameraZ > 0.5)
			{
				cameraZ = -14.5;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(25, timer, 0);
}

// Handle keyboard events where a key is pressed (down)
void keyboard_down(unsigned char key, int x, int y)
{
	if (current_state == playing || (current_state == adjust_light && currently_adjusting_light == diffuse) || current_state == adjust_camera)
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

	if ((int)key == 27) // ESC key
	{
		current_state = playing;
	}

	if (current_state == adjust_camera && key == 'q')
	{
		autofocus = true;
	}
}

// Handle keyboard events where a key is released
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

// Handle "special" keys being pressed (arrows, ESC etc.)
void special_keyboard_down(int key, int x, int y)
{
	if (current_state == playing || current_state == adjust_camera)
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

// Handle "special" keys being released
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

// Handle mouse events
void mouse(GLint button, GLint action, GLint x, GLint y)
{
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	y = SCREEN_HEIGHT - y;

	// Quit
	if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 220 && y < SCREEN_HEIGHT - 180)
	{
		exit(0);
	}
	// Help
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 60 && y < SCREEN_HEIGHT - 20)
	{
		current_state = help;
	}
	// Adjust ambient light
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 100 && y < SCREEN_HEIGHT - 60)
	{
		current_state = adjust_light;
		currently_adjusting_light = ambient;
		targetRed = &ambientRed;
		targetGreen = &ambientGreen;
		targetBlue = &ambientBlue;
	}
	// Adjust light source
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 140 && y < SCREEN_HEIGHT - 100)
	{
		current_state = adjust_light;
		currently_adjusting_light = diffuse;
		targetRed = &diffuseRed;
		targetGreen = &diffuseGreen;
		targetBlue = &diffuseBlue;
	}
	// Adjust camera
	else if (x >= 20 && x <= 300 && y >= SCREEN_HEIGHT - 180 && y < SCREEN_HEIGHT - 140)
	{
		current_state = adjust_camera;
		elephantPOV = false;
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
	glutKeyboardFunc(keyboard_down);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(special_keyboard_down);
	glutSpecialUpFunc(special_keyboard_up);
	glutMouseFunc(mouse);

	glutMainLoop();

	return 0;
}