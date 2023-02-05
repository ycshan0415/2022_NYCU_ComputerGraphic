#include <GL/glut.h>
#include <GL/gl.h>
#include <Windows.h>
#include <iostream>

using namespace std;

# define PI 3.14159265
//float w = glutGet(GLUT_SCREEN_WIDTH);
//float h = glutGet(GLUT_SCREEN_HEIGHT);
float shift = 0;
int wid = 600, hei = 500;
float car_x = 0;
float coin_x = 300, coin_y = 490;
int caught = 0, missed = 0, total = 0;
int level = 1;
float speed = 0.7;
int step = 15;
int dire = 2;
int mode = 0;

void init();
void player();
void coin();
void coin_generate();
void clouds();
void score();
void get_score();

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, wid, hei);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)wid, 0, (GLdouble)hei); // ??
	// left, right, bottom, top
	glMatrixMode(GL_MODELVIEW);
	// glutPostRedisplay();

}

void player() 
{
	if (shift < -260) shift = -260;
	if (shift > 260) shift = 260;
	// avoid going ouside the screen

	// car
	glColor3f(1.0, 0.0, 0.0); // red
	glBegin(GL_QUADS);
		glVertex2f(260 + shift, 80); // top left 
		glVertex2f(340 + shift, 80); // top right
		glVertex2f(340 + shift, 30); // bottom right
		glVertex2f(260 + shift, 30); // bottom left
	car_x = 260 + shift;
	glEnd();
	glFlush();

	// head (has directions)
	glColor3f(0.0, 0.0, 1.0); // blue
	if (dire == 2) { // right
		glBegin(GL_POLYGON);
			glVertex2f(340 + shift, 80);
			glVertex2f(340 + shift, 30);
			glVertex2f(380 + shift, 55);
		glEnd();
	}
	else { // left
		glBegin(GL_POLYGON);
			glVertex2f(260 + shift, 80);
			glVertex2f(260 + shift, 30);
			glVertex2f(220 + shift, 55);
		glEnd();
	}
	glFlush();

	float angle;
	float radius = 20;
	// wheel 1
	glColor3f(1.0, 1.0, 1.0); // white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		angle = (i * PI) / 180;
		float x = cos(angle) * radius;
		float y = sin(angle) * radius;
		glVertex2f(270 + x + shift, 20 + y);
	}
	glEnd();
	glFlush();

	// wheel 2
	glColor3f(1.0, 1.0, 1.0); // white
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		angle = (i * PI) / 180;
		float x = cos(angle) * radius;
		float y = sin(angle) * radius;
		glVertex2f(330 + x + shift, 20 + y);
	}
	glEnd();
	glFlush();

	// glutSwapBuffers();
}

void coin() 
{
	float angle;
	float radius = 20;
	glColor3f(1.0, 1.0, 0.0); // yellow
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		angle = (i * PI) / 180;
		float x = coin_x + cos(angle) * radius;
		float y = coin_y + sin(angle) * radius;
		glVertex2f(x, y);
	}
	glEnd();
	glFlush();
	
	//glutSwapBuffers();
}

void coin_generate()
{
	coin_y = 490;
	if (missed >= 5)
		get_score();
	total++;

	switch (rand() % 10)
	{
		case 0:coin_x = 25; break;
		case 1:coin_x = 75; break;
		case 2:coin_x = 125; break;
		case 5:coin_x = 175; break;
		case 3:coin_x = 225; break;
		case 4:coin_x = 275; break;
		case 7:coin_x = 325; break;
		case 6:coin_x = 375; break;
		case 8:coin_x = 425; break;
		case 9:coin_x = 475; break;
	}

}

