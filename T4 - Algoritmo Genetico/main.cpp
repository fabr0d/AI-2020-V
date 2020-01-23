#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <algorithm>    // std::random_shuffle
#include <math.h>
#include "GL/glut.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#define KEY_ESC 27
using namespace std;

class Point
{
public:
	float x;
	float y;
	bool visited;
	Point()
	{
		x = 0;
		y = 0;
		visited = false;
	}
	Point(float x_, float y_)
	{
		x = x_;
		y = y_;
		visited = false;
	}
};

float Euclidean_distance(Point* P, Point* N)
{
	return sqrt(pow(abs(N->x - P->x), 2) + pow(abs(N->y - P->y), 2));
}

float Euclidean_distance(Point P, Point N)
{
	return sqrt(pow(abs(N.x - P.x), 2) + pow(abs(N.y - P.y), 2));
}

vector<Point> TSMCountries;
int numberTSMCountries = 0;

void createTSMCountries()
{
	for (int i = 0; i < numberTSMCountries; i++)
	{
		float xtemp = rand() % 101;
		float ytemp = rand() % 101;
		TSMCountries.push_back(Point(xtemp, ytemp));
	}
}

void drawTSMCountries()
{
	for (size_t i = 0; i < numberTSMCountries; i++)
	{
		glPointSize(1);
		glBegin(GL_POINTS);
		glColor3d(250, 0, 0);
		glVertex3f(TSMCountries[i].x, TSMCountries[i].y, 0.0);
		glEnd();
	}
}

vector<Point> TSMcountriesPrincipal;
int munofpnts = 0;
int poblationNumber = 0;

void drawTSMCountriesPrincipal()
{
	for (size_t i = 0; i < munofpnts; i++)
	{
		glPointSize(4);
		glBegin(GL_POINTS);
		glColor3d(1.000, 0.271, 0.000);
		glVertex3f(TSMcountriesPrincipal[i].x, TSMcountriesPrincipal[i].y, 0.0);
		glEnd();
	}
}

bool isInTMScountries(Point ToFind) //busca si ya esta en la lista del TSMcountriesPrincipal
{
	for (size_t i = 0; i < TSMcountriesPrincipal.size(); i++)
	{
		if (ToFind.x == TSMcountriesPrincipal[i].x and ToFind.y == TSMcountriesPrincipal[i].y)
		{
			return true;
		}
	}
	return false;
}

void getTenRandomCountries()
{
	for (int i = 0; i < munofpnts; i++)
	{
		int randomico = rand() % TSMCountries.size();
		if (isInTMScountries(TSMCountries[randomico]) == false)
		{
			TSMcountriesPrincipal.push_back(TSMCountries[randomico]);
		}
		else
		{
			i--;
		}
	}
}

void drawEdgesFromPrincipal()
{
	for (size_t i = 0; i < TSMcountriesPrincipal.size(); i++)
	{
		for (size_t j = 0; j < TSMcountriesPrincipal.size(); j++)
		{
			glBegin(GL_LINES);
			glColor3d(1.000, 1.000, 0.000);
			glVertex3d(TSMcountriesPrincipal[i].x, TSMcountriesPrincipal[i].y, 0);
			glVertex3d(TSMcountriesPrincipal[j].x, TSMcountriesPrincipal[j].y, 0);
			glEnd();
		}
	}
}

float printPath(vector<Point*> Path, Point* A, Point* B)
{
	float answ = 0;
	for (size_t i = 0; i < Path.size(); i++)
	{
		if (i + 1 != Path.size())
		{
			glBegin(GL_LINES);
			glColor3d(1.00000f, 0.20000f, 0.80000f);
			glVertex3d(Path[i]->x, Path[i]->y, 0);
			glVertex3d(Path[i + 1]->x, Path[i + 1]->y, 0);
			glEnd();
			answ = answ + Euclidean_distance(Path[i], Path[i + 1]);
		}
	}
	cout << "Distancia Recorrida: " << answ << endl;
	return answ;
}

void drawPointsFromPath(vector<Point*> Path, Point* A, Point* B)
{
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3d(0.000, 0.980, 0.604);
	glVertex3f(A->x, A->y, 0.0);
	glEnd();
	for (size_t i = 0; i < Path.size(); i++)
	{
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glColor3d(0.000, 0.980, 0.604);
		glVertex3f(Path[i]->x, Path[i]->y, 0.0);
		glEnd();
	}
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3d(0.000, 0.980, 0.604);
	glVertex3f(B->x, B->y, 0.0);
	glEnd();
}

/////////////////////////////////////////////////////////////////////////////////////
vector<vector<Point>> Poblacion;

vector<vector<Point>> genRandomIniciañPoblation()
{
	vector<vector<Point>> anw;
	vector<Point> tempo = TSMcountriesPrincipal;
	for (size_t i = 0; i < poblationNumber; i++)
	{
		random_shuffle(tempo.begin()+1, tempo.end());
		anw.push_back(tempo);
	}
	return anw;
}

float CalculateAptitude(vector<Point> Ruta)
{
	float anw = 0.0;
	for (size_t i = 0; i < Ruta.size() - 1; i++)
	{
		anw = anw + Euclidean_distance(Ruta[i], Ruta[i + 1]);
	}
	anw = anw + Euclidean_distance(Ruta[Ruta.size() - 1], Ruta[0]);
	return anw;
}

vector<vector<Point>> geneticAlgorithm(vector<vector<Point>> P)
{
	Poblacion = genRandomIniciañPoblation();
	vector<pair<int, float>> PositionOfAPoblacion_and_Aptitude;
	for (size_t i = 0; i < Poblacion.size(); i++)
	{
		PositionOfAPoblacion_and_Aptitude.push_back( pair<int,float> ( i , CalculateAptitude(Poblacion[i]) ) );
	}
	float maxval = 0.0;

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

	drawTSMCountries();
	drawEdgesFromPrincipal();
	drawTSMCountriesPrincipal();
	//printPath(, p1, p2);
	//drawPointsFromPath(, p1, p2);

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
GLvoid window_redraw(GLsizei width, GLsizei height) 
{
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
	numberTSMCountries = 200;
	cout << "numero de ciudades: ";
	cin >> munofpnts;

	cout << "numero de caminos en una generacion: ";
	cin >> poblationNumber;

	createTSMCountries();
	getTenRandomCountries();



	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("Genetic Algorithm"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}