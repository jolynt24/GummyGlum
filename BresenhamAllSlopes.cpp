// BresenhamAllSlopes.cpp : Defines the entry point for the console application.
//
// BresenhamLineDrawing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

int xs,ys,xe,ye;

void init() {
	glClearColor(1,1,1,1);
	gluOrtho2D(0,500,0,500);
}

void draw_pixel(int x, int y) {
	glColor3f(1,0,0);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void bresenham_draw_line(int x1, int y1, int x2, int y2) {
	int dx, dy, i ,p;
	int incx=1, incy=1;
	int x,y;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(x2<x1)
		incx=-1;
	if(y2<y1)
		incy=-1;
	x=x1;
	y=y1;
	if (dx > dy) {
		draw_pixel(x,y);
		p = 2*dy-dx;
		for(i = 0; i < dx; i++) {
			if (p >= 0) {
				y+=incy;
				p += 2*(dy-dx);
			} else p += (2*dy);
			x+=incx;
			draw_pixel(x,y);
		}
	} else {
		draw_pixel(x,y);
		p = 2*dx-dy;
		for(int i = 0; i < dy; i++) {
			if (p >= 0) {
				x+=incx;
				p += 2*(dx-dy);
			} else p += (2*dx);
			y+=incy;
			draw_pixel(x,y);
		}
	}
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	bresenham_draw_line(xs,ys,xe,ye);
	glFlush();
}

void main() {
	printf("Enter (x1,y1)\n");
	scanf("%d%d",&xs,&ys);
	printf("Enter (x2,y2)\n");
	scanf("%d%d",&xe,&ye);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("BRESENHAM LINE DRAWING");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}