
/************************************************************************************

	File: 			screensaver.c

	Description:	An open GL program that displays a screen saver with various functionality

	Author:			Michael Northorp (modified the point.c from course website, kept similar structure)

*************************************************************************************/

/* include the library header files */

// Freeglut header
#include <GL\freeglut.h>

/* Global variables */

// Interporlation variable
float interp = 0.0;

typedef float x_y_coord[2];

// Coordinates for right and left side of N
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

// Coordinates for left and right side of star
// Left half of star
x_y_coord left_half_star[] = {{-0.3f, 0.45f}, // Vertex 1
{-0.7f, 0.45f}, // Vertex 2
{-0.33f, 0.2f}, // Vertext 3
{-0.45f, -0.1f}, // Vertex 4
{0.0f, 0.15f}, // Vertex 5
{0.0f, 0.8f}}; // Vertex 6

// Right half of star
x_y_coord right_half_star[] = {{0.3f, 0.45f}, // Vertex 1
{0.7f, 0.45f}, // Vertex 2
{0.33f, 0.2f}, // Vertex 3
{0.45f, -0.1f}, // Vertex 4
{0.0f, 0.15f}, // Vertext 5
{0.0f, 0.8f}}; // Vertex 6

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

void drawStar(void) {
		// Var for loop
	int i = 0;

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
	
	// First half of Star
	glBegin(GL_TRIANGLE_FAN);
		// Set color to RED
		glColor3f(0, 1, 0);
		// First part of triangle fan
		for(i=0; i<6; i++) {
			glVertex2f(left_half_star[i][0], left_half_star[i][1]);
		}
	glEnd();

	// Second half of Star
	glBegin(GL_TRIANGLE_FAN);
		// Set color to RED
		glColor3f(0, 1, 0);
		// First part of triangle fan
		for(i=0; i<6; i++) {
			glVertex2f(right_half_star[i][0], right_half_star[i][1]);
		}
	glEnd();
}


void drawLetter(void) {

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
			switch(i) 
			{
				case 1:
					glVertex2f((1-interp) * left_half_n[i][0] + interp * left_half_star[2][0], (1-interp) * left_half_n[i][1] + interp * left_half_star[2][1]);
					break;
				case 2:
					glVertex2f((1-interp) * left_half_n[i][0] + interp * left_half_star[1][0], (1-interp) * left_half_n[i][1] + interp * left_half_star[1][1]);
					break;
				case 3:
					glVertex2f((1-interp) * left_half_n[i][0] + interp * left_half_star[6][0], (1-interp) * left_half_n[i][1] + interp * left_half_star[6][1]);
					break;
				case 4:
					glVertex2f((1-interp) * left_half_n[i][0] + interp * left_half_star[5][0], (1-interp) * left_half_n[i][1] + interp * left_half_star[5][1]);
					break;
				case 5:
					glVertex2f((1-interp) * left_half_n[i][0] + interp * left_half_star[4][0], (1-interp) * left_half_n[i][1] + interp * left_half_star[4][1]);
					break;
				case 6:
					glVertex2f((1-interp) * left_half_n[i][0] + interp * left_half_star[3][0], (1-interp) * left_half_n[i][1] + interp * left_half_star[3][1]);
					break;
				case 7:
					glVertex2f((1-interp) * left_half_n[i][0] + interp * left_half_star[3][0], (1-interp) * left_half_n[i][1] + interp * left_half_star[3][1]);
					break;
				default :
					break;
			}
		}
	glEnd();

	/*
	// Second half of N
	glBegin(GL_TRIANGLE_FAN);
		// Set color to RED
		glColor3f(1, 0, 0);
		// First part of triangle fan
		for(i=0; i<7; i++) {
			if(i == 7) {
				glVertex2f((1-interp) * right_half_n[i][0] + interp * right_half_star[6][0], (1-interp) * right_half_n[i][1] + interp * right_half_star[6][1]);
			} else {
				glVertex2f((1-interp) * right_half_n[i][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[i][1] + interp * right_half_star[i][1]);
			}
		}
	glEnd();
	*/

}

// Runs when program is idle
void myIdle(void)
{

	// update the interpolation variable 
	interp += 0.00005;


	if (interp >= 1.0) {
		interp = 0.0;
	}

	// now force OpenGL to redraw the change
	glutPostRedisplay();
}


/************************************************************************

	Function:		display

	Description:	Draws initial static openGL. Sets up buttons, letter N and menu area

*************************************************************************/
void display(void)
{

	drawLetter();
	//drawStar();

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
	// register the idle function
	glutIdleFunc(myIdle);     
	//initialize the rendering context
	init();
	// go into a perpetual loop
	glutMainLoop();
}
