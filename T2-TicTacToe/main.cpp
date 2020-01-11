#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include "GL/glut.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <queue>
#include <stack>
#include <math.h>
#define KEY_ESC 27

using namespace std;

vector<char> board;

class MiniMax
{
public:
	vector<char>internalBoard;
	bool isMax = false;
	bool isMin = false;
	//bool root = false;
	int deep;
	int RValue;
	MiniMax(){}

	int evaluate()
	{

	}
};


void create_Square(double centerX, double centerY, double longitude)
{
	glBegin(GL_LINE_LOOP);
	glColor3d(0.000, 1.000, 1.000);
	glVertex2f(centerX - (longitude / 2), centerY + (longitude / 2));
	glVertex2f(centerX + (longitude / 2), centerY + (longitude / 2));
	glVertex2f(centerX + (longitude / 2), centerY - (longitude / 2));
	glVertex2f(centerX - (longitude / 2), centerY - (longitude / 2));
	glVertex2f(centerX - (longitude / 2), centerY + (longitude / 2));
	glEnd();
}

void create_circle(double centerX, double centerY, double radius) {
	glBegin(GL_LINE_LOOP);
	glColor3d(0.855, 0.439, 0.839);
	for (int i = 0; i < 100; i++)
	{
		double theta = 2.0 * 3.1415926 * double(i) / 100.0;
		double x = radius * cosf(theta);
		double y = radius * sinf(theta);
		glVertex2f(x + centerX, y + centerY);
	}
	glEnd();
}

//pos1 = 30,70
//pos2 = 50,70
//pos3 = 70,70
//pos4 = 30,50
//pos5 = 50,50
//pos6 = 70,50
//pos7 = 30,30
//pos8 = 50,30
//pos9 = 70,30

void printBoard()
{
	glBegin(GL_LINES);

	glColor3d(1, 1, 1);
	glVertex3d(20, 40, 0);
	glVertex3d(80, 40, 0);

	glColor3d(1, 1, 1);
	glVertex3d(20, 60, 0);
	glVertex3d(80, 60, 0);

	glColor3d(1, 1, 1);
	glVertex3d(40, 20, 0);
	glVertex3d(40, 80, 0);

	glColor3d(1, 1, 1);
	glVertex3d(60, 20, 0);
	glVertex3d(60, 80, 0);

	glEnd();
}

void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255, 0, 0);//x
	glVertex3d(0, 0, 0);
	glVertex3d(100, 0, 0);
	glColor3d(0, 255, 0);//y
	glVertex3d(0, 0, 0);
	glVertex3d(0, 100, 0);
	glColor3d(0, 0, 255);//z
	glVertex3d(0, 0, -30);
	glVertex3d(0, 0, 30);
	glEnd();
}
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();

	printBoard();
	create_Square(30, 30, 10);
	//dibuja el gizmo
	displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-20.0, 120.0, -20.0, 120.0, -1.0, 1.0);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
int main(int argc, char** argv) {
	

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("SKYNET"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}