void clouds()
{
	float theta;
	GLfloat angle;
	glLineWidth(1.5);
	glColor3f(1, 1, 1);
	// cloud 1
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(50 + 50 * cos(theta) / 2, 460 + 50 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(80 + 50 * cos(theta) / 2, 450 + 50 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(90 + 50 * cos(theta) / 2, 480 + 50 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(120 + 50 * cos(theta) / 2, 470 + 50 * sin(theta) / 2);
	}
	glEnd();
	//
	// cloud 2
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(190 + 45 * cos(theta) / 2, 460 + 45 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(225 + 45 * cos(theta) / 2, 470 + 45 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(225 + 45 * cos(theta) / 2, 450 + 45 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(260 + 45 * cos(theta) / 2, 460 + 45 * sin(theta) / 2);
	}
	glEnd();
	//
	// cloud 3
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(330 + 50 * cos(theta) / 2, 460 + 50 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(360 + 50 * cos(theta) / 2, 450 + 50 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(370 + 50 * cos(theta) / 2, 480 + 50 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(400 + 50 * cos(theta) / 2, 470 + 50 * sin(theta) / 2);
	}
	glEnd();
	//
	// cloud 4
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(470 + 45 * cos(theta) / 2, 460 + 45 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(505 + 45 * cos(theta) / 2, 470 + 45 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(505 + 45 * cos(theta) / 2, 450 + 45 * sin(theta) / 2);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * PI * i / 180;
		glVertex2f(540 + 45 * cos(theta) / 2, 460 + 45 * sin(theta) / 2);
	}
	glEnd();
	//
	glFlush();
}

void score()
{
	if (coin_y <= 70 && (coin_x >= car_x && coin_x <= car_x + 80)) {
		printf("\a");
		caught++;
		coin_y = -50;
	}
	missed = total - caught;
}

void get_score()
{
	char gg[12] = "GAME OVER!!";
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2i(230, 300);
	for (int i = 0; i < 12; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, gg[i]);
	
	glFlush();
	glutSwapBuffers();

	printf("\n\n\tGAME OVER\n\n");
	printf("\n  Your score: %d \n", caught);

	getchar();
	exit(0);
}

void game_start(int i, int j)
{
	int k;
	char title[13] = "Coin Catcher";
	char start[24] = "Press Space for start";
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2i(230, 300);
	for (k = 0; k < 13; k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[k]);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(200, 200);
	for (k = 0; k < 24; k++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, start[k]);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (mode != 0) {
		if (caught < 10) {
			char level[8] = "level 1";
			char start[13] = "GAME START!!";
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2i(270, 300);
			for (int i = 0; i < 8; i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, level[i]);
			glRasterPos2i(250, 250);
			for (int i = 0; i < 13; i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, start[i]);
			speed = 0.7;
		}
		else if (caught >= 10 && caught < 20) {
			char level[8] = "level 2";
			char start[36] = "You have got 10 points! keep going!";
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2i(270, 300);
			for (int i = 0; i < 8; i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, level[i]);
			glRasterPos2i(160, 250);
			for (int i = 0; i < 36; i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, start[i]);
			speed = 0.9;
		}
		else if (caught >= 20 && caught < 40) {
			char level[8] = "level 3";
			char start[24] = "Wow! Already 20 points!";
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2i(270, 300);
			for (int i = 0; i < 8; i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, level[i]);
			glRasterPos2i(200, 250);
			for (int i = 0; i < 24; i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, start[i]);
			speed = 1.0;
		}
		else if (caught >= 40) {
			char level[8] = "level 4";
			char start[40] = "Awesome! 40 points reached! Last stage!";
			glColor3f(1.0, 1.0, 1.0);
			glRasterPos2i(270, 300);
			for (int i = 0; i < 8; i++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, level[i]);
			glRasterPos2i(150, 250);
			for (int i = 0; i < 40; i++)
				glutBitmapCharacter(GLUT_BITMAP_8_BY_13, start[i]);
			speed = 1.3;
			step = 25;
		}

		player();
		if (coin_y <= 10)
			coin_generate();
		coin();
		coin_y -= speed;
		clouds();
		score();
		
	}
	else {
		game_start(40, 300);
	}

	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	wid = w;
	hei = h;
}

void catchKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: 
			shift -= step;
			// cout << "left\n";
			dire = 1;
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT: 
			shift += step;
			// cout << "right\n";
			dire = 2;
			glutPostRedisplay();
			break;
		//case GLUT_KEY_UP: NULL;
		//case GLUT_KEY_DOWN: NULL;
	}
}

void menu(int id)
{
	switch (id) {
	case 1: 
		mode = 1;
		break;
	case 2: 
		printf("\n\n\n\t\tQUIT BY PLAYER\n");
		exit(0);
		break;
	default:
		exit(0);
	}

	glutPostRedisplay();
}

void keys(unsigned char key, int x, int y)
{
	if (key == ' ') {
		mode = 1;
		// cout << "space\n";
	}
}

void rules() {
	printf("******************************************************************\n");
	printf("\n\t\t COIN CATCHER\n\n");
	printf("******************************************************************");
	printf("\n\tHow to Play..?\n");
	printf("\n <1> Use direction to control your truck.\n");
	printf("\n <2> To Start, press Space or click Right mouse button then click 'Start Game'.\n");
	printf("\n <3> To Quit manually, click Right mouse button then click 'Quit'.\n");
	printf("\n\n NOTICE : If you miss 5 coins, then you will become a poor guy.\n");
	printf("\n Which means : NO MORE GAMES TO PLAY!!\n");
	printf("\n For each level, the drop speed will increase\n\n");
	printf("\n Hope you enjoy!\n");
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	int mode = GLUT_RGB | GLUT_DOUBLE;
	glutInitDisplayMode(mode);
	init();
	glutInitWindowSize(wid, hei);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("demo");

	rules();
	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Start game", 1);
	glutAddMenuEntry("Quit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// game
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutSpecialFunc(catchKey);
	glutIdleFunc(display);
	glutMainLoop();


	return 0;
}