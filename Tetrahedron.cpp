// Tetrahedron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<gl/glut.h>

float v[4][3] = {{-1.0, -0.5, 0.0}, {1.0, -0.5, 0.0}, {0.0, 0.9, 0.0}, {0.0, 0.0, 1.4}};
int m;

void triangle(float *a, float *b, float *c) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

void tetra(float *a, float *b, float *c, float *d) {
	glColor3f(1, 1, 1);
	triangle(a,b,c);
	glColor3f(1, 0, 0);
	triangle(a,b,d);
	glColor3f(0, 1, 0);
	triangle(a,c,d);
	glColor3f(0, 0, 1);
	triangle(b,c,d);
}

void divide_tetra(float *a, float *b, float *c, float *d, int m) {
	float m0[3], m1[3], m2[3], m3[3], m4[3], m5[3];
	if(m>0) {
		for(int i = 0; i < 3; i++) {
			m0[i] = (a[i] + b[i])/2;
			m1[i] = (b[i] + c[i])/2;
			m2[i] = (a[i] + c[i])/2;
			m3[i] = (a[i] + d[i])/2;
			m4[i] = (b[i] + d[i])/2;
			m5[i] = (c[i] + d[i])/2;
		}
		divide_tetra(a, m0, m2, m3, m-1);
		divide_tetra(m0, b, m1, m4,m-1);
		divide_tetra(m2, m1, c, m5, m-1);
		divide_tetra(m3, m4, m5, d, m-1);
	} else 
		tetra(a, b, c, d);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divide_tetra(v[0], v[1], v[2], v[3], m);
	glFlush();
}

void init() {
	glClearColor(0, 0, 0, 1.0);
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
	glEnable(GL_DEPTH_TEST);
}


void main() {
	printf("Enter the number of sub-divisions to be performed:");
	scanf("%d", &m);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("TETRAHEDRON");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}