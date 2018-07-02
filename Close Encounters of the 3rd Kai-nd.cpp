/*
Name: Kai Bernstein
email: kdbernst@syr.edu
Assignment: Homework 2
Environment: Visual Studio 2017
Date: February 19, 2018
References: None

Interaction:
Press 1 to 5 to cycle between moon phases (1 = New ... 5 = Full).
Press t to toggle TIE Fighters.
Press b to toggle Borg cube.
Press p to toggle Polaris.
Press c to toggle the shooting stars.
Press w to toggle the wormhole.
Right click on the GUI window to quit (Escape key also quits).
Right click on the display window to bring up the menu.
Sky Color changes the color of the sky to day (blue), night (black), or sunset (pink).
Moon Color changes the color of the moon to normal (white), harvest (orange), blood (red) or a couple more interesting options.
Moon Size changes the size of the moon to make it larger or smaller, or set it back to normal.
Rotate rotates the sky 45, 90, 180 or 299 degrees. Picking 0 will return the sky to normal.
Quit... quits.
Left click anywhere on the display window to move the moon to that postition.  Click and drag to move the moon around.
Left click in boxes on GUI window to select those options.  Left click in radio buttons to select moon phase.

I put in several easter eggs that can be found by doing certain things: 
1. No crossovers: Activate the TIE fighters (or Death Star) and the Borg Cube at the same time.
2. Dark Side of the Force: Activate Death Star mode and Pink Floyd mode at the same time, and in that order.
3. He's heading for that small moon: Activate small moon mode and Death Star mode at the same time.
4. Oopsie-daisy!: Throw the moon offscreen.
5. Supermoon: Supermoon isn't really an easter egg, more of a joke, but I'm putting it here anyway.  Just activate Supermoon mode.
6. The Blood Moon Rises: Come on, I've gotta leave at least one a mystery!
*/
#include "stdafx.h"
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

static int id1, id2;
static int width1, height1;
static int width2, height2;
static double cx = 0, cy = 0;
static bool o1 = 0, o2 = 0, o3 = 0, o4 = 0, o5 = 0;
static int radio = 2;
static int sky = 2;
static int mc = 0;
static double angle = 0;
static bool floyd = 0;
static bool yavin = 0;
static bool oops = 0;
static bool l = 1;
static int radius = 8;
static double equation1[4] = { 0, 0, -1, 0 };
static double equation0[4] = { 0, 0, 1, 0 };
static double t = 0;

void writeStrokeString(void *font, const char *string)
{
	const char *c;
	for (c = string; *c != '\0'; c++)
		glutStrokeCharacter(font, *c);
}


