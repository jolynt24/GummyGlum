// CohenSutherland.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<gl/glut.h>

float xmin=50,ymin=50,xmax=180,ymax=180;
float xvmin=200,yvmin=200,xvmax=400,yvmax=400;
int RIGHT=8, LEFT=2,TOP=4,BOTTOM=1;
float sx,sy,vx1,vy1,vx2,vy2;
float x1,y1,x2,y2;
float sp[3],ep[3];
int compute(float x, float y) {
	int code=0;
	if(y > ymax) code=TOP;
	else if(y < ymin) code=BOTTOM;
	if(x > xmax) code=RIGHT;
	else if(x < xmin) code=LEFT;
	return code;
}

void cohen(float x1, float y1, float x2, float y2) {
	float x,y;
	int accept=0,done=0,code_1,code_2,code;
	code_1=compute(x1,y1);
	code_2=compute(x2,y2);
	do {
		if(!(code_1 | code_2)) {
			accept=1;
			done=1;
		}
		else if(code_1 & code_2) done=1;
		else {
			code=code_1?code_1:code_2;
			if(code & TOP) {
				x=x1+(x2-x1)*(ymax-y1)/(y2-y1);
				y=ymax;
			}
			else if(code & BOTTOM) {
				x=x1+(x2-x1)*(ymin-y1)/(y2-y1);
				y=ymin;
			}
			else if(code & RIGHT) {
				y=y1+(y2-y1)*(xmax-x1)/(x2-x1);
				x=xmax;
			} else {
				y=y1+(y2-y1)*(xmin-x1)/(x2-x1);
				x=xmin;
			}
			if(code == code_1) {
				x1=x;
				y1=y;
				code_1=compute(x1,y1);
			} else {
				x2=x;
				y2=y;
				code_2=compute(x2,y2);
			}
		}
	} while(!done);
	if(accept) {
		sx=(xvmax-xvmin)/(xmax-xmin);
		sy=(yvmax-yvmin)/(ymax-ymin);
		vx1=xvmin+(x1-xmin)*sx;
		vy1=xvmin+(y1-ymin)*sy;
		vx2=xvmin+(x2-xmin)*sx;
		vy2=xvmin+(y2-ymin)*sy;
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i=0;i<3;i++){
		glColor3f(0,1,0);
		glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glEnd();
	glColor3f(0,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
	cohen(x1,y1,x2,y2);
	glColor3f(1,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin,yvmin);
	glVertex2f(xvmax,yvmin);
	glVertex2f(xvmax,yvmax);
	glVertex2f(xvmin,yvmax);
	glEnd();
	glColor3f(1,1,0);
	glBegin(GL_LINES);
	glVertex2d(vx1,vy1);
	glVertex2d(vx2,vy2);`
	glEnd();
	glFlush();
}

void init() {
	glClearColor(0,0,0,1);
	gluOrtho2D(0,500,0,500);
}

void main() {
	for(int i=0;i<3;i++){
		printf("Enter end points x1, y1:\n");
		scanf_s("%f%f",&sp[i],&ep[i]);
	}
	/*printf("Enter end points x2, y2:\n");
	scanf_s("%f%f",&x2,&y2);*/
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Cohen Sutherland");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}
