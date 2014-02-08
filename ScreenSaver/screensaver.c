
/************************************************************************************

	File: 			screensaver.c

	Description:	An open GL program that displays a screen saver with various functionality, morphing, sparkles,
					and bonus effects

	Author:			Michael Northorp (modified the point.c from course website as well as other examples)

*************************************************************************************/

/* include the library header files */

// Freeglut header
#include <GL\freeglut.h>
#include <math.h>

/* Global variables */

//  Ratio of the circumference to the diameter of a circle
#define PI 3.14159265f

// Conversion multiplier for converting from degrees to Radians
#define DEG_TO_RAD PI/180.0f

// angle of rotation
float theta = 0.0;

// Mouse variables
int   mousePressed = 0;
float mouseX=0, mouseY=0;

// Window size parameters
float windowHieght = 640.0;
float windowWidth  = 640.0;

// Interporlation variable
float interp = 0.0f;
float sparkleInterp = 0.0f;
int interpFlip = 0;

// Defines a point with x and y coordinate
typedef float x_y_coord[2];

// This struct contains coordinates for a spark, starting coordinates, and if
// it is active or not
typedef struct
{
    float xCoord;
    float yCoord;
	float xStart;
	float yStart;
	float active;
} spark;

int sparkXDir = 0;
int sparkYDir = 0;

