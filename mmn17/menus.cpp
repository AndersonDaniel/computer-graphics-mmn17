#include <GL/glut.h>
#include "menus.h"

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

// Display main menu (always present)
void displayMenu(const int SCREEN_HEIGHT)
{
	glColor3f(.95, .95, .95);
	writeText(25, SCREEN_HEIGHT - 50, GLUT_BITMAP_HELVETICA_18, "HELP");
	writeText(25, SCREEN_HEIGHT - 100, GLUT_BITMAP_HELVETICA_18, "ADJUST AMBIENT LIGHT");
	writeText(25, SCREEN_HEIGHT - 150, GLUT_BITMAP_HELVETICA_18, "ADJUST LIGHT SOURCE");
	writeText(25, SCREEN_HEIGHT - 200, GLUT_BITMAP_HELVETICA_18, "ADJUST CAMERA");
	writeText(25, SCREEN_HEIGHT - 250, GLUT_BITMAP_HELVETICA_18, "QUIT");

	glBegin(GL_LINES);

	glVertex2d(35, SCREEN_HEIGHT - 67);
	glVertex2d(245, SCREEN_HEIGHT - 67);
	glVertex2d(35, SCREEN_HEIGHT - 117);
	glVertex2d(245, SCREEN_HEIGHT - 117);
	glVertex2d(35, SCREEN_HEIGHT - 167);
	glVertex2d(245, SCREEN_HEIGHT - 167);
	glVertex2d(35, SCREEN_HEIGHT - 217);
	glVertex2d(245, SCREEN_HEIGHT - 217);

	glEnd();

	glColor4f(.2, .2, .45, 0.35);
	glBegin(GL_POLYGON);

	glVertex2d(20, SCREEN_HEIGHT - 20);
	glVertex2d(300, SCREEN_HEIGHT - 20);
	glVertex2d(300, SCREEN_HEIGHT - 270);
	glVertex2d(20, SCREEN_HEIGHT - 270);

	glEnd();
}

// Show help screen when requested
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

	writeText(110, SCREEN_HEIGHT - 520, GLUT_BITMAP_HELVETICA_18, "Additional menu options contain relevant directions for adjustments");

	writeText(110, SCREEN_HEIGHT - 570, GLUT_BITMAP_HELVETICA_18, "Press ESC to return to game");

	glColor4f(.2, .2, .45, 0.55);
	glBegin(GL_POLYGON);

	glVertex2d(100, SCREEN_HEIGHT - 300);
	glVertex2d(950, SCREEN_HEIGHT - 300);
	glVertex2d(950, 50);
	glVertex2d(100, 50);

	glEnd();
}

// Screen containing controls for adjusting light (both ambient light and the light source)
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

// Screen with explanations on camera adjustment
void displayAdjustCamera(const int SCREEN_HEIGHT)
{
	glColor3f(.95, .95, .95);

	writeText(110, 180, GLUT_BITMAP_HELVETICA_18,
		"Adjusting camera (press ESC to return to game)");

	writeText(110, 150, GLUT_BITMAP_HELVETICA_18,
		"Use arrows to rotate camera, SPACE to move in camera's direction");

	writeText(110, 120, GLUT_BITMAP_HELVETICA_18,
		"Press Q to refocus camera on elephant");

	glColor4f(.2, .2, .45, 0.4);
	glBegin(GL_POLYGON);

	glVertex2d(100, 50);
	glVertex2d(950, 50);
	glVertex2d(950, 200);
	glVertex2d(100, 200);

	glEnd();
}

// Draw all menus and screen
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
	else if (current_state == adjust_camera)
	{
		displayAdjustCamera(SCREEN_HEIGHT);
	}

	glEnable(GL_LIGHTING);
}
