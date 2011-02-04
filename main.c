// Code adapted from http://www.opengl.org/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

Display                 *dpy;
Window                  root,parent;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

extern Window ToonGetRootWindow(Display*, int, Window*);

void initGL(int width, int height) {
 glViewport(0, 0, width, height);
 glClearColor(1.0, 1.0, 1.0, 1.0);

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-width/2,width/2, -height/2, height/2, 1., 20.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);
}

void drawQuad(x, y, w, h) {
	int x1 = -(w/2)+x;
	int y1 = -(h/2)+y;

	int x2 = (w/2)+x;
	int y2 = -(h/2)+y;

	int x3 = (w/2)+x;
	int y3 = (h/2)+y;

	int x4 = -(w/2)+x;
	int y4 = (h/2)+y;

	glBegin(GL_QUADS);
		glColor3f(0., 0., 0.); glVertex3f(x1, y1, 0.);
		glColor3f(0., 0., 0.); glVertex3f(x2, y2, 0.);
		glColor3f(0., 0., 0.); glVertex3f(x3, y3, 0.);
		glColor3f(0., 0., 0.); glVertex3f(x4, y4, 0.);
	glEnd();
} 

void drawStatic(int width, int height, int size, int ratio) {
        int x, y, count;
	count = 0;
	for (x = -width/2; x < width; x+=size) {
		for (y = -height/2; y < height; y+=size) {
			int rand = random() % 100;
			if (rand > ratio) {
				drawQuad(x, y, size, size);
			}
		}
	}
}
 
int main(int argc, char *argv[]) {

	dpy = XOpenDisplay(NULL);
	vi = glXChooseVisual(dpy, 0, att);
	cmap = XCreateColormap(dpy, DefaultRootWindow(dpy), vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	win = ToonGetRootWindow(dpy, 0, &parent);
	XChangeWindowAttributes(dpy, win, 0, &swa);
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	glDisable(GL_DEPTH_TEST); 
	int width = DisplayWidth(dpy, 0);
	int height = DisplayHeight(dpy, 0);
	initGL(width, height);

	while(1) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawStatic(width, height, 10, 50);
		usleep(16512);
		glXSwapBuffers(dpy, win);
	}
}
