#include <iostream>
#include <glut.h>

using namespace std;

// прототипы функций
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

// угол для поворота
GLfloat angle = 45;
// количество уровней
int level = 1;
// закрашиваем или рисуем только ребра: false-закрашиваем, true- только ребра(клавиша P)
bool state = false;
// задаем пирамиду
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
	// инициализируем графику
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// создаем окно
	glutInitWindowSize(700, 700);
	glutCreateWindow("Serpinski Pyramid");

	MyInit();
	// регистрация обратных вызовов
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Rotate);

	glutMainLoop();

	return 0;
}

void MyInit()
{
	// делаем черный фон
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// разрешить тест глубины
	glEnable(GL_DEPTH_TEST);
	// Улучшение в вычислении перспективы
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Выбор матрицы вида модели
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// сдвинулись вглубь экрана на 4
	glTranslatef(0.0, 0.0, -4.0);
	// вращать будем по оси Y
	glRotatef(angle, 0, 1, 0);
	// делим пирамиду если level > 0 и отрисовываем
	DividePyramid(pyramid[0], pyramid[1], pyramid[2], pyramid[3], pyramid[4], level);
	//Делаем сигнал на перерисовку, ибо постоянно меняем угол поворота
	glutPostRedisplay();
	glutSwapBuffers();
}
void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	// загружаем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	//  Сброс матрицы проекции
	glLoadIdentity();
	// Вычисление соотношения геометрических размеров для окна
	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1, 200.0);
	// Выбор матрицы вида модели
	glMatrixMode(GL_MODELVIEW);
	// Сброс матрицы вида модели
	glLoadIdentity();
}

void DividePyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *s, int level)
{
	// координаты для середин ребер
	GLfloat ab[3], bc[3], ac[3], ad[3], cd[3], bs[3], as[3], cs[3], ds[3];
	if (level == 0)
	{
		DrawPyramid(a, b, c, d, s);
	}
	else
	{
		for (int j = 0; j < 3; j++)
		{
			ab[j] = (a[j] + b[j]) / 2.0; // середина A и B
			bc[j] = (b[j] + c[j]) / 2.0; // середина B и C
			ac[j] = (a[j] + c[j]) / 2.0; // середина A и C (центр квадрата-основания)
			ad[j] = (a[j] + d[j]) / 2.0; // середина A и D
			cd[j] = (c[j] + d[j]) / 2.0; // середина C и D
			bs[j] = (b[j] + s[j]) / 2.0; // середина B и S
			as[j] = (a[j] + s[j]) / 2.0; // середина A и S
			cs[j] = (c[j] + s[j]) / 2.0; // середина C и S
			ds[j] = (d[j] + s[j]) / 2.0; // середина D и S
		}

		// рекурсивно вызываем для 5 меньших пирамидок
		DividePyramid(a, ab, ac, ad, as, level - 1);
		DividePyramid(ab, b, bc, ac, bs, level - 1);
		DividePyramid(ac, bc, c, cd, cs, level - 1);
		DividePyramid(ad, ac, cd, d, ds, level - 1);
		DividePyramid(as, bs, cs, ds, s, level - 1);
	}
}
void DrawPyramid(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *s)
{
	// рисуем закрашенную
	if (!state)
	{
		glBegin(GL_TRIANGLES);
		// красим в фиолетовый цвет
		glColor3f(0.52, 0.44, 1.0);
		DrawTriangle(a, b, s);
		// красим в желтый цвет
		glColor3f(1.0, 0.84, 0.0);
		DrawTriangle(b, c, s);
		// красим в фиолетовый цвет
		glColor3f(0.52, 0.44, 1.0);
		DrawTriangle(c, d, s);
		// красим в желтый цвет
		glColor3f(1.0, 0.84, 0.0);
		DrawTriangle(a, d, s);
		glEnd();

		glBegin(GL_QUADS);
		// красим в желтый цвет
		glColor3f(1.0, 0.84, 0.0);
		DrawQuoad(a, b, c, d);
		glEnd();
	}
	// или отрисовываем только ребра
	else
	{
		glBegin(GL_LINES);
		// красим в синий цвет
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