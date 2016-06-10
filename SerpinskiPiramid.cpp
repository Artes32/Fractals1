#include <iostream>
#include <glut.h>

using namespace std;

// ïðîòîòèïû ôóíêöèé
void MyInit();
void Display();
void Rotate();
void Reshape(int w, int h);
void DividePyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *s, int level);
void DrawPyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *s);
void DrawTriangle(GLfloat *a, GLfloat *b, GLfloat *c);
void DrawQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void DrawLineTriangle(GLfloat *a, GLfloat *b, GLfloat *c);
void DrawLineQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void Keyboard(unsigned char key, int x, int y);

// óãîë äëÿ ïîâîðîòà
GLfloat angle = 45;
// êîëè÷åñòâî óðîâíåé
int level = 1;
// çàêðàøèâàåì èëè ðèñóåì òîëüêî ðåáðà: false-çàêðàøèâàåì, true- òîëüêî ðåáðà(êëàâèøà P)
bool state = false;
// çàäàåì ïèðàìèäó
GLfloat pyramid[5][3] =
{
	{ -1.0, -1.0, 1.0 }, // A
	{ 1.0, -1.0, 1.0 }, // B
	{ 1.0, -1.0, -1.0 }, // C
	{ -1.0, -1.0, -1.0 }, // D
	{ 0.0, 1.0, 0.0 }  // S
};

int main(int argc, char **argv)
{
	// èíèöèàëèçèðóåì ãðàôèêó
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// ñîçäàåì îêíî
	glutInitWindowSize(700, 700);
	glutCreateWindow("Serpinski Pyramid");

	MyInit();
	// ðåãèñòðàöèÿ îáðàòíûõ âûçîâîâ
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Rotate);

	glutMainLoop();

	return 0;
}

void MyInit()
{
	// äåëàåì ÷åðíûé ôîí
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// ðàçðåøèòü òåñò ãëóáèíû
	glEnable(GL_DEPTH_TEST);
	// Óëó÷øåíèå â âû÷èñëåíèè ïåðñïåêòèâû
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Âûáîð ìàòðèöû âèäà ìîäåëè
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// ñäâèíóëèñü âãëóáü ýêðàíà íà 4
	glTranslatef(0.0, 0.0, -4.0);
	// âðàùàòü áóäåì ïî îñè Y
	glRotatef(angle, 0, 1, 0);
	// äåëèì ïèðàìèäó åñëè level > 0 è îòðèñîâûâàåì
	DividePyramid(pyramid[0], pyramid[1], pyramid[2], pyramid[3], pyramid[4], level);
	//Äåëàåì ñèãíàë íà ïåðåðèñîâêó, èáî ïîñòîÿííî ìåíÿåì óãîë ïîâîðîòà
	glutPostRedisplay();
	glutSwapBuffers();
}
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	// çàãðóæàåì ìàòðèöó ïðîåêöèè
	glMatrixMode(GL_PROJECTION);
	//  Ñáðîñ ìàòðèöû ïðîåêöèè
	glLoadIdentity();
	// Âû÷èñëåíèå ñîîòíîøåíèÿ ãåîìåòðè÷åñêèõ ðàçìåðîâ äëÿ îêíà
	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1, 200.0);
	// Âûáîð ìàòðèöû âèäà ìîäåëè
	glMatrixMode(GL_MODELVIEW);
	// Ñáðîñ ìàòðèöû âèäà ìîäåëè
	glLoadIdentity();
}

void DividePyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *s, int level)
{
	// êîîðäèíàòû äëÿ ñåðåäèí ðåáåð
	GLfloat ab[3], bc[3], ac[3], ad[3], cd[3], bs[3], as[3], cs[3], ds[3];
	if (level == 0)
	{
		DrawPyramid(a, b, c, d, s);
	}
	else
	{
		for (int j = 0; j < 3; j++)
		{
			ab[j] = (a[j] + b[j]) / 2.0; // ñåðåäèíà A è B
			bc[j] = (b[j] + c[j]) / 2.0; // ñåðåäèíà B è C
			ac[j] = (a[j] + c[j]) / 2.0; // ñåðåäèíà A è C (öåíòð êâàäðàòà-îñíîâàíèÿ)
			ad[j] = (a[j] + d[j]) / 2.0; // ñåðåäèíà A è D
			cd[j] = (c[j] + d[j]) / 2.0; // ñåðåäèíà C è D
			bs[j] = (b[j] + s[j]) / 2.0; // ñåðåäèíà B è S
			as[j] = (a[j] + s[j]) / 2.0; // ñåðåäèíà A è S
			cs[j] = (c[j] + s[j]) / 2.0; // ñåðåäèíà C è S
			ds[j] = (d[j] + s[j]) / 2.0; // ñåðåäèíà D è S
		}

		// ðåêóðñèâíî âûçûâàåì äëÿ 5 ìåíüøèõ ïèðàìèäîê
		DividePyramid(a, ab, ac, ad, as, level - 1);
		DividePyramid(ab, b, bc, ac, bs, level - 1);
		DividePyramid(ac, bc, c, cd, cs, level - 1);
		DividePyramid(ad, ac, cd, d, ds, level - 1);
		DividePyramid(as, bs, cs, ds, s, level - 1);
	}
}
void DrawPyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *s)
{
	// ðèñóåì çàêðàøåííóþ
	if (!state)
	{
		glBegin(GL_TRIANGLES);
		// êðàñèì â ôèîëåòîâûé öâåò
		glColor3f(0.52, 0.44, 1.0);
		DrawTriangle(a, b, s);
		// êðàñèì â æåëòûé öâåò
		glColor3f(1.0, 0.84, 0.0);
		DrawTriangle(b, c, s);
		// êðàñèì â ôèîëåòîâûé öâåò
		glColor3f(0.52, 0.44, 1.0);
		DrawTriangle(c, d, s);
		// êðàñèì â æåëòûé öâåò
		glColor3f(1.0, 0.84, 0.0);
		DrawTriangle(a, d, s);
		glEnd();

		glBegin(GL_QUADS);
		// êðàñèì â æåëòûé öâåò
		glColor3f(1.0, 0.84, 0.0);
		DrawQuoad(a, b, c, d);
		glEnd();
	}
	// èëè îòðèñîâûâàåì òîëüêî ðåáðà
	else
	{
		glBegin(GL_LINES);
		// êðàñèì â ñèíèé öâåò
		glColor3f(0.0, 0.0, 1.0);
		DrawLineTriangle(a, b, s);
		DrawLineTriangle(c, d, s);
		DrawLineQuoad(a, b, c, d);
		glEnd();
	}
}
void DrawTriangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}
void DrawQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
}
void DrawLineTriangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(a);
	glVertex3fv(c);
}
void DrawLineQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(c);
	glVertex3fv(d);
	glVertex3fv(a);
	glVertex3fv(d);

}
void Rotate()
{
	angle += 0.05;
	if (angle > 360) angle = 0;
}
void Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case '+':
		if (level < 10) level += 1;
		Display();
		break;
	case '-':
		if (level > 0) level -= 1;
		Display();
		break;
	case 'p':
		state = !state;
		Display();
		break;
	}
}
