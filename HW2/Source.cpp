#include <GL/glut.h>
#include <GL/gl.h>
#include <Windows.h>
#include <iostream>
using namespace std;

GLfloat no_mat[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat no_mat_red[4] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat no_mat_green[4] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat no_mat_blue[4] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat no_mat_yellow[4] = {1.0, 1.0, 0.0, 1.0};
GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat no_shininess[] = {0.1};
GLfloat low_shininess[] = {5.0};
GLfloat high_shininess[] = {100.0};
GLfloat mat_emission[] = {0.3, 0.8, 0.0, 1.0};
int angle = 0, neck = 0;
int lshoulder = 0, lhand = 0, rshoulder = 0, rhand = 0;
int lthigh = 0, lcalf = 0, rthigh = 0, rcalf = 0;
bool lshoulderDir = 1, rshoulderDir = 0, lthighDir = 0, rthighDir = 1;
bool walk = 0;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat position[] = {0.0, 5.0, 10.0, 0.0};
	GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
	GLfloat local_view[] = {0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void body(void)
{
	glPushMatrix();
	glTranslatef(0, 1.5, 0);
	glScalef(0.5, 1, 0.3);
	//glEnable(GL_COLOR_MATERIAL);
	//glColor3f(0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	
	glutSolidCube(4);
	glPopMatrix();
}

void head(void)
{
	glPushMatrix();
	//glEnable(GL_COLOR_MATERIAL);
	//glColor3f(1, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_yellow);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat_yellow);

	glTranslatef(0, 3.5, 0);
	glRotatef(neck, 0, 0, 1);
	glTranslatef(0, 1, 0);
	glutWireSphere(0.8, 150, 150);

	glPopMatrix();
}

void leftArm(void)
{	
	glPushMatrix();
	//glEnable(GL_COLOR_MATERIAL);
	//glColor3f(1, 0, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_red);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat_red);
	glTranslatef(1.6, 3.0, 0);
	if (walk)
		glRotatef(lshoulder, 1, 0, 0);
	else
		glRotatef(lshoulder, 0, 0, 1);

	glTranslatef(0, -0.6, 0);
	glScalef(0.5, 1, 0.3);
	glutSolidCube(2);

	glTranslatef(0, -1.3, 0);
	glScalef(1 / 0.5, 1.0f, 1 / 0.3);
	glRotatef(lhand, 0, 0, 1);
	glutWireSphere(0.3, 100, 100);

	glTranslatef(0, -1.2, 0);
	glScalef(0.4, 1, 0.3);
	glutSolidCube(1.8);

	glPopMatrix();
}

void rightArm(void)
{
	glPushMatrix();
	//glEnable(GL_COLOR_MATERIAL);
	//glColor3f(0, 0, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_red);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat_red);
	glTranslatef(-1.6, 3, 0);
	if (walk)
		glRotatef(rshoulder, 1, 0, 0);
	else
		glRotatef(rshoulder, 0, 0, 1);

	glTranslatef(0, -0.6, 0);
	glScalef(0.5, 1, 0.3);
	glutSolidCube(2);

	glTranslatef(0, -1.3, 0);
	glScalef(1 / 0.5, 1.0f, 1 / 0.3);
	glRotatef(rhand, 0, 0, 1);
	glutWireSphere(0.3, 100, 100);

	glTranslatef(0, -1.2, 0);
	glScalef(0.4, 1, 0.3);
	glutSolidCube(1.8);

	glPopMatrix();
}

void leftLeg(void)
{	
	glPushMatrix();
	//glEnable(GL_COLOR_MATERIAL);
	//glColor3f(0, 0, 1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_blue);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat_blue);

	glTranslatef(0.5, -0.4, 0);
	glRotatef(lthigh, 1, 0, 0);
	glTranslatef(0, -1.1, 0);
	glScalef(0.4, 1.0, 0.3);
	glutSolidCube(1.8);

	glTranslatef(0, -1.2, 0);
	glScalef(1 / 0.5, 1.0f, 1 / 0.3);
	glRotatef(lcalf, 1, 0, 0);
	glutWireSphere(0.3, 100, 100);

	glTranslatef(0, -1.2, 0);
	glScalef(0.6, 1, 0.4);
	glutSolidCube(2);

	glPopMatrix();
}

void rightLeg(void)
{
	glPushMatrix();
	//glEnable(GL_COLOR_MATERIAL);
	//glColor3f(0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat_blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat_blue);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat_blue);

	glTranslatef(-0.5, -0.4, 0);
	glRotatef(rthigh, 1, 0, 0);
	glTranslatef(0, -1.1, 0);
	glScalef(0.4, 1, 0.3);
	glColor3f(1, 1, 0);
	glutSolidCube(1.8);

	glTranslatef(0, -1.2, 0);
	glScalef(1 / 0.5, 1.0f, 1 / 0.3);
	glRotatef(rcalf, 1, 0, 0);
	glutWireSphere(0.3, 100, 100);

	glTranslatef(0, -1.2, 0);
	glScalef(0.6, 1, 0.4);
	glutSolidCube(2);

	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);

	glTranslatef(0, 4, 0);
	body();
	head();
	leftArm();
	rightArm();
	leftLeg();
	rightLeg();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(80.0f, (GLfloat)w / (GLfloat)h, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 4, 8, 0.0, 4, 0.0, 0.0, 1.0, 0.0);
}

void keys(unsigned char key, int x, int y)
{
	walk = 0;
	switch (key) {
		case 'z':
			if (neck <= 40)
				neck += 5;
			glutPostRedisplay();
			break;
		case 'x':
			if (neck >= -40)
				neck -= 5;
			glutPostRedisplay();
			break;
		case 'q':
			if (rshoulder >= -160)
				rshoulder -= 5;
			glutPostRedisplay();
			break;
		case 'a':
			if (rshoulder <= 0)
				rshoulder += 5;
			glutPostRedisplay();
			break;
		case 'w':
			if (rhand >= -140)
				rhand -= 5;
			glutPostRedisplay();
			break;
		case 's':
			if (rhand <= 0)
				rhand += 5;
			glutPostRedisplay();
			break;
		case 'e':
			if (lshoulder <= 160)
				lshoulder += 5;
			glutPostRedisplay();
			break;
		case 'd':
			if (lshoulder >= 0)
				lshoulder -= 5;
			glutPostRedisplay();
			break;
		case 'r':
			if (lhand <= 140)
				lhand += 5;
			glutPostRedisplay();
			break;
		case 'f':
			if (lhand >= 0)
				lhand -= 5;
			glutPostRedisplay();
			break;
		case 't':
			if (rthigh >= -110)
				rthigh -= 5;
			glutPostRedisplay();
			break;
		case 'g':
			if (rthigh <= 60)
				rthigh += 5;
			glutPostRedisplay();
			break;
		case 'y':
			if (rcalf >= 0)
				rcalf -= 5;
			glutPostRedisplay();
			break;
		case 'h':
			if (rcalf <= 110)
				rcalf += 5;
			glutPostRedisplay();
			break;
		case 'u':
			if (lthigh >= -110)
				lthigh -= 5;
			glutPostRedisplay();
			break;
		case 'j':
			if (lthigh <= 60)
				lthigh += 5;
			glutPostRedisplay();
			break;
		case 'i':
			if (lcalf >= 0)
				lcalf -= 5;
			glutPostRedisplay();
			break;
		case 'k':
			if (lcalf <= 110)
				lcalf += 5;
			glutPostRedisplay();
			break;
		case ',':
			angle = (angle + 5) % 360;
			glutPostRedisplay();
			break;
		case '.':
			angle = (angle - 5) % 360;
			glutPostRedisplay();
			break;
		case ' ':
			walk = 1;
			glTranslatef(0.0f, 0.0f, 0.0f);
			if (lshoulderDir) {
				lshoulder += 5;
				if (lshoulder >= 50)
					lshoulderDir = 0;
			}
			else {
				lshoulder -= 5;
				if (lshoulder <= -50)
					lshoulderDir = 1;
			}
			if (rshoulderDir) {
				rshoulder += 5;
				if (rshoulder >= 50)
					rshoulderDir = 0;
			}
			else {
				rshoulder -= 5;
				if (rshoulder <= -50)
					rshoulderDir = 1;
			}
			if (lthighDir) {
				lthigh += 5;
				if (lthigh >= 50)
					lthighDir = 0;
			}
			else {
				lthigh -= 5;
				if (lthigh <= -50)
					lthighDir = 1;
			}
			if (rthighDir) {
				rthigh += 5;
				if (rthigh >= 50)
					rthighDir = 0;
			}
			else {
				rthigh -= 5;
				if (rthigh <= -50)
					rthighDir = 1;
			}
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
	cout << "press q, a, w, s for left arm (your left)\n";
	cout << "press e, d, r, f for right arm (your right)\n";
	cout << "press t, g, y, h for left leg (your left)\n";
	cout << "press u, j, i, k for right leg (your right)\n";
	cout << "press z, x for neck\n";
	cout << "press ',', '.' to spin around\n";
	cout << "pree spacebar to keep moving\n";
	glutInit(&argc, argv);
	int mode = GLUT_RGB | GLUT_DOUBLE;
	glutInitDisplayMode(mode);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(250, 60);
	glutCreateWindow(argv[0]);
	glutSetWindowTitle("109550087 單宇晟");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMainLoop();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	return 0;
}