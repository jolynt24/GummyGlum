// Flag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<gl/glut.h>
#include<math.h>
#include<string.h>
#define PI 3.1416

typedef struct {
	GLfloat x, y;
} point;

float theta = 0;
static int value = 0, submenu_id, menu_id;

void bino(int n, int *C) {
	int k, j;
	for(k=0; k<=n; k++) {
		C[k] = 1;
		for(j=n; j>=k+1; j--) C[k] *= j;
		for(j=n-k; j>=2; j--) C[k] /= j;
	}
}

void computeBezPt(float u, point *pt1, int CPt, point *pt2, int *C) {
	int k,n = CPt-1;
	float bFcn;
	pt1 -> x = pt1 -> y = 0.0;
	for(k=0; k<CPt; k++) {
		bFcn = C[k] * pow(u,k) * pow(1-u, n-k);
		pt1-> x += pt2[k].x*bFcn;
		pt1-> y += pt2[k].y*bFcn;
	}
}

void bezier(point *pt1, int cPt, int bPt) {
	point bcPt;
	float u;
	int *C, k;
	C = new int[cPt];
	bino(cPt-1,C);
	glBegin(GL_LINE_STRIP);
	for(k=0; k<=bPt; k++) {
		u = float(k)/float(bPt);
		computeBezPt(u,&bcPt,cPt,pt1,C);
		glVertex2f(bcPt.x, bcPt.y);
	}
	glEnd();
	delete[] C;
}

void flag_menu(int num) {
	if(num==4) exit(0);
	else value = num;
	glutPostRedisplay();
}

void displayText(char *string) {
	int len = strlen(string);
	glColor3f(1,0,0);
	glRasterPos2f(10,450);
	for( int i=0; i<len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
}

void display() {
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	int nCtrlPts=4, nBCPts=40;
	point ctrlPts[4]={{100,400},{150,450},{250,350},{300,400}};
	ctrlPts[1].x += 50*sin(theta*PI/180.0);
	ctrlPts[1].y += 25*sin(theta*PI/180.0);
	ctrlPts[2].x -= 50*sin((theta+30)*PI/180.0);
	ctrlPts[2].y -= 50*sin((theta+30)*PI/180.0);
	ctrlPts[3].x -= 25*sin((theta)*PI/180.0);
	ctrlPts[3].y += sin((theta-30)*PI/180.0);
	theta += 1;
	glClear(GL_COLOR_BUFFER_BIT);

	//=============================
	if(value==1) displayText("India");
	if(value==2) displayText("Netherlands");
	if(value==3) displayText("Russia");
	//============================
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	if(!value == 0) {
		if(value==1) glColor3f(1.0,0.4,0.2);
		if(value==2) glColor3f(0.88,0.26,0.20);
		if(value==3) glColor3f(0.92,0.92,0.92);
		for(i=0; i<50; i++) {
			glTranslatef(0,-0.8,0);
			bezier(ctrlPts, nCtrlPts, nBCPts);
		}
		if(value==1) glColor3f(1.0,1.0,1.0);
		if(value==2) glColor3f(0.80,0.80,0.80);
		if(value==3) glColor3f(0.0,0.0,0.9);
		for(i=0; i<50; i++) {
			glTranslatef(0,-0.8,0);
			bezier(ctrlPts, nCtrlPts, nBCPts);
		}
		if(value==1) glColor3f(0.0,0.9,0.0);
		if(value==2) glColor3f(0.0,0.28,0.67);
		if(value==3) glColor3f(0.9,0.0,0.0);
		for(i=0; i<50; i++) {
			glTranslatef(0,-0.8,0);
			bezier(ctrlPts, nCtrlPts, nBCPts);
		}
	}
	glPopMatrix();
	glColor3f(0.7,0.5,0.3);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(100,400);
	glVertex2f(100,40);
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();
}
void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}

void main() {
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Flag");
	init();
	glutDisplayFunc(display);
	submenu_id = glutCreateMenu(flag_menu);
	glutAddMenuEntry("India",1);
	glutAddMenuEntry("Netherlands",2);
	glutAddMenuEntry("Russia",3);
	menu_id = glutCreateMenu(flag_menu);
	glutAddSubMenu("Draw FLag", submenu_id);
	glutAddMenuEntry("Quit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
