// WallTeapot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<gl/glut.h>

void tea() {
	glPushMatrix();
	glTranslatef(1.3,0.2,1.1);
	glRotatef(45,0,1,0);
	glutSolidTeapot(0.4);
	glPopMatrix();
}

void table() {
	glPushMatrix();
	glTranslatef(1,-0.2,1);
	glScalef(1,0.05,1);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15,-0.7,1.85);
	glScalef(0.1,1.0/2,0.1);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.85,-0.7,1.85);
	glScalef(0.1,1.0/2,0.1);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.85,-0.7,0.15);
	glScalef(0.1,1.0/2,0.1);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15,-0.7,0.15);
	glScalef(0.1,1.0/2,0.1);
	glutSolidCube(2.0);
	glPopMatrix();
}

void wall() {
	glPushMatrix();
	glTranslatef(1,-1,1);
	glScalef(1.9,0.05,3.40);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1,1,0.90);
	glScalef(0.1,2,3.3);
	glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,1,-2.45);
	glScalef(1.9,2,0.08);
	glutSolidCube(2.0);
	glPopMatrix();
}

void display() {
	float amb[3]={1.000, 0.973, 0.863}, amb1[3]={0.255, 0.412, 0.882}, amb2[3]={0.8,0.5,0.5};
	float spec[3]={0.2,0.7,0.6};
	float pos[3]={3,2,1};
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	gluLookAt(2.5,0.5,2,0,0,0,0,1,0);
	wall();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb2);
	table();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amb1);
	tea();
	glFlush();
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4,4,-4,4,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}


void main() {
	glutInitDisplayMode(GLUT_DEPTH|GLUT_SINGLE);
	glutInitWindowSize(600,6000);
	glutCreateWindow("Teapot");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}