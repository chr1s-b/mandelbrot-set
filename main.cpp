//============================================================================
// SETUP:
// http://www.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html
//============================================================================

#include <windows.h>  // For MS Windows
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

#include <iostream>
#include <string>
using namespace std;
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */

float interval = 1.0;
int rows = 640;
int cols = 640;
int xoff = 0;
int yoff = 0;
float FOV = 4.0;
float x_new;
int maxIteration = 100;

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

   glBegin( GL_POINTS );
   for (int row = 0; row < rows; row++) {
	   for (int col = 0; col < cols; col++) {
		   float c_re = (col + (xoff/FOV)/interval - cols/2.)*FOV/cols;
		   float c_im = (row + (yoff/FOV)/interval - rows/2.)*FOV/cols;
		   float x = 0; float y = 0;
		   int iteration = 0;
		   while ((x*x+y*y <= 4) && (iteration < maxIteration)) {
			   x_new = x*x - y*y + c_re;
			   y = 2*x*y + c_im;
			   x = x_new;
			   iteration++;
		   }
		   if (iteration < maxIteration) {
			   glColor3f(((255-iteration*10)%255)/255.,0.,1.);
		   } else {
			   glColor3f(0.,0.,0.);
		   }
		   glVertex2f((interval*col*2/cols)-1.,(interval*row*2/rows)-1.);
	   }
   }
   glEnd();
   glFlush();  // Render now
}

void zoom(int x,int y,float factor) {
	x -= cols/2.; y -= rows/2.;
	xoff = x*FOV + xoff;
	yoff = y*-FOV + yoff;
	FOV = FOV * factor;
	return;
}

void keypress(unsigned char Key, int x, int y) {
	switch (Key) {
	case 27: exit(0); break;
	case 'Q': zoom(x,y,10/9.); break;
	case 'W': zoom(x,y,9/10.); break;
	case 'q': zoom(x,y,10/9.); break;
	case 'w': zoom(x,y,9/10.); break;
	}
	glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitWindowSize(cols, rows);   // Set the window's initial width & height
   glutCreateWindow("Mandelbrot Set"); // Create a window with the given title
   glutInitWindowPosition(100, 50); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutKeyboardFunc(keypress); // Reference the function to deal with keyboard events
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