void drawBoxes()
{
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(1, 27, 0);
	glScalef(0.015, 0.015, 0.015);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Options");
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (floyd)
		glColor3f(0.5, 0.5, 0.5);
	else
		glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 25, 0);
	glVertex3f(1, 23, 0);
	glVertex3f(3, 23, 0);
	glVertex3f(3, 25, 0);
	glEnd();
	if (o1) {
		glBegin(GL_LINES);
		glVertex3f(1, 25, 0);
		glVertex3f(3, 23, 0);
		glVertex3f(3, 25, 0);
		glVertex3f(1, 23, 0);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(3.5, 23.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "TIE Fighters");
	glPopMatrix();
	if (floyd)
		glColor3f(0.5, 0.5, 0.5);
	else
		glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 20, 0);
	glVertex3f(1, 18, 0);
	glVertex3f(3, 18, 0);
	glVertex3f(3, 20, 0);
	glEnd();
	if (o2) {
		glBegin(GL_LINES);
		glVertex3f(1, 20, 0);
		glVertex3f(3, 18, 0);
		glVertex3f(3, 20, 0);
		glVertex3f(1, 18, 0);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(3.5, 18.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Assimilate!");
	glPopMatrix();
	if (sky == 1 || sky == 3)
		glColor3f(0.5, 0.5, 0.5);
	else
		glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 15, 0);
	glVertex3f(1, 13, 0);
	glVertex3f(3, 13, 0);
	glVertex3f(3, 15, 0);
	glEnd();
	if (o3) {
		glBegin(GL_LINES);
		glVertex3f(1, 15, 0);
		glVertex3f(3, 13, 0);
		glVertex3f(3, 15, 0);
		glVertex3f(1, 13, 0);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(3.5, 13.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Polaris");
	glPopMatrix();
	if (sky == 1 || sky == 3)
		glColor3f(0.5, 0.5, 0.5);
	else
		glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 10, 0);
	glVertex3f(1, 8, 0);
	glVertex3f(3, 8, 0);
	glVertex3f(3, 10, 0);
	glEnd();
	if (o4) {
		glBegin(GL_LINES);
		glVertex3f(1, 10, 0);
		glVertex3f(3, 8, 0);
		glVertex3f(3, 10, 0);
		glVertex3f(1, 8, 0);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(3.5, 8.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Shooting Stars");
	glPopMatrix();
	if (sky == 1 || sky == 3)
		glColor3f(0.5, 0.5, 0.5);
	else
		glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 5, 0);
	glVertex3f(1, 3, 0);
	glVertex3f(3, 3, 0);
	glVertex3f(3, 5, 0);
	glEnd();
	if (o5) {
		glBegin(GL_LINES);
		glVertex3f(1, 5, 0);
		glVertex3f(3, 3, 0);
		glVertex3f(3, 5, 0);
		glVertex3f(1, 3, 0);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(3.5, 3.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Wormhole");
	glPopMatrix();
}

void drawButtons()
{
	if ((yavin && !floyd) || radius == 16)
		glColor3f(0.5, 0.5, 0.5);
	else
		glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(16, 27, 0);
	glScalef(0.015, 0.015, 0.015);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Phases");
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 40; ++i)
		glVertex2f(cos(2 * PI * i / 40) + 17, sin(2 * PI * i / 40) + 24);
	glEnd();
	if (radio == 1) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(17, 24);
		for (int i = 0; i <= 40; ++i)
			glVertex2f(.8*cos(2 * PI * i / 40) + 17, .8*sin(2 * PI * i / 40) + 24);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(19, 23.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "New");
	glPopMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 40; ++i)
		glVertex2f(cos(2 * PI * i / 40) + 17, sin(2 * PI * i / 40) + 19);
	glEnd();
	if (radio == 2) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(17, 19);
		for (int i = 0; i <= 40; ++i)
			glVertex2f(.8*cos(2 * PI * i / 40) + 17, .8*sin(2 * PI * i / 40) + 19);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(19, 18.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Crescent");
	glPopMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 40; ++i)
		glVertex2f(cos(2 * PI * i / 40) + 17, sin(2 * PI * i / 40) + 14);
	glEnd();
	if (radio == 3) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(17, 14);
		for (int i = 0; i <= 40; ++i)
			glVertex2f(.8*cos(2 * PI * i / 40) + 17, .8*sin(2 * PI * i / 40) + 14);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(19, 13.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Half");
	glPopMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 40; ++i)
		glVertex2f(cos(2 * PI * i / 40) + 17, sin(2 * PI * i / 40) + 9);
	glEnd();
	if (radio == 4) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(17, 9);
		for (int i = 0; i <= 40; ++i)
			glVertex2f(.8*cos(2 * PI * i / 40) + 17, .8*sin(2 * PI * i / 40) + 9);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(19, 8.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Gibbous");
	glPopMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 40; ++i)
		glVertex2f(cos(2 * PI * i / 40) + 17, sin(2 * PI * i / 40) + 4);
	glEnd();
	if (radio == 5) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(17, 4);
		for (int i = 0; i <= 40; ++i)
			glVertex2f(.8*cos(2 * PI * i / 40) + 17, .8*sin(2 * PI * i / 40) + 4);
		glEnd();
	}
	glPushMatrix();
	glTranslatef(19, 3.5, 0);
	glScalef(0.0075, 0.0075, 0.0075);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Full");
	glPopMatrix();
}

void drawMoon()
{
	if (floyd)
		glColor3f(0.0, 0.0, 0.0);
	else if (yavin)
		glColor3f(0.7, 0.7, 0.7);
	else if (radius == 16)
		glColor3f(0.0, 0.0, 0.3);
	else if (mc == 1)
		glColor3f(0.8, 0.5, 0.0);
	else if (mc == 2)
		glColor3f(0.3, 0.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1.0);
	glTranslatef(cx, cy, 0);
	if (radio == 1)
		glRotatef(180, 0, 1, 0);
	else if (radio == 2)
		glRotatef(135, 0, 1, 0);
	else if (radio == 3)
		glRotatef(90, 0, 1, 0);
	else if (radio == 4)
		glRotatef(45, 0, 1, 0);
	glClipPlane(GL_CLIP_PLANE0, equation0);
	glEnable(GL_CLIP_PLANE0);
	glutSolidSphere(radius, 30, 30);
	glDisable(GL_CLIP_PLANE0);
}

void drawDarkMoon()
{
	if (floyd)
		glColor3f(1.0, 1.0, 1.0);
	else if (sky == 1)
		glColor3f(0.0, 0.0, 1.0);
	else if (sky == 3)
		glColor3f(1.0, 0.5, 0.5);
	else
		glColor3f(0.0, 0.0, 0.0);
	glClipPlane(GL_CLIP_PLANE1, equation1);
	glEnable(GL_CLIP_PLANE1);
	glutSolidSphere(radius, 30, 30);
	glDisable(GL_CLIP_PLANE1);
}

void drawTIE(double x, double y, double z)
{
	if (mc == 2 && o1 && radius == 11 && sky != 1 && sky != 3 && radio == 5 && o3)
		glColor3f(0.3, 0.0, 0.0);
	else
		glColor3f(0.3, 0.3, 0.3);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(x, y, z);
	glutWireSphere(.35, 30, 30);
	glPopMatrix();
	glBegin(GL_LINES);
	glVertex3f(x + .7, y + .8, z);
	glVertex3f(x + .7, y - .8, z);
	glVertex3f(x - .6, y + .8, z);
	glVertex3f(x - .6, y - .8, z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(x + .35, y, z);
	glVertex3f(x + .7, y, z);
	glVertex3f(x - .35, y, z);
	glVertex3f(x - .6, y, z);
	glEnd();
}

void drawBorg()
{
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-20, 13, 16);
	glutSolidCube(4);
	glPopMatrix();
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(-21, 14, 20);
	glVertex3f(-21, 14.1, 20);
	glVertex3f(-21.1, 14.1, 20);
	glVertex3f(-21.1, 14, 20);
	glVertex3f(-19, 13, 20);
	glVertex3f(-19, 13.1, 20);
	glVertex3f(-19.1, 13.1, 20); 
	glVertex3f(-19.1, 13, 20);
	glVertex3f(-20, 12, 20);
	glVertex3f(-20, 12.1, 20);
	glVertex3f(-20.1, 12.1, 20);
	glVertex3f(-20.1, 12, 20);
	glEnd();
}

void drawPolaris() 
{
	if (floyd)
		glColor3f(0.0, 0.0, 0.0);
	else if (mc == 2 && o1 && radius == 11 && sky != 1 && sky != 3 && radio == 5 && o3)
		glColor3f(0.3, 0.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(0, 29.5, -19);
	glVertex3f(0, 27.5, -19);
	glVertex3f(-1, 28.5, -19);
	glVertex3f(1, 28.5, -19);
	glVertex3f(-1*(sqrt(2)/2), 28.5 + sqrt(2)/2, -19);
	glVertex3f((sqrt(2) / 2), 28.5 - sqrt(2) / 2, -19);
	glVertex3f((sqrt(2) / 2), 28.5 + sqrt(2) / 2, -19);
	glVertex3f(-1 * (sqrt(2) / 2), 28.5 - sqrt(2) / 2, -19);
	glEnd();
}

void drawStars()
{
	if (floyd)
		glColor3f(0.0, 0.0, 0.0);
	else if (mc == 2 && o1 && radius == 11 && sky != 1 && sky != 3 && radio == 5 && o3)
		glColor3f(1.0, 0.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(22, 26.5, 0);
	glBegin(GL_POINTS);
	glVertex3f(-12.6, -13, -19);
	glVertex3f(-6, -15.5, -19);
	glVertex3f(-15, -5, -19);
	glVertex3f(-11, -8, -19);
	glVertex3f(-4, -11, -19);
	glVertex3f(-19, -1, -19);
	glEnd();
	glPopMatrix();
}

void drawDisc() 
{
	glColor3f(0.3, 0.3, 0.3);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glTranslatef(cx, cy, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int i = 1; i <= 40; i++)
		glVertex3f((radius + .1) * cos(2 * PI * i / 40), 0, (radius + .1) * sin(2 * PI * i / 40));
	glEnd();
	if (radius == 5)
		glScalef(0.625, 0.625, 1);
	if (radius == 11)
		glScalef(1.375, 1.375, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 4, radius);
	for (int i = 1; i <= 41; i++)
		glVertex3f(3 * cos(2 * PI * i / 40), 3 * sin(2 * PI * i / 40) + 4, radius);
	glEnd();
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawComet()
{
	if (floyd)
		glColor3f(0.0, 0.0, 0.0);
	else if (mc == 2 && o1 && radius == 11 && sky != 1 && sky != 3 && radio == 5 && o3)
		glColor3f(0.3, 0.0, 0.0);
	else
		glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glTranslatef(t, 0, 0);
	glTranslatef(31, -20, 18);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int i = 1; i <= 41; i++)
		glVertex3f(.3 * cos(2 * PI * i / 40), .3 * sin(2 * PI * i / 40), 0);
	glEnd();
	glPopMatrix();
}

void drawWormhole()
{
	if (floyd)
		glColor3f(0.0, 0.0, 0.0);
	else if (mc == 2 && o1 && radius == 11 && sky != 1 && sky != 3 && radio == 5 && o3)
		glColor3f(0.3, 0.0, 0.0);
	else
		glColor3f(0.0, 0.0, 0.3);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(21, -3, -18);
	glutWireCone(3, 3, 30, 30);
	glPopMatrix();
}

void writeError()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(-27, 0, 0);
	glScalef(0.014, 0.014, 0.014);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "You can't mix Star Wars and Star Trek!");
	glPopMatrix();
}

void writeFloyd()
{
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1);
	glPushMatrix();
	if (!yavin) {
		glTranslatef(-21, -15, 19);
		glScalef(0.02, 0.02, 0.02);
		writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Dark side of the moon");
	}
	else {
		glTranslatef(-27, -15, 19);
		glScalef(0.013, 0.013, 0.013);
		writeStrokeString(GLUT_STROKE_MONO_ROMAN, "You don't know the power of the dark side");
	}
	glPopMatrix();
}

