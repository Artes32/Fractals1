#include <iostream>
#include <glut.h>

using namespace std;

void Initialization();
void Screen();
void Revolve();
void Change(int wi, int he);
void DividePyramid(GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t, GLfloat *e, int stage);
void DrawPyramid(GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t, GLfloat *e);
void DrawTriangle(GLfloat *p, GLfloat *r, GLfloat *s);
void DrawQuoad(GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t);
void DrawLineTriangle(GLfloat *a, GLfloat *b, GLfloat *c);
void DrawLineQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void Keyboard(unsigned char letter, int a, int b);
bool shading = false;
float red = 1.0;
float green = 0.0;
float blue = 0.0;
float red1 = 0.0;
float green1 = 0.0;
float blue1 = 0.8;
float red2 = 1.0;
float green2 = 0.64;
float blue2 = 0.0;
GLfloat polx = 0.0;
GLfloat poly = 0.0;
GLfloat polz = -4.0;
int stage = 3;
GLfloat turn = 44.95;
GLfloat pyramid[5][3] =
{
	{ -1.0, -1.0, 1.0 },
	{ 1.0, -1.0, 1.0 },
	{ 1.0, -1.0, -1.0 },
	{ -1.0, -1.0, -1.0 },
	{ 0.0, 1.0, 0.0 }
};

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 680);
	glutCreateWindow("Пирамида Серпинского");
	Initialization();
	glutDisplayFunc(Screen);
	glutReshapeFunc(Change);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Revolve);
	glutMainLoop();

	return 0;
}

void Initialization()
{
	glClearColor(0.01, 0.01, 0.01, 1.0);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Screen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(polx, poly, polz);
	glRotatef(turn, 0, 1, 0);
	DividePyramid(pyramid[0], pyramid[1], pyramid[2], pyramid[3], pyramid[4], stage);
	glutPostRedisplay();
	glutSwapBuffers();
}
void Change(int wi, int he)
{
	glViewport(0, 0, wi, he);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)wi / (GLdouble)he, 0.1, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void DividePyramid(GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t, GLfloat *e, int stage)
{
	GLfloat pr[3], rs[3], ps[3], pt[3], st[3], re[3], pe[3], se[3], te[3];
	if (stage == 0)
	{
		DrawPyramid(p, r, s, t, e);
	}
	else
	{
		for (int j = 0; j < 3; j++)
		{
			pr[j] = (p[j] + r[j]) / 2.0; 
			rs[j] = (r[j] + s[j]) / 2.0;
			ps[j] = (p[j] + s[j]) / 2.0; 
			pt[j] = (p[j] + t[j]) / 2.0; 
			st[j] = (s[j] + t[j]) / 2.0;
			re[j] = (r[j] + e[j]) / 2.0; 
			pe[j] = (p[j] + e[j]) / 2.0;
			se[j] = (s[j] + e[j]) / 2.0; 
			te[j] = (t[j] + e[j]) / 2.0;
		}

		DividePyramid(p, pr, ps, pt, pe, stage - 1);
		DividePyramid(pr, r, rs, ps, re, stage - 1);
		DividePyramid(ps, rs, s, st, se, stage - 1);
		DividePyramid(pt, ps, st, t, te, stage - 1);
		DividePyramid(pe, re, se, te, e, stage - 1);
	}
}
void DrawPyramid(GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t, GLfloat *e)
{
	if (!shading)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(red1, green1, blue1);
		DrawTriangle(p, e, r);
		glColor3f(red2, green2, blue2);
		DrawTriangle(r, e, s);
		glColor3f(red, green, blue);
		DrawTriangle(s, e, t);
		glColor3f(red2, green2, blue2);
		DrawTriangle(t, e, p);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0, 0.64, 0.0);
		DrawQuoad(p, r, s, t);
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
		glColor3f(0.25, 0.41, 0.88);
		DrawLineTriangle(p, r, e);
		DrawLineTriangle(s, t, e);
		DrawLineQuoad(p, r, s, t);
		glEnd();
	}
}
void DrawTriangle(GLfloat *p, GLfloat *r, GLfloat *s)
{
	glVertex3fv(p);
	glVertex3fv(r);
	glVertex3fv(s);
}
void DrawQuoad(GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t)
{
	glVertex3fv(p);
	glVertex3fv(r);
	glVertex3fv(s);
	glVertex3fv(t);
}
void DrawLineTriangle(GLfloat *p, GLfloat *r, GLfloat *e)
{
	glVertex3fv(p);
	glVertex3fv(r);
	glVertex3fv(r);
	glVertex3fv(e);
	glVertex3fv(p);
	glVertex3fv(e);
}
void DrawLineQuoad(GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t)
{
	glVertex3fv(p);
	glVertex3fv(r);
	glVertex3fv(r);
	glVertex3fv(s);
	glVertex3fv(s);
	glVertex3fv(t);
	glVertex3fv(t);
	glVertex3fv(p);

}
void Revolve()
{
	turn += 0.05;
	if (turn > 360) turn = 0;
}
void Keyboard(unsigned char letter, int a, int b) {
	switch (letter)
	{
	case '+':
		if (stage < 7) stage += 1;
		Screen();
		break;
	case '-':
		if (stage > 0) stage -= 1;
		Screen();
		break;
	case '*':
		shading = !shading;
		Screen();
		break;
	case 'q':
		red = 1.0;
		green = 0.0;
		blue = 0.0; 
		red1 = 0.0;
		green1 = 0.0;
		blue1 = 0.8;
		red2 = 1.0;
		green2 = 0.64;
		blue2 = 0.0;
		break;
	case 'w':
		red2 = 1.0;
		green2 = 0.0;
		blue2 = 0.0;
		red = 0.0;
		green = 0.0;
		blue = 0.8;
		red1 = 1.0;
		green1 = 0.64;
		blue1 = 0.0;
		break;
	case 'e':
		red1 = 1.0;
		green1 = 0.0;
		blue1 = 0.0;
		red2 = 0.0;
		green2 = 0.0;
		blue2 = 0.8;
		red = 1.0;
		green = 0.64;
		blue = 0.0;
		break;
	case '4':
		polx -= 0.1;
		break;
	case '6':
	    polx += 0.1;
		break;
	case '8':
		poly += 0.1;
		break;
	case '2':
		poly -= 0.1;
		break;
	case '5':
		polz += 0.1;
		break;
	case '0':
		polz -= 0.1;
		break;
	}
}