#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>
#include "resource.h"

using std::vector;

typedef struct GLUT_CONFIG_FUNCS maingl;
struct GLUT_CONFIG_FUNCS {
	static GLfloat  pointSize, lineWidth, fps, currentTime, vo, vf;
	static GLint ancho, alto;
	static GLclampf Ccolor[4], color[3];
	static unsigned int cckey, ckey;
	static const char* nombre;
	static void inicio();
	static void preDisplay();
	static void display();
	static void idle();
	static void mouse(int, int, int, int);
	static void keyboard(unsigned char, int, int);
	static void cccolorchanger();
	static void ccolorchanger();
};

struct clicks {
	int posx, posy;
	static int key, seekey, itv;
	static void mouse(int, int);
	static void mostrar();
};



int clicks::key = 0;
int clicks::seekey = 0;
int clicks::itv = 0;

vector<GLenum> glenums = { GL_LINE_LOOP,GL_POINTS,GL_POLYGON,GL_TRIANGLES, GL_POLYGON_BIT };



vector<clicks*> poses;

void clicks::mouse(int x, int y) {
	clicks* pos = new clicks;
	pos->posx = x;
	pos->posy = maingl::alto - y;
	poses.push_back(pos);
	key += 1;
}


void clicks::mostrar() {
	glBegin(glenums[itv]);
	for (auto it : poses) { glVertex2d(it->posx, it->posy); }
	glEnd();
}



int main(int argc, char** argv) {

	glutInit(&argc, argv);

	maingl::inicio();
	maingl::preDisplay();

	glutMainLoop();

	return 0;

}



GLint GLUT_CONFIG_FUNCS::ancho = 800;
GLint GLUT_CONFIG_FUNCS::alto = 600;
GLfloat GLUT_CONFIG_FUNCS::pointSize = 10;
GLfloat GLUT_CONFIG_FUNCS::lineWidth = 6;
GLfloat GLUT_CONFIG_FUNCS::fps = 60;
GLfloat GLUT_CONFIG_FUNCS::currentTime = 0;
GLfloat GLUT_CONFIG_FUNCS::vo = 0;
GLfloat GLUT_CONFIG_FUNCS::vf = 0;
const char* GLUT_CONFIG_FUNCS::nombre = "controles  1=color fondo  2=color linea   E=cambio de estado   R=retroceder   T=borrar  click=punto de anclaje";
int unsigned GLUT_CONFIG_FUNCS::cckey = 0;
int unsigned GLUT_CONFIG_FUNCS::ckey = 0;
GLclampf GLUT_CONFIG_FUNCS::Ccolor[] = { 0.3,0.4,0.8,0.6 };
void GLUT_CONFIG_FUNCS::display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (!poses.empty()) { clicks::mostrar(); }
	glutSwapBuffers();
}
void GLUT_CONFIG_FUNCS::mouse(int boton, int estado, int posx, int posy) {
	if ((estado == GLUT_LEFT_BUTTON) && (boton == GLUT_DOWN)) { clicks::mouse(posx, posy); }
}
void GLUT_CONFIG_FUNCS::keyboard(unsigned char key, int x, int y) {

	switch (key)
	{
	case '1':
		cccolorchanger();
		break;
	case '2':
		ccolorchanger();
		break;
	case 'e':

		clicks::itv += 1;
		if (clicks::itv >= glenums.size()) { clicks::itv = 0; }

		break;
	case 'E':
		clicks::itv += 1;
		if (clicks::itv >= glenums.size()) { clicks::itv = 0; }

		break;
	case 't':

		poses.clear();

		break;
	case 'T':

		poses.clear();

		break;
	case 'r':

		if (!poses.empty()) { poses.pop_back(); }

		break;
	case 'R':

		if (!poses.empty()) { poses.pop_back(); }

		break;
	}
}
void GLUT_CONFIG_FUNCS::idle() {

	if ((GLUT_ELAPSED_TIME - (currentTime + fps) > 0)) {
		glutPostRedisplay();
	}
}
void GLUT_CONFIG_FUNCS::inicio() {

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(ancho, alto);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(nombre);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
}
void GLUT_CONFIG_FUNCS::preDisplay() {

	glClearColor(Ccolor[0], Ccolor[1], Ccolor[2], Ccolor[3]);
	glOrtho(0, ancho, 0, alto, -1, 1);
	glPointSize(pointSize);
	glLineWidth(lineWidth);

}

void GLUT_CONFIG_FUNCS::cccolorchanger() {

	switch (cckey)
	{
	case 0:
		glClearColor(0.2, 0.8, 0.4, 1);
		break;
	case 1:
		glClearColor(0.8, 0.4, 0.4, 1);
		break;
	case 2:
		glClearColor(0.3, 0.4, 0.8, 1);
		break;
	case 3:
		glClearColor(0.3, 0.3, 0.3, 1);
		break;
	case 4:
		glClearColor(0.4, 0.5, 0.6, 1);
		break;
	}

	cckey += 1;
	if (cckey >= 5) {
		cckey = 0;
		cccolorchanger();
	}
}

void GLUT_CONFIG_FUNCS::ccolorchanger() {

	switch (ckey)
	{
	case 0:
		glColor3f(0.0, 1, 0.0);
		break;
	case 1:
		glColor3f(1, 0.0, 0.0);
		break;
	case 2:
		glColor3f(0.0, 1, 1);
		break;
	case 3:
		glColor3f(1, 1, 0.0);
		break;
	case 4:
		glColor3f(1, 1, 1);
		break;
	}

	ckey += 1;
	if (ckey >= 5) {
		ckey = 0;
		ccolorchanger();
	}
}
