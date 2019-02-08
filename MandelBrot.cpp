/*--------------------------------------------------------*/
/*  CS-378           Computer Graphics     Jordan Buhmann */
/*--------------------------------------------------------*/
/*  Assignment 1 - Drawing the MandelBrot Set             */
/*--------------------------------------------------------*/

#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <cfloat>
#include <list>
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
	k.real = real + c.real;
	k.imag = imag + c.imag;
	return k;
}

complex complex::operator *(complex c) {
	complex k;
	k.real = (real*c.real) - (imag*c.imag);
	k.imag = (real*c.imag) + (imag*c.real);
	return k;
}

double complex::abs() {
	return sqrt((real*real) + (imag*imag));
}



// Defining default values for window size, shape and location.
#define INITIAL_WIN_W 700
#define INITIAL_WIN_H 700
#define INITIAL_WIN_X 150
#define INITIAL_WIN_Y 50


// Variables for keeping track of the screen window dimensions.
int windowHeight = INITIAL_WIN_H;
int windowWidth = INITIAL_WIN_W;

double X1 = -1;
double X2 = 1;
double Y1 = -1;
double Y2 = 1;
int** table;


void initTables(int w, int h){
table = new int*[w];
for (int i = 0; i < w; i++) table[i] = new int[h];
}

struct rectangle
{
	double xmin;
	double ymin;
	double xmax;
	double ymax;
	rectangle(double xmn, double ymn, double xmx, double ymx)
		: xmin(xmn), ymin(ymn), xmax(xmx), ymax(ymx)
	{}
};

list<rectangle*> rectList;


void mandelbrot()
{
	int w = INITIAL_WIN_W;
	int h = INITIAL_WIN_H;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS); // start drawing in single pixel mode
	double x1 = X1;
	double x2 = X2;
	double y1 = Y1;
	double y2 = Y2;
	rectList.push_back(new rectangle(x1, y1, x2, y2));
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			// Work out the point in the complex plane that corresponds to this pixel in the output image.
			double xx = x1 + (x * (x2 - x1) / (w - 1));
			double yy = y1 + (y * (y2 - y1) / (h - 1));
			complex c(xx, yy);
			//			cout << "c: " << c.real << " " << c.imag << endl;
						// Start off z at (0, 0).
			complex z(0.0, 0.0);

			// Iterate z = z^2 + c until we've iterated too many times.
			int iterations = 0;
			while (z.abs() < 2 && iterations < 1000)
			{
				z = (z * z) + c;
				//				cout << "Iteration: " << iterations << "z: " << z.real << " " << z.imag << endl;
				iterations++;
			}
			if (iterations == 1000)
			{
				glColor3f(0.0, 0.0, 0.0); // Set color to draw mandelbrot
				// This point is in the Mandelbrot set.
				glVertex2i(x, y);
			}

			else if (iterations > 90) {
				glColor3f(1.0, 1.0, 0.5); //Set pixel to black
										  // iterations. This point isn't in the set.
				glVertex2i(x, y);
			}
			else if (iterations > 75) {
				glColor3f(1.0, 0.0, 0.5); //Set pixel to black
										  // iterations. This point isn't in the set.
				glVertex2i(x, y);
			}

			else if (iterations > 50) {
				glColor3f(1.0, 0.0, 0.0); //Set pixel to black
										  // iterations. This point isn't in the set.
				glVertex2i(x, y);
			}
			else if (iterations > 25) {
				glColor3f(0.0, 0.0, 1.0); //Set pixel to black
										  // iterations. This point isn't in the set.
				glVertex2i(x, y);
			}
			else if (iterations > 1) {
				glColor3f(0.1, 0.1, 0.1); //Set pixel to black
										  // iterations. This point isn't in the set.
				glVertex2i(x, y);
			}
			else {
				glColor3f(0.0, 0.0, 0.0); //Set pixel to black
										  // iterations. This point isn't in the set.
				glVertex2i(x, y);
			}
		}
	}
	cout << "                            done" << endl;
	glEnd();
	glFlush();

}

bool push = false;