void writeQuote()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(-23, -15, 19);
	glScalef(0.02, 0.02, 0.02);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "...it's a space station");
	glPopMatrix();
}

void writeMessage()
{
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(-10, 0, 0);
	glScalef(0.03, 0.03, 0.03);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Whoops...");
	glPopMatrix();
	oops = 0;
}

void writeBlood()
{
	glColor3f(0.3, 0.0, 0.0);
	glLineWidth(1);
	glPushMatrix();
	glTranslatef(-28, -18, 0);
	glScalef(0.017, 0.017, 0.017);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "Blood will be spilled tonight...");
	glPopMatrix();
}

void drawSymbol()
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(5);
	glPushMatrix();
	glTranslatef(-10 + cx, -10 + cy, 16);
	glScalef(0.2, 0.2, 0.2);
	writeStrokeString(GLUT_STROKE_MONO_ROMAN, "S");
	glPopMatrix();
}

void increaseTranslation()
{
	if (t > -530 && l)
		t -= .1;
	else if (t <= -530) {
		t += .1; l = 0;
	}
	else if (t >= 500 && !l) {
		t -= .1; l = 1;
	}
	else if (t > -530 && !l)
		t += .1;
}

void animate(int value)
{
	if (o4 && sky != 1 && sky != 3) {
		increaseTranslation();
		glutPostRedisplay();
		glutTimerFunc(10000, animate, 1);
	}
}

