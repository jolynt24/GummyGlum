// RotatingColorCube.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<gl/glut.h>

float v[8][3]={{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1},{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1}};
float angle[3]={0,0,0};
int axis=2;

void square(float *a, float *b, float *c, float *d) {
	glBegin(GL_QUADS);
	glColor3fv(a);
	glVertex3fv(a);
	glColor3fv(b);
	glVertex3fv(b);
	glColor3fv(c);
	glVertex3fv(c);
	glColor3fv(d);
	glVertex3fv(d);
	glEnd();
}

void colorCube() {
	square(v[0],v[1],v[2],v[3]);
	square(v[4],v[5],v[6],v[7]);
	square(v[0],v[1],v[4],v[5]);
	square(v[3],v[2],v[6],v[7]);
	square(v[1],v[5],v[6],v[2]);
	square(v[0],v[4],v[7],v[3]);
}

void spinCube() {
	angle[axis] += 0.1;
	if (angle[axis] >360)
		angle[axis]=0;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}

void reShape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h) 
		glOrtho(-2,2,-2*h/w,2*h/w,-10,10);
	else glOrtho(-2*h/w,2*h/w,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);
	glEnable(GL_DEPTH_TEST);
}


void init() {
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(angle[0],1,0,0);
	glRotatef(angle[1],0,1,0);
	glRotatef(angle[2],0,0,1);
	colorCube();
	glFlush();
	glutSwapBuffers();
}

void main() {
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("ROTATING COLOR CUBE");
	glutDisplayFunc(display);
	glutReshapeFunc(reShape);
	init();
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glutMainLoop();
}