spark sparkList[] = {{2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Up spark
{-2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Down spark
{0.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Left spark
{0.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Right spark
{-2.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Up/Left spark
{-2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down/Left
{2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down /Right
{2.0f, 2.0f, 0.0f, 0.0f, 0.0f},	// Up/Right
{2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Up spark
{-2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Down spark
{0.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Left spark
{0.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Right spark
{-2.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Up/Left spark
{-2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down/Left
{2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down /Right
{2.0f, 2.0f, 0.0f, 0.0f, 0.0f},	// Up/Right
{2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Up spark
{-2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Down spark
{0.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Left spark
{0.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Right spark
{-2.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Up/Left spark
{-2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down/Left
{2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down /Right
{2.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Up/Right
{2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Up spark
{-2.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // Down spark
{0.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Left spark
{0.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Right spark
{-2.0f, 2.0f, 0.0f, 0.0f, 0.0f}, // Up/Left spark
{-2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down/Left
{2.0f, -2.0f, 0.0f, 0.0f, 0.0f}, // Down /Right
{2.0f, 2.0f, 0.0f, 0.0f, 0.0f}}; // Up / Right

float buttonWidth = 0.3f;
float buttonHeight = 0.2f;

// Sparkle coordinate
x_y_coord sparkleCoord = {0.0f, 0.0f};

// Set the current vertex and next vertex for interpolation of sparkle
int currentPoint = 0;
int goingToPoint = 1;

// Scale to grow and shrink
float scale = 0.0f;
int scaleFlip = 0;

// Scale to shrink/grow sqaures in background
float sqaureScale = 0.0f;
float bonusMod = 0;

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

// All of the coordinates put in an array that contains the point vertex while
// morphing
x_y_coord interpCoords[] = {{-0.5f, 0.5f}, // Vertex 1
{-0.3f, 0.5f}, // Vertex 2
{-0.1f, 0.2f}, // Vertex 3
{-0.1f, -0.1f}, // Vertex 4
{-0.3f, 0.18f}, // Vertext 5
{-0.3f, -0.3f}, // Vertex 6
{-0.5f, -0.3f}, // Vertex 7
{0.26f, -0.3f}, // Vertex 8
{0.06f, -0.3f}, // Vertex 9
{-0.1f, -0.1f}, // Vertex 10
{-0.1f, 0.2f}, // Vertex 11
{0.06f, -0.1f}, // Vertex 12
{0.06f, 0.5f}, // Vertex 13
{0.26f, 0.5f}}; // Vertex 14

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

// This bonus draws some psychedalic sqaures in the background of the page
void drawBonus(void) {
	int i = 0;

	// If bonus button pressed, then render bonus
	if(bonusButtonPressed) {
		for (i=0;i<10;i++) {
			bonusMod = (float)i/10.0f;

			// Set the color
			glColor3f(1, bonusMod, 0);

			// Set the line width
			glLineWidth(2.0);
			glBegin(GL_LINE_STRIP);
				glVertex2f((-2.0f+bonusMod)*sqaureScale, (-2.0f+bonusMod)*sqaureScale);
				glVertex2f((-2.0f+bonusMod)*sqaureScale, (2.0f-bonusMod)*sqaureScale);
				glVertex2f((2.0f-bonusMod)*sqaureScale, (2.0f-bonusMod)*sqaureScale);
				glVertex2f((2.0f-bonusMod)*sqaureScale, (-2.0f+bonusMod)*sqaureScale);
				glVertex2f((-2.0f+bonusMod)*sqaureScale, (-2.0f+bonusMod)*sqaureScale);
			glEnd();
		}

		for (i=0;i<10;i++) {
			bonusMod = (float)i/10.0f;

			// Set the color
			glColor3f(bonusMod, 1, 0.2);

			glLineWidth(1.0);
			glBegin(GL_LINE_STRIP);
				glVertex2f((-1.0f+bonusMod)*sqaureScale, (-1.0f+bonusMod)*sqaureScale);
				glVertex2f((-1.0f+bonusMod)*sqaureScale, (1.0f-bonusMod)*sqaureScale);
				glVertex2f((1.0f-bonusMod)*sqaureScale, (1.0f-bonusMod)*sqaureScale);
				glVertex2f((1.0f-bonusMod)*sqaureScale, (-1.0f+bonusMod)*sqaureScale);
				glVertex2f((-1.0f+bonusMod)*sqaureScale, (-1.0f+bonusMod)*sqaureScale);
			glEnd();
		}
	}
}

void drawMenu(void) {
	// Draw a simple background for the menu area
	// Set color of menu
	glColor3f(1.0, 1.0, 0.1);

	// Draw menu as a polygon
	glBegin(GL_POLYGON);
		glVertex2f(-1.0, -0.4f);
		glVertex2f(1.0, -0.4f);
		glVertex2f(1.0, -1.0f);
		glVertex2f(-1.0, -1.0f);
	glEnd();
}

// This function draws sparks coming out of the center of the spark
void drawSparks(void) {
	int i = 0;

	for (i=0; i<32;i++) {
		// Shoot off predefine sparks in random lines from the center
		// Push the matrix
		glPushMatrix();

		// Enable blending
		glEnable(GL_BLEND);
		// Set blending mode
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// The position of the current center to the sparkleCoord

		// Check if spark is done its lifespan
		if(sparkList[i].active >= 1.0) {
			// Deactive spark
			sparkList[i].active = 0.0;
		}

		// If inactive then set the start to the sparkle coords
		if(sparkList[i].active == 0.0) {
			sparkList[i].xStart = sparkleCoord[0];
			sparkList[i].yStart = sparkleCoord[1];
		}

		// Increase active count
		sparkList[i].active += 0.01;

		switch(i%8) {
			case 0: // Up spark
				sparkXDir = sparkList[i].active*1;
				sparkYDir = sparkList[i].active*0;
				break;
			case 1: // Down spark
				sparkXDir = sparkList[i].active*-1;
				sparkYDir = sparkList[i].active*0;
				break;
			case 2: // Left spark
				sparkXDir = sparkList[i].active*0;
				sparkYDir = sparkList[i].active*-1;
				break;
			case 3: // Right spark
				sparkXDir = sparkList[i].active*0;
				sparkYDir = sparkList[i].active*1;
				break;
			case 4: // Up/Left spark
				sparkXDir = sparkList[i].active*-1;
				sparkYDir = sparkList[i].active*1;
				break;
			case 5: // Down/left
				sparkXDir = sparkList[i].active*-1;
				sparkYDir = sparkList[i].active*-1;
				break;
			case 6: // Down/Right
				sparkXDir = sparkList[i].active*1;
				sparkYDir = sparkList[i].active*-1;
				break;
			case 7: // Up/Right
				sparkXDir = sparkList[i].active*1;
				sparkYDir = sparkList[i].active*1;
				break;
			default:
				break;
		}


		printf("%d", sparkXDir);
		glTranslatef(sparkList[i].xStart+sparkList[i].active, sparkList[i].yStart+sparkList[i].active, 0.0);
		glBegin(GL_LINES);
			glColor4f(1.0, 0.0, 0, 0.0);
			glVertex3f(sparkList[i].xCoord*scale, sparkList[i].yCoord*scale, 0.0);
			glColor4f(1.0, 0.0, 0, 1.0);
			glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		// Pop off the matrix
		glPopMatrix();
	}
}

// This draws the sparkle
void drawSparkle(void) {
	// Center of sparkle is the coordinates given by sparkleCoord
	// Draw the Lines of sparkle
	// Push the matrix
	glPushMatrix();

	// Set the color to yellow
	glColor3f(1, 1, 0);

	// Enable blending
	glEnable(GL_BLEND);
	// Set blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// The position of the current center to the sparkleCoord
	glTranslatef(sparkleCoord[0], sparkleCoord[1], 0.0);
	// Rotate along Z
	glRotatef(theta, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(-0.1*scale, 0.0*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(0.1*scale, 0.0*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(0.0*scale, 0.1*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(0.0*scale, -0.1*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(-0.05*scale, -0.05*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(0.05*scale, 0.05*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(-0.05*scale, 0.05*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(1.0, 1.0, 0, 0.0);
		glVertex3f(0.05*scale, -0.05*scale, 0.0);
		glColor4f(1.0, 1.0, 0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	// Pop off the matrix
	glPopMatrix();
}

void drawButtons(void) {
	// Var for loop
	int i = 0;

	// Loop through to draw all 4 buttons
	for(i=0;i<4;i++) {


		// Draws each buttons shadow, 4 corners
		glBegin(GL_POLYGON);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2f(buttons[i][0], buttons[i][1]);
			glVertex2f(buttons[i][0]+buttonWidth+0.01, buttons[i][1]);
			glVertex2f(buttons[i][0]+buttonWidth+0.01, buttons[i][1]-buttonHeight-0.01);
			glVertex2f(buttons[i][0], buttons[i][1]-buttonHeight-0.01);
		glEnd();

		// Begin button drawing
		glBegin(GL_POLYGON);
			// Set color to Blue as default
			glColor3f(0, 0, 1);

			// Recolor if pressed
			if(morphButtonPressed && i == 0) {
				glColor3f(1,0,0);
			}

			// Recolor if pressed
			if(sparkleButtonPressed && i == 1) {
				glColor3f(1,0,0);
			}

			// Recolor if pressed, and sparkle button is pressed
			if(sparksButtonPresssed && i == 2 && sparkleButtonPressed) {
				glColor3f(1,0,0);
			}

			// Recolor if pressed
			if(bonusButtonPressed && i == 3) {
				glColor3f(1,0,0);
			}

			// Draws each button, 4 corners
			glVertex2f(buttons[i][0], buttons[i][1]);
			glVertex2f(buttons[i][0]+buttonWidth, buttons[i][1]);
			glVertex2f(buttons[i][0]+buttonWidth, buttons[i][1]-buttonHeight);
			glVertex2f(buttons[i][0], buttons[i][1]-buttonHeight);

		glEnd();
	}
}

// This function draws the text for all four buttons
void drawButtonText(void) {
	// Set color to yellow
	glColor3f(1, 1, 0);
	// Morph button
	glRasterPos3f(buttons[0][0]+0.02f , buttons[0][1]-0.12f ,0.0f);
	glutBitmapString( GLUT_BITMAP_HELVETICA_18 , "MORPH" );

	// Sparkle
	glRasterPos3f(buttons[1][0]+0.02f , buttons[1][1]-0.12f ,0.0f);
	glutBitmapString( GLUT_BITMAP_HELVETICA_18 , "SPARKLE" );

	// Sparks
	glRasterPos3f(buttons[2][0]+0.02f , buttons[2][1]-0.12f ,0.0f);
	glutBitmapString( GLUT_BITMAP_HELVETICA_18 , "SPARKS" );

	// Bonus
	glRasterPos3f(buttons[3][0]+0.02f , buttons[3][1]-0.12f ,0.0f);
	glutBitmapString( GLUT_BITMAP_HELVETICA_18 , "BONUS" );
}


// This draws the letter or morphs it into a star depending on if the morph
// button is pressed
void morphLetter(void) {

	// Var for loop
	int i = 0;

	// Morphs or draws letter depending if button is pressed
	// This allows us to get the vertex no matter what and store it in the first_half_coors
	// and second_half_coords
	if (!morphButtonPressed) {
		interp = 0.0;
	}

	// First half of N
	glBegin(GL_TRIANGLE_FAN);
		// Set color to Red
		glColor3f(1, 0, 0);
		// First part of triangle fan
		for(i=0; i<7; i++) {
			switch(i)
			{
				case 0:
					glVertex2f((1-interp) * left_half_n[1][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[1][1] + interp * left_half_star[i][1]);
					interpCoords[1][0] = (1-interp) * left_half_n[1][0] + interp * left_half_star[i][0];
					interpCoords[1][1] = (1-interp) * left_half_n[1][1] + interp * left_half_star[i][1];
					break;
				case 1:
					glVertex2f((1-interp) * left_half_n[0][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[0][1] + interp * left_half_star[i][1]);
					interpCoords[0][0] = (1-interp) * left_half_n[0][0] + interp * left_half_star[i][0];
					interpCoords[0][1] = (1-interp) * left_half_n[0][1] + interp * left_half_star[i][1];
					break;
				case 2:
					glVertex2f((1-interp) * left_half_n[6][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[6][1] + interp * left_half_star[i][1]);
					glVertex2f((1-interp) * left_half_n[5][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[5][1] + interp * left_half_star[i][1]);

					interpCoords[6][0] = (1-interp) * left_half_n[6][0] + interp * left_half_star[i][0];
					interpCoords[6][1] = (1-interp) * left_half_n[6][1] + interp * left_half_star[i][1];

					interpCoords[5][0] = (1-interp) * left_half_n[5][0] + interp * left_half_star[i][0];
					interpCoords[5][1] = (1-interp) * left_half_n[5][1] + interp * left_half_star[i][1];
					break;
				case 3:
					glVertex2f((1-interp) * left_half_n[4][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[4][1] + interp * left_half_star[i][1]);
					interpCoords[4][0] = (1-interp) * left_half_n[4][0] + interp * left_half_star[i][0];
					interpCoords[4][1] = (1-interp) * left_half_n[4][1] + interp * left_half_star[i][1];
					break;
				case 4:
					glVertex2f((1-interp) * left_half_n[3][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[3][1] + interp * left_half_star[i][1]);
					interpCoords[3][0] = (1-interp) * left_half_n[3][0] + interp * left_half_star[i][0];
					interpCoords[3][1] = (1-interp) * left_half_n[3][1] + interp * left_half_star[i][1];
					break;
				case 5:
					glVertex2f((1-interp) * left_half_n[2][0] + interp * left_half_star[i][0], (1-interp) * left_half_n[2][1] + interp * left_half_star[i][1]);
					interpCoords[2][0] = (1-interp) * left_half_n[2][0] + interp * left_half_star[i][0];
					interpCoords[2][1] = (1-interp) * left_half_n[2][1] + interp * left_half_star[i][1];
					break;
				default :
					break;
			}
		}
	glEnd();

	// Second half of N
	glBegin(GL_TRIANGLE_FAN);
		// Set color to Red
		glColor3f(1, 0, 0);
		// First part of triangle fan
		for(i=0; i<7; i++) {
		switch(i)
			{
				case 0:
					glVertex2f((1-interp) * right_half_n[0][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[0][1] + interp * right_half_star[i][1]);
					interpCoords[7][0] = (1-interp) * right_half_n[0][0] + interp * right_half_star[i][0];
					interpCoords[7][1] = (1-interp) * right_half_n[0][1] + interp * right_half_star[i][1];
					break;
				case 1:
					glVertex2f((1-interp) * right_half_n[6][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[6][1] + interp * right_half_star[i][1]);
					glVertex2f((1-interp) * right_half_n[5][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[5][1] + interp * right_half_star[i][1]);

					interpCoords[13][0] = (1-interp) * right_half_n[6][0] + interp * right_half_star[i][0];
					interpCoords[13][1] = (1-interp) * right_half_n[6][1] + interp * right_half_star[i][1];

					interpCoords[12][0] = (1-interp) * right_half_n[5][0] + interp * right_half_star[i][0];
					interpCoords[12][1] = (1-interp) * right_half_n[5][1] + interp * right_half_star[i][1];
					break;
				case 2:
					glVertex2f((1-interp) * right_half_n[4][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[4][1] + interp * right_half_star[i][1]);
					interpCoords[11][0] = (1-interp) * right_half_n[4][0] + interp * right_half_star[i][0];
					interpCoords[11][1] = (1-interp) * right_half_n[4][1] + interp * right_half_star[i][1];
					break;
				case 3:
					glVertex2f((1-interp) * right_half_n[3][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[3][1] + interp * right_half_star[i][1]);
					interpCoords[10][0] = (1-interp) * right_half_n[3][0] + interp * right_half_star[i][0];
					interpCoords[10][1] = (1-interp) * right_half_n[3][1] + interp * right_half_star[i][1];
					break;
				case 4:
					glVertex2f((1-interp) * right_half_n[2][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[2][1] + interp * right_half_star[i][1]);
					interpCoords[9][0] = (1-interp) * right_half_n[2][0] + interp * right_half_star[i][0];
					interpCoords[9][1] = (1-interp) * right_half_n[2][1] + interp * right_half_star[i][1];
					break;
				case 5:
					glVertex2f((1-interp) * right_half_n[1][0] + interp * right_half_star[i][0], (1-interp) * right_half_n[1][1] + interp * right_half_star[i][1]);
					interpCoords[8][0] = (1-interp) * right_half_n[1][0] + interp * right_half_star[i][0];
					interpCoords[8][1] = (1-interp) * right_half_n[1][1] + interp * right_half_star[i][1];
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
	if (scaleFlip == 0) {
		scale += 0.007f;
	} else if (scaleFlip == 1) {
		scale -= 0.007f;
	}

	// Flips the interp to subtract or add, depending on the part of the morph it is in
	if (scale >= 2.5) {
		scaleFlip = 1;
	} else if (scale <= 0.7 && scaleFlip != 0) {
		scaleFlip = 0;
	}

	// Sqaure scale for bonus part, scales the sqaures
	sqaureScale += 0.01f;
	if (sqaureScale >= 1.0f) {
		sqaureScale = 0.0f;
	}


	// update the angle of rotation
	theta += 2.0f;

	// if we have done a full turn, start at zero again
	if (theta >= 360.0f) {
		theta -= 360.0f;
	}

	// update the interpolation variable depending on value of the flip variable
	if (interpFlip == 0) {
		interp += 0.003f;
	} else if (interpFlip == 1) {
		interp -= 0.003f;
	}

	// Increase sparkle interpolation variable
	sparkleInterp += 0.005f;

	// Checks if the sparkle has reached a new vertice, then swap it for a new one
	if (sparkleInterp >= 1.0) {

		// Set current point to the point it is going to, based on the switch statment
		currentPoint = goingToPoint;
		// Reset sparkle Interp to 0
		sparkleInterp = 0.0f;
	}

	// Flips the interp to subtract or add, depending on the part of the morph it is in
	if (interp >= 1.0f) {
		interpFlip = 1;
	} else if (interp <= 0.0f && interpFlip != 0) {
		interpFlip = 0;
	}

	// Calculate current position of sparkle by chosing which points it is currently between
	// and where it should go next
	switch(currentPoint) {
		case 0:
			goingToPoint = 1; //done
			break;
		case 1:
			goingToPoint = 2; //done
			break;
		case 2:
			goingToPoint = 11; //done
			break;
		case 3:
			goingToPoint = 4; //uneeded
			break;
		case 4:
			goingToPoint = 5; //Done
			break;
		case 5:
			goingToPoint = 6; //Done
			break;
		case 6:
			goingToPoint = 0; //Done
			break;

		// Second half
		case 7:
			goingToPoint = 8; //done
			break;
		case 8:
			goingToPoint = 9; //Done
			break;
		case 9:
			goingToPoint = 4; //Done
			break;
		case 10:
			goingToPoint = 11; //uneeded
			break;
		case 11:
			goingToPoint = 12; //done
			break;
		case 12:
			goingToPoint = 13; //done
			break;
		case 13:
			goingToPoint = 7; //done
			break;
		default:
			break;
	}

	sparkleCoord[0] = (1-sparkleInterp) * interpCoords[currentPoint][0] + sparkleInterp * interpCoords[goingToPoint][0];
	sparkleCoord[1] = (1-sparkleInterp) * interpCoords[currentPoint][1] + sparkleInterp * interpCoords[goingToPoint][1];

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

// This checks if a mouse button was pressed and does logic based on its location
void mouseCheck(void) {
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
}

// This performs button stuff depending on if a button is pressed or not
void buttonLogic(void) {
	if(sparkleButtonPressed) {
		// Draw the spinning sparkle that traces the N and star
		drawSparkle();
	}

	if(sparksButtonPresssed) {
		// Draw Sparks only if sparkle button is pressed
		if(sparkleButtonPressed) {
			drawSparks();
		}
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

	// Draw bonus in background if button pressed
	drawBonus();

	// Morphs the letter if button pressed, else stays as N
	morphLetter();

	// Draw background for menu
	drawMenu();

	// Always draw base buttons and shadows, but draw over if one is pressed
	drawButtons();

	// Checks if mouse is pressed
	mouseCheck();

	// Performs button operations depending on mouse position
	buttonLogic();

	// Draw text for buttons
	drawButtonText();

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