void reshape(int w, int h)
// Callback for processing reshape events.
{
	if (h == 0) {
		h == 1;
	}
	float aspectRatio = (float) (w / h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, aspectRatio, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const int width = windowWidth;
	const int height = windowHeight;
	glOrtho(0, width, 0, height, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mandelbrot();
	//glutSwapBuffers();
}


const int width = 700, height = 700; // window size
int xAnchor, yAnchor, xStretch, yStretch;
int windowID;
bool rubberBanding = false;

void escExit(GLubyte key, int, int)
// Callback for processing keyboard events.
{
	if (key == 27 /* ESC */) std::exit(0);
}


void drawLine(int xOld, int yOld, int xNew, int yNew)
// Draw a line from (xOld,yOld) to (xNew,yNew).
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(xOld, yOld);
	glVertex2i(xOld, yNew);
	glVertex2i(xNew, yNew);
	glVertex2i(xNew, yOld);
	glEnd();
	glFlush();
}

void drawRubberBand(int xOld, int yOld, int xNew, int yNew)
{
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_XOR);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xOld, yOld);
	glVertex2i(xOld, yNew);
	glVertex2i(xNew, yNew);
	glVertex2i(xNew, yOld);
	glEnd();
	glDisable(GL_COLOR_LOGIC_OP);
	glFlush();
}

void rubberBand(int x, int y)
// Callback for processing mouse motion.
{
	if (push = true) {


		if (rubberBanding)
		{
			drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);

			y = windowHeight - y;
			xStretch = x;
			yStretch = y;
			drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);
			glFlush();
		}
	}
}

void processLeftDown(int x, int y)
// Function for processing mouse left botton down events.
{
	if (push = true) {

		if (!rubberBanding)
		{
			int xNew = x;
			int yNew = windowHeight - y;
			xAnchor = xNew;
			yAnchor = yNew;
			xStretch = xNew;
			yStretch = yNew;
			drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);
			rubberBanding = true;
		}
	}
}



void processLeftUp(int x, int y)
// Function for processing mouse left botton up events.
{
	if (rubberBanding)
	{
		int xNew, yNew;
		drawRubberBand(xAnchor, yAnchor, xStretch, yStretch);
		rubberBanding = false;
		xNew = x;
		yNew = y;
		xStretch = xNew;
		yStretch = yNew;

		double xd = abs(xStretch - xAnchor);
		double yd = abs(yStretch - yAnchor);
		double ar = yd / xd;
		double aw = windowHeight / windowWidth;

		if (ar > aw) {
			double z = abs(xd - (yd*windowWidth / windowHeight));
			xStretch = xStretch + (z / 2);
			xAnchor = xAnchor - (z / 2);
			ar = yd / xd;
		}

		if (ar < aw) {
			double z = abs(((xd*(windowHeight)) / windowWidth) - yd);
			yStretch = yStretch + (z / 2);
			yAnchor = yAnchor - (z / 2);
			ar = yd / xd;
		}


		
		double zxAnchor = X1 + (xAnchor * (X2 - X1) / (windowWidth - 1));
		double zyAnchor = Y1 + (yAnchor * (Y2 - Y1) / (windowHeight - 1));
		double zxStretch = X1 + (xStretch * (X2 - X1) / (windowWidth - 1));
		double zyStretch = Y1 + (yStretch * (Y2 - Y1) / (windowHeight - 1));
		X1 = zxAnchor;
		Y1 = zyAnchor;
		X2 = zxStretch;
		Y2 = zyStretch;
		
		//Save new point  in stretch
		//convert anchor and stretch into (x1,y1) (x2,y2)
		glutPostRedisplay();
	}
}


void mouse(int button, int state, int x, int y)
// Function for processing mouse events.
{
	if (push = true) {
		if (button == GLUT_LEFT_BUTTON)
			switch (state)
			{
			case GLUT_DOWN: processLeftDown(x, y); break;
			case GLUT_UP: processLeftUp(x, y); break;
			}
	}
}

void clearPicture()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//void push() {
//	if (button == GLUT_LEFT_BUTTON)
//
//}
//



void mainMenu(int item)
// Callback for processing main menu.
{
	switch (item)
	{
	case 1: push = true; break;
	case 2: 
	case 3: std::exit(0);
	}
}
//
//
//
void setMenus()
// Function for creating menus.
{


	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Push", 1);
	glutAddMenuEntry("Exit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
	glutDisplayFunc(display);

	// Set the callback for reshape events.
	glutReshapeFunc(reshape);

	// Set the callback for keyboard events.
	glutKeyboardFunc(escExit);

	glutMouseFunc(mouse);

	glutMotionFunc(rubberBand);
	glutPassiveMotionFunc(rubberBand);
	setMenus();


	// Start the GLUT main loop.
	glutMainLoop();

}