void drawScene1(void)
{
	glutSetWindow(id1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 30.0, 0.0, 30.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawBoxes();
	drawButtons();
	glutSwapBuffers();
}

void drawScene2(void)
{
	glutSetWindow(id2);
	if (floyd)
		glClearColor(1.0, 1.0, 1.0, 0.0);
	else if (sky == 1)
		glClearColor(0.0, 0.0, 1.0, 0.0);
	else if (sky == 3)
		glClearColor(1.0, 0.5, 0.5, 0.0);
	else
		glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(angle, 0, 0, 1);
	if ((o1 && o2) || (o2 && yavin))
		writeError();
	else {
		glEnable(GL_DEPTH_TEST);
		glPushMatrix();
		drawMoon();
		drawDarkMoon();
		glPopMatrix();
		if (floyd)
			writeFloyd();
		if (yavin && !floyd)
			drawDisc();
		if (radius == 16)
			drawSymbol();
		if (o1) {
			drawTIE(20, -10, 15);
			drawTIE(-25, 5, 17);
			drawTIE(0, -26, 10);
			drawTIE(-18, -5, -11);
		}
		if (o2)
			drawBorg();
		if (o3 && sky != 1 && sky != 3)
			drawPolaris();
		if (o4 && sky != 1 && sky != 3) {
			drawComet();
			animate(1);
		}
		if (o5 && sky != 1 && sky != 3)
			drawWormhole();
		if (sky != 1 && sky != 3)
			drawStars();
		if (yavin && radius == 5)
			writeQuote();
		if (oops)
			writeMessage();
		if (mc == 2 && o1 && radius == 11 && sky != 1 && sky != 3 && radio == 5 && o3)
			writeBlood();
		glDisable(GL_DEPTH_TEST);
	}
	glPopMatrix();
	glutSwapBuffers();
}

void mouseControl(int button, int state, int x, int y)
{
	if (glutGetWindow() == id1) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (x >= 20 && x <= 60) {
				if ((height1 - y) >= 460 && (height1 - y) <= 500 && !floyd)
					o1 = !o1;
				else if ((height1 - y) >= 360 && (height1 - y) <= 400 && !floyd)
					o2 = !o2;
				else if ((height1 - y) >= 260 && (height1 - y) <= 300 && sky != 1 && sky != 3)
					o3 = !o3;
				else if ((height1 - y) >= 160 && (height1 - y) <= 200 && sky != 1 && sky != 3)
					o4 = !o4;
				else if ((height1 - y) >= 60 && (height1 - y) <= 100 && sky != 1 && sky != 3)
					o5 = !o5;
			}
			if (x >= 320 && x <= 360 && (!yavin || floyd) && radius != 16) {
				if ((height1 - y) >= 460 && (height1 - y) <= 500)
					radio = 1;
				else if ((height1 - y) >= 360 && (height1 - y) <= 400)
					radio = 2;
				else if ((height1 - y) >= 260 && (height1 - y) <= 300)
					radio = 3;
				else if ((height1 - y) >= 160 && (height1 - y) <= 200)
					radio = 4;
				else if ((height1 - y) >= 60 && (height1 - y) <= 100)
					radio = 5;
			}
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			glutPostRedisplay();
			glutSetWindow(id2);
			glutPostRedisplay();
		}
		if (button == GLUT_RIGHT_BUTTON)
			exit(0);
	}
	if (glutGetWindow() == id2) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			cx = x/10 - 30; cy = (height2 - y)/10 - 30;
			glutPostRedisplay();
			glutSetWindow(id1);
			glutPostRedisplay();
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			if (x >= (600 + radius * 10) || x <= (0 - radius*10) || y <= (0 - radius * 10) || y >= (600 + radius * 10)) {
				oops = 1;
				glutPostRedisplay();
				glutSetWindow(id1);
				glutPostRedisplay();
			}

		}
	}
}

