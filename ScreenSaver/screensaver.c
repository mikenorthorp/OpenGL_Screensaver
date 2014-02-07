
/************************************************************************************

	File: 			screensaver.c

	Description:	An open GL program that displays a screen saver with various functionality, morphing, sparkles,
					and bonus effects

	Author:			Michael Northorp (modified the point.c from course website as well as other examples)

*************************************************************************************/

/* include the library header files */

// Freeglut header
#include <GL\freeglut.h>

/* Global variables */

// Mouse variables
int   mousePressed = 0;
float mouseX=0, mouseY=0;

// Window size parameters
float windowHieght = 640.0;
float windowWidth  = 640.0;

// Interporlation variable
float interp = 0.0f;
int interpFlip = 0;

// Defines a point with x and y coordinate
typedef float x_y_coord[2];

float buttonWidth = 0.3f;
float buttonHeight = 0.2f;

// Sparkle coordinate
x_y_coord sparkleCoord = {0.0f, 0.0f};

// Button x,y coordinates for 4 buttons for top right corner of buttons
x_y_coord buttons[] = {{-0.7f, -0.6f}, {-0.3f, -0.6f}, {0.1f, -0.6f}, {0.5f, -0.6f}};

int morphButtonPressed = 0;
int sparkleButtonPressed = 0;
int sparksButtonPresssed = 0;
int bonusButtonPressed = 0;

