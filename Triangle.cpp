// Triangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

float theta=0,xc,yc;
float tri[3][3]={{10,50,30},{10,10,37},{1,1,1}};
float res[3][3]={0};

void triangle(float a[3][3]) {
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(a[0][0],a[1][0]);
	glVertex2f(a[0][1],a[1][1]);
	glVertex2f(a[0][2],a[1][2]);
	glEnd();
}

void multiply(float b[3][3]){
	int i,j,k;
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			res[i][j]=0;
			for(k=0; k<3; k++)
				res[i][j] += b[i][k] * tri[k][j];
		}
	}
	triangle(res);
}

void display() {
	float rot0[3][3]={{cos(theta),-sin(theta),0},{sin(theta),cos(theta),0},{0,0,1}};
	float rotF[3][3]={{cos(theta),-sin(theta),xc-xc*cos(theta)+yc*sin(theta)},{sin(theta),cos(theta),yc-yc*cos(theta)-xc*cos(theta)},{0,0,1}};
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2f(0,-60);
	glVertex2f(0,60);
	glVertex2f(-60,0);
	glVertex2f(60,0);
	glEnd();
	glColor3f(1,0,0);
	triangle(tri);
	glColor3f(0,0,1);
	multiply(rot0);
	glColor3f(0,1,0);
	multiply(rotF);
	glFlush();
}

void init() {
	glClearColor(0.0,0.0,0.0,1.0);
	gluOrtho2D(-60,60,-60,60);
}

void main() {
	printf("Enter the angle (theta) to be rotated\n");
	scanf("%f",&theta);
	theta=(3.14*theta)/180;
	printf("Enter the Fixed point (xc,yc)\n");
	scanf("%f%f",&xc,&yc);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(800,800);
	glutCreateWindow("Triangle Rotation about an origin and a fixed point");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