void mouseMotion(int x, int y)
{
	if (glutGetWindow() == id2) {
		cx = x / 10 - 30; cy = (height2 - y) / 10 - 30;
		glutPostRedisplay();
		glutSetWindow(id1);
		glutPostRedisplay();
	}
}

void skyMenu(int id)
{
	if (id == 1)
		sky = 1;
	if (id == 2) {
		sky = 2;
		floyd = 0;
	}
	if (id == 3)
		sky = 3;
	glutPostRedisplay();
	glutSetWindow(id1);
	glutPostRedisplay();
}

void colorMenu(int id)
{
	if (id == 12) {
		mc = 0; floyd = 0; yavin = 0;
		if (radius == 16) { radius = 8; }
	}
	if (id == 4) {
		mc = 1; floyd = 0; yavin = 0;
		if (radius == 16) { radius = 8; }
	}
	if (id == 5) {
		mc = 2; floyd = 0; yavin = 0;
		if (radius == 16) { radius = 8; }
	}
	if (id == 6) {
		sky = 0; mc = 0; floyd = 1; o1 = 0; o2 = 0;
		if (radius == 16) { radius = 8; }
	}
	if (id == 7) {
		mc = 1977; floyd = 0; yavin = 1; radio = 5;
		if (radius == 16) { radius = 8; }
	}
	glutPostRedisplay();
	glutSetWindow(id1);
	glutPostRedisplay();
}

