#define FREEGLUT_STATIC
#include <GL\freeglut.h>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>

void init(void);
void Draw_flag(void);
void Draw_star(void);
double cov(int x);

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("A program to draw the flag");

	init();
	Draw_flag();
	Draw_star();
	glutMainLoop();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-70, 290, -170, 90);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Draw_flag(void)
{
	//draw blue square
	glColor3f(0.0, 0.2, 0.6);
	//glRecti(-50, 50, 50, -50);
	glBegin(GL_POLYGON);
	glVertex2d(-50, 50);
	glVertex2d(-50, -50);
	glVertex2d(50, -50);
	glVertex2d(50, 50);
	glEnd();

	//draw white triangle
	glColor3f(1.0, 1.0, 1.0);
	//glRecti(50, 50, 250, -50);
	glBegin(GL_POLYGON);
	glVertex2d(50, 50);
	glVertex2d(50, -50);
	glVertex2d(250, -50);
	glVertex2d(250, 50);
	glEnd();

	//draw red triangle
	glColor3f(1.0, 0.0, 0.0);
	//glRecti(-50, -50, 250, -150);
	glBegin(GL_POLYGON);
	glVertex2d(-50, -50);
	glVertex2d(-50, -150);
	glVertex2d(250, -150);
	glVertex2d(250, -50);
	glEnd();

	glFlush();
}

double cov(int x)
{
	const double pi = 3.1415926;
	double res = x / 180.0*pi;
	return res;
}

void Draw_star(void)
{
	GLdouble vert[10][2];
	vert[0][0] = 0.0;
	vert[0][1] = 20 * tan(cov(18)) / tan(cov(36)) + 20 * cos(cov(18));
	vert[1][0] = vert[0][0] - 20 * tan(cov(18));
	vert[1][1] = vert[0][1] - 20 * cos(cov(18));
	vert[2][0] = vert[1][0] - 20;
	vert[2][1] = vert[1][1];
	vert[3][0] = vert[2][0] + 20 * cos(cov(36));
	vert[3][1] = vert[2][1] - 20 * sin(cov(36));
	vert[4][0] = vert[3][0] - 20 * cos(cov(72));
	vert[4][1] = vert[3][1] - 20 * sin(cov(72));
	vert[5][0] = 0.0;
	vert[5][1] = -20 * tan(cov(18)) / sin(cov(36));
	for (int i = 6; i < 10; i++){
		vert[i][0] = -vert[10 - i][0];
		vert[i][1] = vert[10 - i][1];
	}

	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_POLYGON);
	for (int i = 1; i < 10; i += 2){
		glVertex2dv(vert[i]);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for (int i = 1; i <= 7; i += 2){
		glVertex2dv(vert[i]);
		glVertex2dv(vert[i+1]);
		glVertex2dv(vert[i+2]);
	}
	glVertex2dv(vert[9]);
	glVertex2dv(vert[0]);
	glVertex2dv(vert[1]);
	glEnd();

	glFlush();
}