// Coordinates for right and left side of N
// First half of N
x_y_coord left_half_n[] = {{-0.5f, 0.5f}, // Vertex 1
{-0.3f, 0.5f}, // Vertex 2
{-0.1f, 0.2f}, // Vertex 3
{-0.1f, -0.1f}, // Vertex 4
{-0.3f, 0.18f}, // Vertext 5
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

// This draws the sparkle
void drawSparkle(void) {
	// Center of sparkle is the coordinates given by sparkleCoord

}

void drawButtons(void) {
	// Var for loop
	int i = 0;

	for(i=0;i<4;i++) {
		// Begin button drawing
		glBegin(GL_POLYGON);
			// Set color to RED
			glColor3f(0, 0, 1);

			// Draws each button, 4 corners
			glVertex2f(buttons[i][0], buttons[i][1]);
			glVertex2f(buttons[i][0]+buttonWidth, buttons[i][1]);
			glVertex2f(buttons[i][0]+buttonWidth, buttons[i][1]-buttonHeight);
			glVertex2f(buttons[i][0], buttons[i][1]-buttonHeight);

			//TODO Add bitmap text

		glEnd();
	}
}

void drawStar(void) {
	// Var for loop
	int i = 0;

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

	// First half of Star
	glBegin(GL_TRIANGLE_FAN);
		// Set color to RED
		glColor3f(0, 1, 1);
		// First part of triangle fan
		for(i=0; i<7; i++) {
			glVertex2f(left_half_n[i][0], left_half_n[i][1]);
		}
	glEnd();

	// Second half of Star
	glBegin(GL_TRIANGLE_FAN);
		// Set color to RED
		glColor3f(0, 1, 1);
		// First part of triangle fan
		for(i=0; i<7; i++) {
			glVertex2f(right_half_n[i][0], right_half_n[i][1]);
		}
	glEnd();
}


void morphLetter(void) {

	// Var for loop
	int i = 0;

	// First half of N
	glBegin(GL_TRIANGLE_FAN);
		// Set color to Yellow
		glColor3f(0, 1, 1);
		// First part of triangle fan
		for(i=0; i<7; i++) {
			switch(i)
			{
				case 0:
					glVertex2f((1-interp) * left_half_n[1][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[1][1] + interp * left_half_star[i][1]);
					break;
				case 1:
					glVertex2f((1-interp) * left_half_n[0][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[0][1] + interp * left_half_star[i][1]);
					break;
				case 2:
					glVertex2f((1-interp) * left_half_n[6][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[6][1] + interp * left_half_star[i][1]);
					glVertex2f((1-interp) * left_half_n[5][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[5][1] + interp * left_half_star[i][1]);
					break;
				case 3:
					glVertex2f((1-interp) * left_half_n[4][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[4][1] + interp * left_half_star[i][1]);
					break;
				case 4:
					glVertex2f((1-interp) * left_half_n[3][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[3][1] + interp * left_half_star[i][1]);
					break;
				case 5:
					glVertex2f((1-interp) * left_half_n[2][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[2][1] + interp * left_half_star[i][1]);
					break;
				default :
					break;
			}
		}
	glEnd();

	// Second half of N
	glBegin(GL_TRIANGLE_FAN);
		// Set color to Yellow
		glColor3f(0, 1, 1);
		// First part of triangle fan
		for(i=0; i<7; i++) {
		switch(i)
			{
				case 0:
					glVertex2f((1-interp) * right_half_n[0][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[0][1] + interp * right_half_star[i][1]);
					break;
				case 1:
					glVertex2f((1-interp) * right_half_n[6][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[6][1] + interp * right_half_star[i][1]);
					glVertex2f((1-interp) * right_half_n[5][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[5][1] + interp * right_half_star[i][1]);
					break;
				case 2:
					glVertex2f((1-interp) * right_half_n[4][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[4][1] + interp * right_half_star[i][1]);
					break;
				case 3:
					glVertex2f((1-interp) * right_half_n[3][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[3][1] + interp * right_half_star[i][1]);
					break;
				case 4:
					glVertex2f((1-interp) * right_half_n[2][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[2][1] + interp * right_half_star[i][1]);
					break;
				case 5:
					glVertex2f((1-interp) * right_half_n[1][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[1][1] + interp * right_half_star[i][1]);
					break;
				default :
					break;
			}
		}
	glEnd();

}

// Runs when program is idle
void myIdle(void)
{

	// update the interpolation variable depending on value of the flip variable
	if (interpFlip == 0) {
		interp += 0.003f;
	} else if (interpFlip == 1) {
		interp -= 0.003f;
	}

	// Flips the interp to subtract or add, depending on the part of the morph it is in
	if (interp >= 1.0) {
		interpFlip = 1;
	} else if (interp <= 0.0 && interpFlip != 0) {
		interpFlip = 0;
	}

	// now force OpenGL to redraw the change
	glutPostRedisplay();
}

/************************************************************************

	Function:		mouseEventListener

	Description:	Listens for position of mouse

*************************************************************************/
void mouseEventListener(int button, int state, int x, int y)
{
	// if the left button is pressed then note the position and force a re-draw
	if (button==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)
	{
		// store that the mouse is pressed
		mousePressed = 1;

		// We must invert y coordinate first
		y = windowHieght - (float)y;

		// Normalize mouse position between -1.0 and 1.0
		mouseX = ((float)x/(windowWidth/2))-1;
		mouseY = ((float)y/(windowWidth/2))-1;

		// now force OpenGL to redraw the change
		glutPostRedisplay();
	}

}



/************************************************************************

	Function:		display

	Description:	Draws initial static openGL. Sets up buttons, letter N and menu area

*************************************************************************/
void display(void)
{

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	if(!morphButtonPressed) {
		drawLetter();
	}

	// Always draw base buttons, but draw over if one is pressed
	drawButtons();

	// if we have a mouse position
	if (mousePressed)
	{
		mousePressed = 0;

		// Morph button depressed
		if(mouseX >= buttons[0][0] && mouseX <= (buttons[0][0]+buttonWidth) &&
		   mouseY <= buttons[0][1] && mouseY >= (buttons[0][1]-buttonHeight) && morphButtonPressed) {
		   	// This disables the morph and reverts back to the letter N
			morphButtonPressed = 0;
		// Morph button is pressed
		} else if (mouseX >= buttons[0][0] && mouseX <= (buttons[0][0]+buttonWidth) &&
		   		   mouseY <= buttons[0][1] && mouseY >= (buttons[0][1]-buttonHeight)) {
			morphButtonPressed = 1;
			// Reset interp to 0 to make smooth transition
			interp = 0.0;
		}

		// Sparkle button depressed
		if(mouseX >= buttons[1][0] && mouseX <= (buttons[1][0]+buttonWidth) &&
		   mouseY <= buttons[1][1] && mouseY >= (buttons[1][1]-buttonHeight) && sparkleButtonPressed) {
			sparkleButtonPressed = 0;
		// Sparkle button is pressed
		} else if (mouseX >= buttons[1][0] && mouseX <= (buttons[1][0]+buttonWidth) &&
		   mouseY <= buttons[1][1] && mouseY >= (buttons[1][1]-buttonHeight)) {
			sparkleButtonPressed = 1;
		}

		// Spark button depressed
		if(mouseX >= buttons[2][0] && mouseX <= (buttons[2][0]+buttonWidth) &&
		   mouseY <= buttons[2][1] && mouseY >= (buttons[2][1]-buttonHeight) && sparksButtonPresssed) {
			sparksButtonPresssed = 0;
		// Sparkle button is pressed
		} else if (mouseX >= buttons[2][0] && mouseX <= (buttons[2][0]+buttonWidth) &&
		   mouseY <= buttons[2][1] && mouseY >= (buttons[2][1]-buttonHeight)) {
			sparksButtonPresssed = 1;
		}

		// Bonus button depressed
		if(mouseX >= buttons[3][0] && mouseX <= (buttons[3][0]+buttonWidth) &&
		   mouseY <= buttons[3][1] && mouseY >= (buttons[3][1]-buttonHeight) && bonusButtonPressed) {
			bonusButtonPressed = 0;
		// Bonuse button pressed
		} else if (mouseX >= buttons[3][0] && mouseX <= (buttons[3][0]+buttonWidth) &&
		   mouseY <= buttons[3][1] && mouseY >= (buttons[3][1]-buttonHeight)) {
			bonusButtonPressed = 1;
		}
	}

	// Draw letter if morph button is pressed and change button
	if(morphButtonPressed) {
		// Change button color

		// Morph letter
		morphLetter();
	}

	if(sparkleButtonPressed) {
		// Change button color

		// Morph letter
		drawStar();
	}

	if(sparksButtonPresssed) {
		// Change button color

		// Morph letter
		drawStar();
	}

	if(bonusButtonPressed) {
		// Change button color

		// Morph letter
		drawStar();
	}

	// send all output to display
	glutSwapBuffers();
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// set window size
	glutInitWindowSize(640,640);
	// open the screen window
	glutCreateWindow("Screensaver");
	// register redraw function
	glutDisplayFunc(display);
	// register the idle function
	glutIdleFunc(myIdle);
	// register mouse function
	glutMouseFunc(mouseEventListener);
	//initialize the rendering context
	init();
	// go into a perpetual loop
	glutMainLoop();
}