void sizeMenu(int id)
{
	if (id == 8)
		radius = 5;
	if (id == 9)
		radius = 8;
	if (id == 10)
		radius = 11;
	if (id == 11) {
		radius = 16; mc = 0;  floyd = 0; yavin = 0; radio = 5;
	}
	glutPostRedisplay();
	glutSetWindow(id1);
	glutPostRedisplay();
}

void mainMenu(int id)
{
	if (id == 0)
		exit(0);
	if (id == 13) {
		angle = 1;
	}
	glutPostRedisplay();
	glutSetWindow(id1);
	glutPostRedisplay();
}

void rotationMenu(int id)
{
	switch (id)
	{
	case 13:
		angle = 45;
		break;
	case 14:
		angle = 90;
		break;
	case 15:
		angle = 180;
		break;
	case 16:
		angle = 299;
		break;
	case 17:
		angle = 0;
		break;
	default:
		break;
	}
	glutPostRedisplay();
	glutSetWindow(id1);
	glutPostRedisplay();
}

void makeMenu(void)
{
	int sub1, sub2, sub3, sub4;
	sub1 = glutCreateMenu(skyMenu);
	glutAddMenuEntry("Day", 1);
	glutAddMenuEntry("Night", 2);
	glutAddMenuEntry("Sunset", 3);
	sub2 = glutCreateMenu(colorMenu);
	glutAddMenuEntry("Normal Moon", 12);
	glutAddMenuEntry("Harvest Moon", 4);
	glutAddMenuEntry("Blood Moon", 5);
	glutAddMenuEntry("Pink Floyd", 6);
	glutAddMenuEntry("That's no moon...", 7);
	sub3 = glutCreateMenu(sizeMenu);
	glutAddMenuEntry("Small Moon", 8);
	glutAddMenuEntry("Normal Moon", 9);
	glutAddMenuEntry("Big Moon", 10);
	glutAddMenuEntry("Supermoon", 11);
	sub4 = glutCreateMenu(rotationMenu);
	glutAddMenuEntry("Rotate 45", 13);
	glutAddMenuEntry("Rotate 90", 14);
	glutAddMenuEntry("Rotate 180", 15);
	glutAddMenuEntry("Rotate 299", 16);
	glutAddMenuEntry("Rotate 0", 17);
	glutCreateMenu(mainMenu);
	glutAddSubMenu("Sky Color", sub1);
	glutAddSubMenu("Moon Color", sub2);
	glutAddSubMenu("Moon Size", sub3);
	glutAddSubMenu("Rotate Sky", sub4);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void setup1(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void setup2(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	makeMenu();
}

void resize1(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 30.0, 0.0, 30.0, -5.0, 5.0);
	width1 = w;
	height1 = h;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void resize2(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0, -20.0, 20.0);
	width2 = w;
	height2 = h;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case '1':
		radio = 1;
		glutPostRedisplay();
		break;
	case '2':
		radio = 2;
		glutPostRedisplay();
		break;
	case '3':
		radio = 3;
		glutPostRedisplay();
		break;
	case '4':
		radio = 4;
		glutPostRedisplay();
		break;
	case '5':
		radio = 5;
		glutPostRedisplay();
		break;
	case 't':
		o1 = !o1;
		glutPostRedisplay();
		break;
	case 'b':
		o2 = !o2;
		glutPostRedisplay();
		break;
	case 'p':
		o3 = !o3;
		glutPostRedisplay();
		break;
	case 'c':
		o4 = !o4;
		glutPostRedisplay();
		break;
	case 'w':
		o5 = !o5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void printInteraction(void) 
{
	cout << "Interaction:" << endl;
	cout << "Press 1 to 5 to cycle between moon phases (1 = New ... 5 = Full)." << endl
		<< "Press t to toggle TIE Fighters." << endl
		<< "Press b to toggle Borg cube." << endl
		<< "Press p to toggle Polaris." << endl
		<< "Press c to toggle the shooting stars." << endl
		<< "Press w to toggle the wormhole." << endl
		<< "Right click on the GUI window to quit (Escape key also quits)." << endl
		<< "Right click on the display window to bring up the menu." << endl
		<< "Sky Color changes the color of the sky to day (blue), night (black), or sunset (pink)." << endl
		<< "Moon Color changes the color of the moon to normal (white), harvest (orange), blood (red) or a couple more interesting options." << endl
		<< "Moon Size changes the size of the moon to make it larger or smaller, or set it back to normal." << endl
		<< "Rotate rotates the sky 45, 90, 180 or 299 degrees. Picking 0 will return the sky to normal." << endl
		<< "Quit... quits." << endl
		<< "Left click anywhere on the display window to move the moon to that postition.  Click and drag to move the moon around." << endl
		<< "Left click in boxes on GUI window to select those options.  Left click in radio buttons to select moon phase." << endl
		<< endl
		<< "I put in several easter eggs that can be found by doing certain things:" << endl
		<< "1. No crossovers: Activate the TIE fighters(or Death Star) and the Borg Cube at the same time." << endl
		<< "2. Dark Side of the Force: Activate Death Star mode and  Pink Floyd mode at the same time, and in that order." << endl
		<< "3. He's heading for that small moon: Activate small moon mode and Death Star mode at the same time." << endl
		<< "4. Oopsie-daisy!: Throw the moon offscreen." << endl
		<< "5. Supermoon: Supermoon isn't really an easter egg, more of a joke, but I'm putting it here anyway.  Just activate Supermoon mode." << endl
		<< "6. The Blood Moon Rises: Come on, I've gotta leave at least one a mystery!" << endl;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	id1 = glutCreateWindow("window 1");
	glutDisplayFunc(drawScene1);
	glutReshapeFunc(resize1);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
	setup1();
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(700, 100);
	id2 = glutCreateWindow("window 2");
	glutDisplayFunc(drawScene2);
	glutReshapeFunc(resize2);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
	setup2();
	glutMainLoop();
	return 0;
}