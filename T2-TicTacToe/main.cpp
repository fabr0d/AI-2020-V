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

bool isValidMove(int pos, vector<int> board) //check in board if can move in a empty box
{
	if (board[pos] != 1 and board[pos] != 2)
	{
		return true;
	}
	return false;
}

class MiniMax
{
public:
	vector<char>internalBoard;
	vector<char>temporalBoard;
	bool isMax = false;
	bool isMin = false;
	bool root = false;
	int deep;// Profundidad actual
	int RValue;// Valor del Nodo
	char CoinValue; //Valor de la Ficha, A = square / B = circle
	vector <MiniMax*> sons;
	MiniMax(int _deep, bool _root, bool _isMin, bool _isMax, vector<char> boardsTest, char _CoinValue)
	{
		isMax = _isMax;
		isMin = _isMin;
		deep = _deep;
		CoinValue = _CoinValue;
		if (_root == true)
		{
			internalBoard = board; //contiene el tablero global
			temporalBoard = board; //aca se probaran los nuevos tableros
			
			if (sons.size() < 1) // caso que ya no haigan mas hijos
			{
				RValue = -9999;
			}
			
		}
		else
		{

		}
	}

	int evaluate() // usa internalBoard
	{
		int Positive = 0;
		int Negative = 0;
		char aux = CoinValue;
		if ((internalBoard[2] == CoinValue or internalBoard[2] == 'C') and 
			(internalBoard[4] == CoinValue or internalBoard[4] == 'C') and
			(internalBoard[6] == CoinValue or internalBoard[6] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[2] != CoinValue and internalBoard[2] != 'C') or internalBoard[2] == 'C') and
			((internalBoard[4] != CoinValue and internalBoard[4] != 'C') or internalBoard[4] == 'C') and
			((internalBoard[6] != CoinValue and internalBoard[6] != 'C') or internalBoard[6] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[0] == CoinValue or internalBoard[0] == 'C') and
			(internalBoard[4] == CoinValue or internalBoard[4] == 'C') and
			(internalBoard[8] == CoinValue or internalBoard[8] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[0] != CoinValue and internalBoard[0] != 'C') or internalBoard[0] == 'C') and
			((internalBoard[4] != CoinValue and internalBoard[4] != 'C') or internalBoard[4] == 'C') and
			((internalBoard[8] != CoinValue and internalBoard[8] != 'C') or internalBoard[8] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[0] == CoinValue or internalBoard[0] == 'C') and
			(internalBoard[1] == CoinValue or internalBoard[1] == 'C') and
			(internalBoard[2] == CoinValue or internalBoard[2] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[0] != CoinValue and internalBoard[0] != 'C') or internalBoard[0] == 'C') and
			((internalBoard[1] != CoinValue and internalBoard[1] != 'C') or internalBoard[1] == 'C') and
			((internalBoard[2] != CoinValue and internalBoard[2] != 'C') or internalBoard[2] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[3] == CoinValue or internalBoard[3] == 'C') and
			(internalBoard[4] == CoinValue or internalBoard[4] == 'C') and
			(internalBoard[5] == CoinValue or internalBoard[5] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[3] != CoinValue and internalBoard[3] != 'C') or internalBoard[3] == 'C') and
			((internalBoard[4] != CoinValue and internalBoard[4] != 'C') or internalBoard[4] == 'C') and
			((internalBoard[5] != CoinValue and internalBoard[5] != 'C') or internalBoard[5] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[6] == CoinValue or internalBoard[6] == 'C') and
			(internalBoard[7] == CoinValue or internalBoard[7] == 'C') and
			(internalBoard[8] == CoinValue or internalBoard[8] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[6] != CoinValue and internalBoard[6] != 'C') or internalBoard[6] == 'C') and
			((internalBoard[7] != CoinValue and internalBoard[7] != 'C') or internalBoard[7] == 'C') and
			((internalBoard[8] != CoinValue and internalBoard[8] != 'C') or internalBoard[8] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[0] == CoinValue or internalBoard[0] == 'C') and
			(internalBoard[3] == CoinValue or internalBoard[3] == 'C') and
			(internalBoard[6] == CoinValue or internalBoard[6] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[0] != CoinValue and internalBoard[0] != 'C') or internalBoard[0] == 'C') and
			((internalBoard[3] != CoinValue and internalBoard[3] != 'C') or internalBoard[3] == 'C') and
			((internalBoard[6] != CoinValue and internalBoard[6] != 'C') or internalBoard[6] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[1] == CoinValue or internalBoard[1] == 'C') and
			(internalBoard[4] == CoinValue or internalBoard[4] == 'C') and
			(internalBoard[7] == CoinValue or internalBoard[7] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[1] != CoinValue and internalBoard[1] != 'C') or internalBoard[1] == 'C') and
			((internalBoard[4] != CoinValue and internalBoard[4] != 'C') or internalBoard[4] == 'C') and
			((internalBoard[7] != CoinValue and internalBoard[7] != 'C') or internalBoard[7] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[2] == CoinValue or internalBoard[2] == 'C') and
			(internalBoard[5] == CoinValue or internalBoard[5] == 'C') and
			(internalBoard[8] == CoinValue or internalBoard[8] == 'C'))
		{
			Positive++;
		}
		else if (((internalBoard[2] != CoinValue and internalBoard[2] != 'C') or internalBoard[2] == 'C') and
			((internalBoard[5] != CoinValue and internalBoard[5] != 'C') or internalBoard[5] == 'C') and
			((internalBoard[8] != CoinValue and internalBoard[8] != 'C') or internalBoard[8] == 'C'))
		{
			Negative++;
		}

		return Positive-Negative;
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