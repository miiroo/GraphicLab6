#include<Windows.h>
#include <GL/glut.h> 
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
struct Point
{
	float x, y, z;
};

struct Color { float r, g, b; };

vector<Point> v1;
vector<vector<int>> faces1;

int point_count1, face_count1;

vector<Point> v2;
vector<vector<int>> faces2;
vector<Color>color1;


int point_count2, face_count2;

void reshape(int w, int h);
void display();
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

void init(void) {
//	GLfloat mat_specular[] = { 1.0, 1, 1, 1 };
//	GLfloat mat_shininess[] = { 70.0 };
	GLfloat light_position[] = { 5.0, 5.0, 5.0, 1 };
	GLfloat white_light[] = { 1.0, 0.0, 0.0, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
//	glColorMaterial(GL_FRONT, GL_DIFFUSE);
//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
}


void readfromfile(string path, vector<Point> * v, vector<vector<int>> *faces, vector<Color> *color, int * point_count, int * face_count)
{
	float x, y, z;
	Point p;
	ifstream f(path, ios::in);
	f >> (*point_count);
	for (int i = 0; i < (*point_count); i++)
	{
		f >> p.x >> p.y >> p.z;
		(*v).push_back(p);
	}
	f >> (*face_count);
	(*faces).resize((*face_count));
	(*color).resize((*face_count));

	for (int i = 0; i < (*face_count); i++)
	{
		float r, g, b;
		f >> (*color)[i].r >> (*color)[i].g >> (*color)[i].b;

		for (int j = 0; j < 4; j++)
		{
			int p;
			f >> p;
			(*faces)[i].push_back(p);
		}
	}
	f.close();
}

int main(int argc, char * argv[])
{
	readfromfile("a.txt", &v1, &faces1, &color1, &point_count1, &face_count1);
	//readfromfile("s.txt", &v2, &faces2, &point_count2, &face_count2);

	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL lesson 7");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();

	return 0;
}

void reshape(int w, int h)
{

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
//	gluPerspective(50, 1, 1, 30);
//	gluLookAt(5, 5, 20, 5, 5, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void display()
{
	//glDisable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	for (int i = 0; i < face_count1; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(color1[i].r, color1[i].g, color1[i].b);
		for (int j = 0; j < faces1[i].size(); j++)
		{
			glVertex3f(v1[faces1[i][j]].x, v1[faces1[i][j]].y, v1[faces1[i][j]].z);
		}


		glEnd();
	}
	/*
	for (int i = 0; i < face_count2; i++)
	{
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < faces2[i].size(); j++)
		{
			glVertex3f(v2[faces2[i][j]].x, v2[faces2[i][j]].y, v2[faces2[i][j]].z);
		}


		glEnd();
	}
	*/

	

	glutSwapBuffers();
	glDisable(GL_CULL_FACE);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if ((key == '=') || (key == '+')) {
		glMatrixMode(GL_MODELVIEW);
		glScaled(1.2, 1.2, 1.2);
		display();
	}
	if ((key == '-') || (key == '_')) {
		glMatrixMode(GL_MODELVIEW);
		glScaled(0.8, 0.8, 0.8);
		display();
	}
	if (key == 127) {
		glMatrixMode(GL_MODELVIEW);
		glRotated(5, 0, 0, 1);
		display();
	}
	if (key == '1') {
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		display();
	}
	if (key == '2') {
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		display();
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0, 1, 0);
		display();
		break;
	case GLUT_KEY_DOWN:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0, -1, 0);
		display();
		break;
	case GLUT_KEY_LEFT:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(-1, 0, 0);
		display();
		break;
	case GLUT_KEY_RIGHT:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(1, 0, 0);
		display();
		break;
	case GLUT_KEY_HOME:
		glMatrixMode(GL_MODELVIEW);
		glRotated(5, 1, 0, 0);
		display();
		break;
	case GLUT_KEY_END:
		glMatrixMode(GL_MODELVIEW);
		glRotated(5, 0, 1, 0);
		display();
		break;
	case GLUT_KEY_PAGE_UP:
		glMatrixMode(GL_MODELVIEW);
		glRotated(-5, 1, 1, 1);
		display();
		break;
	case GLUT_KEY_PAGE_DOWN:
		glMatrixMode(GL_MODELVIEW);
		glRotated(5, 1, 1, 1);
		display();
		break;
	}
}