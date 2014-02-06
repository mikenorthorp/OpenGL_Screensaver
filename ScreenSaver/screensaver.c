
/************************************************************************************

	File: 			screensaver.c

	Description:	An open GL program that displays a screen saver with various functionality

	Author:			Michael Northorp (modified the point.c from course website, kept similar structure)

*************************************************************************************/

/* include the library header files */

// Freeglut header
#include <GL\freeglut.h>

/* Global variables */
typedef float x_y_coord[2];

// First half of N
x_y_coord left_half_n[] = {{-0.5f, 0.5f}, // Vertex 1
{-0.3f, 0.5f}, // Vertex 2
{-0.1f, 0.2f}, // Vertex 3
{-0.1f, -0.1f}, // Vertex 4
{-0.3f, 0.3f}, // Vertext 5
{-0.3f, -0.3f}, // Vertex 6
{-0.5f, -0.3f}}; // Vertex 7

// second half of N
x_y_coord right_half_n[] = {{0.26f, -0.3f}, // Vertex 1
{0.06f, -0.3f}, // Vertex 2
{-0.1f, -0.1f}, // Vertex 3
{-0.1f, 0.2f}, // Vertex 4
{0.06f, -0.1f}, // Vertex 5
{0.06f, 0.5f}, // Vertex 6
{0.26f, 0.5f}}; // Vertex 7

// Coorinates for left and right side of star
// Left half of star
x_y_coord left_half_star[] = {{-0.5f, 0.5f}, // Vertex 1
{-0.3f, 0.5f}, // Vertex 2
{-0.1f, 0.2f}, // Vertex 3
{-0.1f, -0.1f}, // Vertex 4
{-0.3f, 0.3f}, // Vertext 5
{-0.3f, -0.3f}, // Vertex 6
{-0.5f, -0.3f}}; // Vertex 7

// Right half of star
x_y_coord right_half_star[] = {{-0.5f, 0.5f}, // Vertex 1
{-0.3f, 0.5f}, // Vertex 2
{-0.1f, 0.2f}, // Vertex 3
{-0.1f, -0.1f}, // Vertex 4
{-0.3f, 0.3f}, // Vertext 5
{-0.3f, -0.3f}, // Vertex 6
{-0.5f, -0.3f}}; // Vertex 7

/************************************************************************

	Function:		init

	Description:	Performs all setup for openGL

*************************************************************************/
void init(void)
{
	// Starting color is black
	glColor3f(0.0f, 0.0f, 0.0f);

	// set to projection mode
	glMatrixMode(GL_PROJECTION);

	// load the identity matrix
	glLoadIdentity();

	// set window mode to 2D orthographica and set the window size
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

/************************************************************************

	Function:		display

	Description:	Draws initial static openGL. Sets up buttons, letter N and menu area

*************************************************************************/
void display(void)
{
	// Var for loop
	int i = 0;

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
	
	// First half of N
	glBegin(GL_TRIANGLE_FAN);
		// Set color to RED
		glColor3f(1, 0, 0);
		// First part of triangle fan
		for(i=0; i<7; i++) {
			glVertex2f(left_half_n[i][0], left_half_n[i][1]);
		}
	glEnd();

	// Second half of N
	glBegin(GL_TRIANGLE_FAN);
		// Set color to RED
		glColor3f(1, 0, 0);
		// First part of triangle fan
		for(i=0; i<7; i++) {
			glVertex2f(right_half_n[i][0], right_half_n[i][1]);
		}
	glEnd();

	

	// send all output to display
	glFlush();
}


/************************************************************************

	Function:		main

	Description:	Sets up the openGL rendering context and the windowing
					system, then begins the display loop.

*************************************************************************/
void main(int argc, char** argv)
{
	// initialize the toolkit
	glutInit(&argc, argv);
	// set display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// set window size
	glutInitWindowSize(640,640);
	// set window position on screen
	//glutInitWindowPosition(100, 150);
	// open the screen window
	glutCreateWindow("Screensaver");
	// register redraw function
	glutDisplayFunc(display);
	//initialize the rendering context
	init();
	// go into a perpetual loop
	glutMainLoop();
}
