#include <iostream>
#include <glut.h>

using namespace std;

void Initialization();
void Screen();
void Revolve();
void Change(int wi, int he);
void DivideSponge(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t, int stage);
void DrawSponge(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t);
void DrawQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void DrawLineQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);
void Keyboard(unsigned char letter, int a, int b);
bool shading = false;
int stage = 3;
int color = 0;
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
GLfloat polz = -6.5;
GLfloat turn = 44.95;
GLfloat sponge[8][3] =
{
	{ -1.5, -1.5, -1.5 }, //A
	{ 1.5, -1.5, -1.5 }, //B
	{ 1.5, -1.5, 1.5 }, //C
	{ -1.5, -1.5, 1.5 }, //D
	{ -1.5, 1.5, -1.5 }, //P
	{ 1.5, 1.5, -1.5 }, //R
	{ 1.5, 1.5, 1.5 }, //S
	{ -1.5, 1.5, 1.5 }, //T
};

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 680);
	glutCreateWindow("Губка Менгера");
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
	glRotatef(turn, 1, 1, 0);
	DivideSponge(sponge[0], sponge[1], sponge[2], sponge[3], sponge[4], sponge[5], sponge[6], sponge[7], stage);
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

void DivideSponge(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t, int stage)
{
	GLfloat lambda1;
	GLfloat lambda2;

	// переменные для первого пласта куба: 
	GLfloat ab[3];
	GLfloat bc[3];
	GLfloat cd[3];
	GLfloat da[3];

	GLfloat ba[3];
	GLfloat cb[3];
	GLfloat dc[3];
	GLfloat ad[3];
    
	GLfloat ac[3];
	GLfloat bd[3];
	GLfloat ca[3];
	GLfloat db[3];

	// переменные для второго пласта куба:
	GLfloat dt[3];
	GLfloat ap[3];
	GLfloat br[3];
	GLfloat cs[3];

	GLfloat ds[3];
	GLfloat cr[3];
	GLfloat bp[3];
	GLfloat at[3];

	GLfloat ct[3];
	GLfloat bs[3];
	GLfloat ar[3];
	GLfloat dp[3];

	GLfloat apcs[3];
	GLfloat brdt[3];
	GLfloat csap[3];
	GLfloat dtbr[3];

	// переменные для третьего пласта куба: 
	GLfloat td[3];
	GLfloat pa[3];
	GLfloat rb[3];
	GLfloat sc[3];

	GLfloat sd[3];
	GLfloat rc[3];
	GLfloat pb[3];
	GLfloat ta[3];

	GLfloat tc[3];
	GLfloat sb[3];
	GLfloat ra[3];
	GLfloat pd[3];

	GLfloat pasc[3];
	GLfloat rbtd[3];
	GLfloat scpa[3];
	GLfloat tdrb[3];
	
	// переменные для четвёртого пласта куба: 
	GLfloat pr[3];
	GLfloat rs[3];
	GLfloat st[3];
	GLfloat tp[3];

	GLfloat rp[3];
	GLfloat sr[3];
	GLfloat ts[3];
	GLfloat pt[3];

	GLfloat ps[3];
	GLfloat rt[3];
	GLfloat sp[3];
	GLfloat tr[3];

	if (stage == 0)
	{
		DrawSponge(a, b, c, d, p, r, s, t);
	}
	else
	{
		lambda1 = 0.5;
		lambda2 = 2.0;
		for (int j = 0; j < 3; j++)
		{
			// Первый пласт куба:
			ab[j] = (a[j] + lambda1 * b[j]) / (1 + lambda1);
			bc[j] = (b[j] + lambda1 * c[j]) / (1 + lambda1);
			cd[j] = (c[j] + lambda1 * d[j]) / (1 + lambda1);
			da[j] = (d[j] + lambda1 * a[j]) / (1 + lambda1);

			ba[j] = (a[j] + lambda2 * b[j]) / (1 + lambda2);
			cb[j] = (b[j] + lambda2 * c[j]) / (1 + lambda2);
			dc[j] = (c[j] + lambda2 * d[j]) / (1 + lambda2);
			ad[j] = (d[j] + lambda2 * a[j]) / (1 + lambda2);

			ac[j] = (a[j] + lambda1 * c[j]) / (1 + lambda1);
			bd[j] = (b[j] + lambda1 * d[j]) / (1 + lambda1);
			ca[j] = (a[j] + lambda2 * c[j]) / (1 + lambda2);
			db[j] = (b[j] + lambda2 * d[j]) / (1 + lambda2);

			// Второй пласт куба:
			dt[j] = (d[j] + lambda1 * t[j]) / (1 + lambda1);
			ap[j] = (a[j] + lambda1 * p[j]) / (1 + lambda1);
			br[j] = (b[j] + lambda1 * r[j]) / (1 + lambda1);
			cs[j] = (c[j] + lambda1 * s[j]) / (1 + lambda1);

			ds[j] = (d[j] + lambda1 * s[j]) / (1 + lambda1);
			cr[j] = (c[j] + lambda1 * r[j]) / (1 + lambda1);
			bp[j] = (b[j] + lambda1 * p[j]) / (1 + lambda1);
			at[j] = (a[j] + lambda1 * t[j]) / (1 + lambda1);

			ct[j] = (c[j] + lambda1 * t[j]) / (1 + lambda1);
			bs[j] = (b[j] + lambda1 * s[j]) / (1 + lambda1);
			ar[j] = (a[j] + lambda1 * r[j]) / (1 + lambda1);
			dp[j] = (d[j] + lambda1 * p[j]) / (1 + lambda1);

			apcs[j] = (ap[j] + lambda1 * cs[j]) / (1 + lambda1);
			brdt[j] = (br[j] + lambda1 * dt[j]) / (1 + lambda1);
			csap[j] = (ap[j] + lambda2 * cs[j]) / (1 + lambda2);
			dtbr[j] = (br[j] + lambda2 * dt[j]) / (1 + lambda2);

			// Третий пласт куба:
			td[j] = (d[j] + lambda2 * t[j]) / (1 + lambda2);
			pa[j] = (a[j] + lambda2 * p[j]) / (1 + lambda2);
			rb[j] = (b[j] + lambda2 * r[j]) / (1 + lambda2);
			sc[j] = (c[j] + lambda2 * s[j]) / (1 + lambda2);

			sd[j] = (d[j] + lambda2 * s[j]) / (1 + lambda2);
			rc[j] = (c[j] + lambda2 * r[j]) / (1 + lambda2);
			pb[j] = (b[j] + lambda2 * p[j]) / (1 + lambda2);
			ta[j] = (a[j] + lambda2 * t[j]) / (1 + lambda2);

			tc[j] = (c[j] + lambda2 * t[j]) / (1 + lambda2);
			sb[j] = (b[j] + lambda2 * s[j]) / (1 + lambda2);
			ra[j] = (a[j] + lambda2 * r[j]) / (1 + lambda2);
			pd[j] = (d[j] + lambda2 * p[j]) / (1 + lambda2);

			pasc[j] = (pa[j] + lambda1 * sc[j]) / (1 + lambda1);
			rbtd[j] = (rb[j] + lambda1 * td[j]) / (1 + lambda1);
			scpa[j] = (pa[j] + lambda2 * sc[j]) / (1 + lambda2);
			tdrb[j] = (rb[j] + lambda2 * td[j]) / (1 + lambda2);

			// Четвёртый пласт куба:
			pr[j] = (p[j] + lambda1 * r[j]) / (1 + lambda1);
			rs[j] = (r[j] + lambda1 * s[j]) / (1 + lambda1);
			st[j] = (s[j] + lambda1 * t[j]) / (1 + lambda1);
			tp[j] = (t[j] + lambda1 * p[j]) / (1 + lambda1);

			rp[j] = (p[j] + lambda2 * r[j]) / (1 + lambda2);
			sr[j] = (r[j] + lambda2 * s[j]) / (1 + lambda2);
			ts[j] = (s[j] + lambda2 * t[j]) / (1 + lambda2);
			pt[j] = (t[j] + lambda2 * p[j]) / (1 + lambda2);

			ps[j] = (p[j] + lambda1 * s[j]) / (1 + lambda1);
			rt[j] = (r[j] + lambda1 * t[j]) / (1 + lambda1);
			sp[j] = (p[j] + lambda2 * s[j]) / (1 + lambda2);
			tr[j] = (r[j] + lambda2 * t[j]) / (1 + lambda2);
		}

		// рекурсивно вызываем первый пласт кубов:
		DivideSponge(d, dc, db, da, dt, ds, dtbr, dp, stage - 1);
		DivideSponge(dc, cd, ca, db, ds, ct, csap, dtbr, stage - 1);
		DivideSponge(cd, c, cb, ca, ct, cs, cr, csap, stage - 1);
		DivideSponge(da, db, ac, ad, dp, dtbr, apcs, at, stage - 1);
		DivideSponge(ca, cb, bc, bd, csap, cr, bs, brdt, stage - 1);
		DivideSponge(ad, ac, ab, a, at, apcs, ar, ap, stage - 1);
		DivideSponge(ac, bd, ba, ab, apcs, brdt, bp, ar, stage - 1);
		DivideSponge(bd, bc, b, ba, brdt, bs, br, bp, stage - 1);

		// рекурсивно вызываем второй пласт кубов:
		DivideSponge(dt, ds, dtbr, dp, td, tc, tdrb, ta, stage - 1);
		DivideSponge(ct, cs, cr, csap, sd, sc, sb, scpa, stage - 1);
		DivideSponge(at, apcs, ar, ap, pd, pasc, pb, pa, stage - 1);
		DivideSponge(brdt, bs, br, bp, rbtd, rc, rb, ra, stage - 1);

		// рекурсивно вызываем третий пласт кубов:
		DivideSponge(td, tc, tdrb, ta, t, ts, tr, tp, stage - 1);
		DivideSponge(tc, sd, scpa, tdrb, ts, st, sp, tr, stage - 1);
		DivideSponge(sd, sc, sb, scpa, st, s, sr, sp, stage - 1);
		DivideSponge(ta, tdrb, pasc, pd, tp, tr, ps, pt, stage - 1);
		DivideSponge(scpa, sb, rc, rbtd, sp, sr, rs, rt, stage - 1);
		DivideSponge(pd, pasc, pb, pa, pt, ps, pr, p, stage - 1);
		DivideSponge(pasc, rbtd, ra, pb, ps, rt, rp, pr, stage - 1);
		DivideSponge(rbtd, rc, rb, ra, rt, rs, r, rp, stage - 1);

	}
}

void DrawSponge(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, GLfloat *p, GLfloat *r, GLfloat *s, GLfloat *t)
{
	if (!shading)
	{
		glBegin(GL_QUADS);
		glColor3f(red, green, blue);
		DrawQuoad(a, b, c, d);
		glColor3f(red2, green2, blue2);
		DrawQuoad(d, t, s, c);
		glColor3f(red1, green1, blue1);
		DrawQuoad(c, s, r, b);
		glColor3f(red2, green2, blue2);
		DrawQuoad(b, r, p, a);
		glColor3f(red1, green1, blue1);
		DrawQuoad(a, p, t, d);
		glColor3f(red, green, blue);
		DrawQuoad(p, r, s, t);
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
		glColor3f(0.25, 0.41, 0.88);
		DrawLineQuoad(t, p, r, s);
		DrawLineQuoad(a, p, r, b);
		DrawLineQuoad(a, b, c, d);
		DrawLineQuoad(c, s, t, d);
		glEnd();
	}
}

void DrawQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
}

void DrawLineQuoad(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(c);
	glVertex3fv(d);
	glVertex3fv(d);
	glVertex3fv(a);

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
		if (stage < 4) stage += 1;
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