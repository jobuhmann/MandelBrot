/*--------------------------------------------------------*/
/*  CS-378           Computer Graphics     Jordan Buhmann */
/*--------------------------------------------------------*/
/*  Assignment 1 - Drawing the MandelBrot Set             */
/*--------------------------------------------------------*/

#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <cfloat>
#include <iostream>

using namespace std;

class complex
{
public:
	double real;
	double imag;

	complex(double, double);
	complex(complex&);
	complex operator *(complex);
	complex operator +(complex);
	double abs();
	   
};

complex::complex(double r = 0.0, double im = 0.0) {
	real = r;
	imag = im;
}

complex::complex(complex &c) {
	this->real = c.real;
	this->imag = c.imag;
}

complex complex::operator +(complex c) {
	complex k;
	k.real = this->real + c.real;
	k.imag = this->imag + c.imag;
	return k;
}

complex complex::operator *(complex c) {
	complex k;
	k.real = (real*c.real) - (imag*c.imag);
	k.imag = (real*c.imag) + (imag*c.real);
	return k;
}

double complex::abs() {
	complex c;
	return sqrt((c.real*c.real) + (c.imag*c.imag));
}



// Defining default values for window size, shape and location.
#define INITIAL_WIN_W 800
#define INITIAL_WIN_H 800
#define INITIAL_WIN_X 150
#define INITIAL_WIN_Y 50
#define X1 0.262
#define X2 0.263 
#define Y1 0.002
#define Y2 0.003

bool draw = true;

// Variables for keeping track of the screen window dimensions.
int windowHeight, windowWidth;


void mandelbrot()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_POINTS); // start drawing in single pixel mode
	double x1 = X1;
	double x2 = X2;
	double y1 = Y1;
	double y2 = Y2;
	for (int y = 0; y < INITIAL_WIN_H; ++y)
	{
		for (int x = 0; x < INITIAL_WIN_W; ++x)
		{
			// Work out the point in the complex plane that corresponds to this pixel in the output image.
			complex c = ((x1 + (x * (x2 - x1) / INITIAL_WIN_W)), (y1 + (y * (y2 - y1) / INITIAL_WIN_H)));

			// Start off z at (0, 0).
			complex z = (0.0, 0.0);

			// Iterate z = z^2 + c until we've iterated too many times.
			int iterations = 0;
			while (z.abs() < 2 && iterations < 1000)
			{
				z = (z * z) + c;

				iterations++;

			}
			if (iterations == 1000)
			{
				glColor3f(1.0, 0.0, 0.0); // Set color to draw mandelbrot
				// This point is in the Mandelbrot set.
				glVertex2i(x, y);				
			}
			else{
				glColor3f(1.0, 1.0, 1.0); //Set pixel to black
										  // iterations. This point isn't in the set.
				glVertex2i(x, y);
			}
		}
	}
	glEnd();
	glFlush();

}


//void mouse(int button, int state, int x, int y)
//// Function for processing mouse events.
//{
//	if (button == GLUT_MIDDLE_BUTTON)
//		switch (state)
//		{
//		
//		}
//}
//
void reshape(int w, int h)
// Callback for processing reshape events.
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

}
//
//
//void setMenus()
//// Function for creating menus.
//{
//
//	glutCreateMenu(mainMenu);
//	glutAddMenuEntry("Clear", 1);
//	glutAddMenuEntry("Exit", 2);
//	glutAttachMenu(GLUT_MIDDLE_BUTTON);
//}
//
//void mainMenu(int item)
//// Callback for processing main menu.
//{
//	switch (item)
//	{
//	case 1: clearPicture(); break;
//	case 2: std::exit(0);
//	}
//}

const int width = 600, height = 600; // window size
int windowID;

void escExit(GLubyte key, int, int)
// Callback for processing keyboard events.
{
	if (key == 27 /* ESC */) std::exit(0);
}

int main(int argc, char * argv[])
{
	
	// Mask floating point exceptions.
	_control87(MCW_EM, MCW_EM);

	// Choose RGB display mode for normal screen window.
	glutInitDisplayMode(GLUT_RGB);

	// Set initial window size, position, and title.
	glutInitWindowSize(INITIAL_WIN_W, INITIAL_WIN_H);
	glutInitWindowPosition(INITIAL_WIN_X, INITIAL_WIN_Y);
	glutCreateWindow("MandelBrot");

	// You don't (yet) want to know what this does.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)INITIAL_WIN_W, 0.0, (double)INITIAL_WIN_H);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// This is a hack.
	glTranslatef(0.375, 0.375, 0.0);

	// Set the callbacks for the normal screen window.
	glutDisplayFunc(mandelbrot);

	// Set the callback for reshape events.
	glutReshapeFunc(reshape);

	// Set the callback for keyboard events.
	glutKeyboardFunc(escExit);

	// Start the GLUT main loop.
	glutMainLoop();

}





// RUBBER BAND

//// Variable for use in rubberbanding.
//int xAnchor, yAnchor, xStretch, yStretch;
//bool rubberBanding = false;
//

//
//void drawLine(int xOld, int yOld, int xNew, int yNew)
//// Draw a line from (xOld,yOld) to (xNew,yNew).
//{
//	glBegin(GL_LINES);
//	glVertex2i(xOld, yOld);
//	glVertex2i(xNew, yNew);
//	glEnd();
//	glFlush();
//}
//
//
//
//void drawRubberBand(int xA, int yA, int xS, int yS)
//{
//	glEnable(GL_COLOR_LOGIC_OP);
//	glLogicOp(GL_XOR);
//	glBegin(GL_LINES);
//	glVertex2i(xA, yA);
//	glVertex2i(xS, yS);
//	glEnd();
//	glDisable(GL_COLOR_LOGIC_OP);
//	glFlush();
//}
//
//void rubberBand(int x, int y)
//// Callback for processing mouse motion.
//{
//	if (rubberBanding)
//	{
//		drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);
//		y = windowHeight - y;
//		xStretch = x;
//		yStretch = y;
//		drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);
//		glFlush();
//	}
//}
//

