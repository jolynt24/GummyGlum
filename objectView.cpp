// objectView.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<gl/glut.h>

float v[8][3]={{-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0},{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0}};
int eye[3]={0,0,5};

void keyboard(unsigned char key, int x, int y) {
	if(key == 'x') eye[0]+=1.0;
	if(key == 'X') eye[0]-=1.0;
	if(key=='y') eye[1]+=1.0;
	if(key=='Y') eye[1]-=1.0;
	if(key=='z') eye[2]+=1.0;
	if(key=='Z') eye[2]-=1.0;
	glutPostRedisplay();
}


void init() {
	glClearColor(0,0,0,1);
	//glEnable(GL_DEPTH_TEST);
}

void reShape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	if(w<=h) gluPerspective(90,w/h,2.0,20.0);
	else gluPerspective(90,h/w,2.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);
	//glEnable(GL_DEPTH_TEST);
}

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
	square(v[0],v[1],v[5],v[4]);
	square(v[3],v[2],v[6],v[7]);
	square(v[1],v[5],v[6],v[2]);
	square(v[0],v[4],v[7],v[3]);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	gluLookAt(eye[0],eye[1],eye[2],0,0,0,0,1,0);
	colorCube();
	glFlush();
	glutSwapBuffers();
}

void main() {
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Object View");
	glutDisplayFunc(display);
	glutReshapeFunc(reShape);
	init();
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}