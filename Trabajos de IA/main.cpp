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

class Point;
class Edge 
{
public:
	Edge(Point* a, Point* b) {
		VertexA = a;
		VertexB = b;
	};
	Point* VertexA;
	Point* VertexB;
};
class Point 
{
public:
	vector<Edge*>Edges;
	float x;
	float y;
	bool visited;
	bool added;
	float cost;
	Point()
	{
		x = 0;
		y = 0;
		visited = false;
		added = false;
	}
	Point(float x_, float y_)
	{
		x = x_;
		y = y_;
		visited = false;
		added = false;
	}
	Point operator =  (const Point& P) 
	{
		this->x = P.x;
		this->y = P.y;
		return *this;
	}
	bool operator ==  (const Point& P) {
		if (this->x == P.x && this->y == P.y) {
			return true;
		}
		return false;

	}
};

vector<Point> Puntos;
int numberPointsT = 0;

void createPoints()
{
	for (int i = 0; i < numberPointsT; i++)
	{
		float xtemp = rand() % 101;
		float ytemp = rand() % 101;
		Puntos.push_back(Point(xtemp, ytemp));
	}
}

void drawPoints()
{
	for (size_t i = 0; i < numberPointsT; i++)
	{
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glColor3d(250, 0, 0);
		glVertex3f(Puntos[i].x, Puntos[i].y, 0.0);
		glEnd();
	}
}

float Euclidean_distance(Point deltaX, Point deltaY)
{
	return sqrt(pow((deltaX.x-deltaY.x),2) + pow((deltaX.y - deltaY.y), 2));
}

vector<Edge*> EdgesGlob;

void getEdgesKNN()
{
	float minDist = 10;
	for (size_t i = 0; i < Puntos.size(); i++)
	{
		while (Puntos[i].Edges.size() < 5)
		{
			for (size_t j = 0; j < Puntos.size(); j++)
			{
				float ED = Euclidean_distance(Puntos[i], Puntos[j]);
				if (ED < minDist && ED != 0 && Puntos[i].Edges.size() < 5 && Puntos[j].Edges.size() < 5)
				{
					bool exist = false;

					Edge* nuevo1 = new Edge(&Puntos[i], &Puntos[j]);
					Edge* nuevo2 = new Edge(&Puntos[j], &Puntos[i]);
					
					Puntos[i].Edges.push_back(nuevo1);
					Puntos[j].Edges.push_back(nuevo2);
					EdgesGlob.push_back(nuevo1);
					EdgesGlob.push_back(nuevo2);
				}
			}
			if (Puntos[i].Edges.size() < 5)
			{
				cout << "test" << endl;
				minDist = minDist + 5;
			}
		}
	}
}

void drawEDGES()
{
	for (size_t i = 0; i < EdgesGlob.size(); i++)
	{
		glBegin(GL_LINES);
		glColor3d(0.20000f, 0.80000f, 1.00000f);
		glVertex3d(EdgesGlob[i]->VertexA->x, EdgesGlob[i]->VertexA->y, 0);
		glVertex3d(EdgesGlob[i]->VertexB->x, EdgesGlob[i]->VertexB->y, 0);
		glEnd();
	}
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

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();

	drawEDGES();
	drawPoints();

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
//
//el programa principal
//
int main(int argc, char** argv) {
	numberPointsT = 200;
	createPoints();
	getEdgesKNN();

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("YY EY"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}