//
//void processLeftDown(int x, int y)
//// Function for processing mouse left botton down events.
//{
//	if (!rubberBanding)
//	{
//		int xNew = x;
//		int yNew = windowHeight - y;
//		xAnchor = xNew;
//		yAnchor = yNew;
//		xStretch = xNew;
//		yStretch = yNew;
//		drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);
//		rubberBanding = true;
//	}
//}
//
//
//
//void processLeftUp(int x, int y)
//// Function for processing mouse left botton up events.
//{
//	if (rubberBanding)
//	{
//		int xNew, yNew;
//		drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);
//		rubberBanding = false;
//		xNew = x;
//		yNew = windowHeight - y;
//		drawLine(xAnchor, yAnchor, xNew, yNew);
//		glFlush();
//	}
//}
//
//
//void mouse(int button, int state, int x, int y)
//// Function for processing mouse events.
//{
//	if (button == GLUT_LEFT_BUTTON)
//		switch (state)
//		{
//		case GLUT_DOWN: processLeftDown(x, y); break;
//		case GLUT_UP: processLeftUp(x, y); break;
//		}
//}
//
//
//

// HOUSE

//void drawHouse()
//{
//	// Clear the window.
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	// Draw the base of the house.
//	glBegin(GL_LINE_LOOP);
//	glVertex2i(200, 200);
//	glVertex2i(200, 500);
//	glVertex2i(500, 500);
//	glVertex2i(500, 200);
//	glEnd();
//
//	// Draw the roof of the house.
//	glBegin(GL_LINE_STRIP);
//	glVertex2i(200, 500);
//	glVertex2i(350, 630);
//	glVertex2i(500, 500);
//	glEnd();
//
//	// Draw the door of the house.
//	glBegin(GL_POINTS);
//	for (int i = 0; i < 125; i++) glVertex2i(320, 200 + i);
//	for (int i = 0; i < 60; i++) glVertex2i(320 + i, 325);
//	for (int i = 0; i < 125; i++) glVertex2i(380, 200 + i);
//	glEnd();
//
//	// Draw the antenna on the house.
//	glBegin(GL_LINES);
//	glVertex2i(200, 500);  glVertex2i(200, 600);
//	glVertex2i(175, 600);  glVertex2i(225, 600);
//	glVertex2i(175, 575);  glVertex2i(225, 575);
//	glVertex2i(175, 550);  glVertex2i(225, 550);
//	glEnd();
//
//	// Draw the base of the garage.
//	glBegin(GL_LINE_LOOP);
//	glVertex2i(500, 200);
//	glVertex2i(500, 350);
//	glVertex2i(650, 350);
//	glVertex2i(650, 200);
//	glEnd();
//
//	// Draw the roof of the garage.
//	glBegin(GL_LINE_STRIP);
//	glVertex2i(500, 350);
//	glVertex2i(575, 425);
//	glVertex2i(650, 350);
//	glEnd();
//
//	// Set polygon fill/line mode. 
//	// Forward facing polygons are filled. 
//	// Backward facing polygons are outlined. 
//	glPolygonMode(GL_FRONT, GL_FILL);
//	glPolygonMode(GL_BACK, GL_LINE);
//
//	// Draw the windows of the house.
//	// Generate vertices clockwise: Polygon faces backward.
//	glBegin(GL_POLYGON);
//	glVertex2i(225, 375);
//	glVertex2i(225, 475);
//	glVertex2i(325, 475);
//	glVertex2i(325, 375);
//	glEnd();
//	// Generate vertices counter-clockwise: Polygon faces forward.
//	glBegin(GL_POLYGON);
//	glVertex2i(375, 375);
//	glVertex2i(475, 375);
//	glVertex2i(475, 475);
//	glVertex2i(375, 475);
//	glEnd();
//
//	glFlush();
//}
//
//void reshape(int w, int h)
//// Callback for processing reshape events.
//{
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, w, 0.0, h);
//}
//
//
//void escExit(GLubyte key, int, int)
//// Callback for processing keyboard events.
//{
//	if (key == 27 /* ESC */) std::exit(0);
//}
//
//
//
//int main()
//{
//	// Mask floating point exceptions.
//	_control87(MCW_EM, MCW_EM);
//
//	// Choose RGB display mode for normal screen window.
//	glutInitDisplayMode(GLUT_RGB);
//
//	// Set initial window size, position, and title.
//	glutInitWindowSize(INITIAL_WIN_W, INITIAL_WIN_H);
//	glutInitWindowPosition(INITIAL_WIN_X, INITIAL_WIN_Y);
//	glutCreateWindow("American Dream House");
//
//	// You don't (yet) want to know what this does.
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, (double)INITIAL_WIN_W, 0.0, (double)INITIAL_WIN_H);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	// This is a hack.
//	glTranslatef(0.375, 0.375, 0.0);
//
//	// Set the color for clearing the normal screen window.
//	glClearColor(1.0, 1.0, 1.0, 0.0);
//
//	// Set the color for drawing the house.
//	glColor3f(0.0, 0.0, 1.0);
//
//	// Set the callbacks for the normal screen window.
//	glutDisplayFunc(drawHouse);
//
//	// Set the callback for reshape events.
//	glutReshapeFunc(reshape);
//
//	// Set the callback for keyboard events.
//	glutKeyboardFunc(escExit);
//
//	// Start the GLUT main loop.
//	glutMainLoop();
//
//}
