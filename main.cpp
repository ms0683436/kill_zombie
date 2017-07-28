#include "Function.h"
#define   PI  3.1415926
using namespace std;
/*-Declare GLU quadric objects, sphere, cylinder, and disk --*/
GLUquadricObj  *sphere = NULL, *cylind = NULL, *disk;

float  eye[3] = { 0.0, 30, -35 };
float  eyedirection[3] = { 0, 15, -35 };
float  ahead[3] = { 0, 0, 1 };


float a = 0,b=10;

int angx;
//跳躍
int jump=0;
int jumpdown = 0;
int speed = 8;
float angP1 = 0, angP2 = 0, angP3 = 0;
int range = 2;

bool MOUSE_LEFT = false, MOUSE_RIGHT = false;
float ro=0;

void rotateY(float &x, float &z, float ang) {
	float tempX = x, tempZ = z;
	x = tempX * cos(ang) + tempZ * sin(ang);
	z = -tempX * sin(ang) + tempZ * cos(ang);
}

void DrawBody() {
	glPushMatrix();
	glColor3f(0.2, 0.1, 0.6);
	glScalef(my.body.L, my.body.H, my.body.W);
	draw_cube();
	glPopMatrix();
}

void DrawArm() {
	glPushMatrix();
	glColor3f(0.8, 0.2, 0.2);
	glScalef(2, 5, 1);
	glTranslatef(0, -0.5, 0);
	draw_cube();
	glPopMatrix();
}

void DrawLag() {
	glPushMatrix();
	glColor3f(0.2, 0.8, 0.8);
	glScalef(2, 6, 1.5);
	glTranslatef(0, -0.5, 0);
	draw_cube();
	glPopMatrix();
}

void DrawPerson(human my) {
	glPushMatrix();	//上面的長方形
	glTranslatef(my.body.x, my.body.y, my.body.z);
	glRotatef(-angx, 0.0, 1.0, 0.0);
	//左腳
	glPushMatrix();
	glTranslatef(0, -4, 0);
	glRotated(angP1, 1, 0, 0);
	glTranslatef(1.5, 0, 0);
	DrawLag();
	glPopMatrix();
	//右腳
	glPushMatrix();
	glTranslatef(0, -4, 0);
	glRotated(angP2, 1, 0, 0);
	glTranslatef(-1.5, 0, 0);
	DrawLag();
	glPopMatrix();
	//左手
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotated(angP3, 1, 0, 0);
	glRotated(angP2, 1, 0, 0);
	glTranslatef(3.5, 0.5, 0);
	DrawArm();
	glPopMatrix();
	//右手
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotated(angP1, 1, 0, 0);
	glTranslatef(-3.5, 0.5, 0);
	DrawArm();
	glPopMatrix();
	//頭
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.8);
	glTranslatef(0, 5, 0);
	glScalef(my.body.L, 2, my.body.W);
	draw_cube();
	glPopMatrix();
	//身體
	DrawBody();
	glPopMatrix();
}

void addBox(float pos[], float vel[])
{
	Particle p;
	for (int i = 0; i < 3; i++) {
		p.pos[i] = pos[i];
		p.vel[i] = vel[i];
		p.color[i] = (double)rand() / RAND_MAX;
	}
	my.myBag.particlesBox.push_back(p);
}

void DrawBox() {
	for (int i = 0; i < my.myBag.particlesBox.size(); i++) {
		glPushMatrix();
		glTranslatef(my.myBag.particlesBox[i].pos[0], my.myBag.particlesBox[i].pos[1], my.myBag.particlesBox[i].pos[2]);
		glScalef(10, 10, 10);
		glColor3f(0.2, 0.2, 0.5);
		draw_cube();
		glPopMatrix();
	}
}

void buildBox(float pos[], float ang) {
	float v[] = { 0,0,0 };
	float box[] = { 0,-5,10 };
	float BoxPos[3];
	int xxx, yyy, zzz;
	rotateY(box[0], box[2], ang);
	for (int i = 0; i < 3; i++) {
		BoxPos[i] = pos[i] + box[i];
	}
	xxx = (BoxPos[0] + 155) / 10;
	yyy = (BoxPos[1]) / 10;
	zzz = (BoxPos[2] + 155) / 10;

	terrain[xxx][yyy][zzz].ONOROFF = 1;
	xxx = xxx * 10 - 150;
	yyy = yyy * 10;
	zzz = zzz * 10 - 150;
	BoxPos[0] = xxx;
	BoxPos[1] = yyy;
	BoxPos[2] = zzz;
	addBox(BoxPos, v);
}

void addBall(float pos[], float vel[])
{
	Particle p;
	for (int i = 0; i < 3; i++) {
		p.pos[i] = pos[i];
		p.vel[i] = vel[i];
		p.color[i] = (double)rand() / RAND_MAX;
	}
	my.myBag.particlesBall.push_back(p);

}

void draw_ball() {
	for (int i = 0; i < my.myBag.particlesBall.size(); i++) {
		glPushMatrix();
		glColor3f(0.7, 0.1, 0.6);
		glTranslatef(my.myBag.particlesBall[i].pos[0], my.myBag.particlesBall[i].pos[1], my.myBag.particlesBall[i].pos[2]);
		glutSolidSphere(my.myBag.particlesBall[i].radius, 20, 15);
		glPopMatrix();
	}
}

void throwBall(float pos[], float ang) {
	float v[] = { 0,0,2 };
	float Ball[] = { 0,0,-5 };
	float BallPos[3];
	rotateY(v[0], v[2], ang);
	rotateY(Ball[0], Ball[2], ang);
	for (int i = 0; i < 3; i++) {
		BallPos[i] = pos[i] - Ball[i];
	}
	BallPos[1] = pos[1] + 10;
	addBall(BallPos, v);
}

void ballsmove(int i) {
	int zzz=0, yyy=0, xxx=0,radius=0;
	int text_x=0,text_y=0,text_z=0;
	radius = my.myBag.particlesBall[i].radius/2;
	xxx = (my.myBag.particlesBall[i].pos[0]+ my.myBag.particlesBall[i].vel[0] +155)/10;
	yyy = (my.myBag.particlesBall[i].pos[1] + my.myBag.particlesBall[i].vel[1])/10;
	zzz = (my.myBag.particlesBall[i].pos[2] + my.myBag.particlesBall[i].vel[2] +155)/10;
	
	if (terrain[xxx][yyy][zzz].ONOROFF == 1){
		//尋找前一次的方位
		text_x = (my.myBag.particlesBall[i].pos[0] + 155) / 10;
		text_y = (my.myBag.particlesBall[i].pos[1]) / 10;
		text_z = (my.myBag.particlesBall[i].pos[2] + 155) / 10;
		
		text_x -= xxx;
		text_y -= yyy;
		text_z -= zzz;
		//printf("%d  %d  %d-------------------------this\n", text_x, text_y, text_z);
		if (text_x != 0) {
			my.myBag.particlesBall[i].vel[0] = (-my.myBag.particlesBall[i].vel[0]);
		}
		 if (text_y != 0) {
			 my.myBag.particlesBall[i].vel[1] = (-my.myBag.particlesBall[i].vel[1]);
		}
		 if (text_z != 0) {
			 my.myBag.particlesBall[i].vel[2] = (-my.myBag.particlesBall[i].vel[2]);
		}
	}
	else {
		my.myBag.particlesBall[i].pos[0] += my.myBag.particlesBall[i].vel[0];
		my.myBag.particlesBall[i].pos[1] += my.myBag.particlesBall[i].vel[1];
		my.myBag.particlesBall[i].pos[2] += my.myBag.particlesBall[i].vel[2];
	}

	for (int k = 0; k < 10; k++) {
		if (monster[k].humanmonster.body.x + monster[k].humanmonster.body.L / 2 >my.myBag.particlesBall[i].pos[0] &&
			monster[k].humanmonster.body.x - monster[k].humanmonster.body.L / 2 <my.myBag.particlesBall[i].pos[0] &&
			monster[k].humanmonster.body.y + monster[k].humanmonster.body.H / 2 >my.myBag.particlesBall[i].pos[1] &&
			monster[k].humanmonster.body.y - monster[k].humanmonster.body.H / 2 <my.myBag.particlesBall[i].pos[1] &&
			monster[k].humanmonster.body.z + monster[k].humanmonster.body.W / 2 >my.myBag.particlesBall[i].pos[2] &&
			monster[k].humanmonster.body.z - monster[k].humanmonster.body.W / 2 <my.myBag.particlesBall[i].pos[2]
			) {
			monster[k].life = 1;
			monster[k].humanmonster.body.y = -20;
		}
	}
}

void drawing_monster() {
	for (int i = 0; i < 10; i++) {
		if (monster[i].life == 0) {	DrawPerson(monster[i].humanmonster);}
		//
	}
}

void monstermove() {
	float temp_x = 0, temp_y = 0, temp_z = 0, temp = 0;
	int xxx, yyy, zzz;
	for (int i = 0; i < 10; i++) {
		////////////////////////取怪物速度
		temp_x = my.body.x - monster[i].humanmonster.body.x;
		temp_y = my.body.y - monster[i].humanmonster.body.y;
		temp_z = my.body.z - monster[i].humanmonster.body.z;
		temp = sqrt(temp_x*temp_x + temp_y*temp_y + temp_z*temp_z);
		monster[i].humanmonster.vec_x = temp_x / temp;
		monster[i].humanmonster.vec_z = temp_z / temp;
		monster[i].humanmonster.vec_x *= 0.1;
		monster[i].humanmonster.vec_z *= 0.1;
		//////////////////////////////////////////////////////
		xxx = (monster[i].humanmonster.body.x + monster[i].humanmonster.vec_x + 155) / 10;
		yyy = (monster[i].humanmonster.body.y - 5) / 10;
		zzz = (monster[i].humanmonster.body.z + monster[i].humanmonster.vec_z + 155) / 10;
		/////////////////////////////////////////
		//printf("%d  %d  %d\n", xxx, yyy, zzz);
		//printf("%f  %f  \n", monster[i].humanmonster.body.y, monster[i].humanmonster.vec_y);

		if (terrain[xxx][yyy][zzz].ONOROFF == 1) {
			monster[i].jump = 1;
		}
		else {
			monster[i].humanmonster.body.x += monster[i].humanmonster.vec_x;
			monster[i].humanmonster.body.z += monster[i].humanmonster.vec_z;
		}


		if (monster[i].jump >= 1) {
			if (monster[i].jump>8) {
				monster[i].jump = 0;
			}
			else {
				monster[i].humanmonster.body.y += monster[i].humanmonster.vec_y;
				monster[i].jump++;
				monster[i].humanmonster.vec_y--;
			}
		}
		else {
			if (monster[i].humanmonster.body.y>15) {
				monster[i].humanmonster.body.y -= 3;
				monster[i].jump = 0;
				monster[i].humanmonster.vec_y = 8;
			}
			zzz = (monster[i].humanmonster.body.z + 155) / 10;
			xxx = (monster[i].humanmonster.body.x + 155) / 10;
			yyy = (monster[i].humanmonster.body.y - 5) / 10;
			if (terrain[xxx][yyy][zzz].ONOROFF == 1) {
				monster[i].humanmonster.body.y += 3;
			}
		}
	}
}

void gameTest() {
	float testX, testY, testZ;
	int win = 0;
	for (int i = 0; i < 10; i++) {
		testX = abs(my.body.x - monster[i].humanmonster.body.x);
		testY = abs(my.body.y - monster[i].humanmonster.body.y);
		testZ = abs(my.body.z - monster[i].humanmonster.body.z);
		if (testX < my.body.L && testY < my.body.H 	&& testZ < my.body.W) {
			//printf("%d", monster[i].life);
			printf("You Loose!\n");
			system("pause");
		}
		win += monster[i].life;
		//printf("%d", monster[i].life);
	}
	if (win == 9) {
		printf("You Win!\n");
		system("pause");
	}
}

void rangeTest(int i) {
	if (my.myBag.particlesBall[i].pos[0] > 145 || my.myBag.particlesBall[i].pos[0] < -155
		|| my.myBag.particlesBall[i].pos[2] > 145 || my.myBag.particlesBall[i].pos[2] < -155)
		my.myBag.particlesBall.erase(my.myBag.particlesBall.begin()+i);
}

/*-------------------------------------------------------
* Display callback func. This func. draws three
* cubes at proper places to simulate a solar system.
*/
void display()
{
	int j = 0;
	my.body.pos[0] = my.body.x;
	my.body.pos[1] = my.body.y;
	my.body.pos[2] = my.body.z;

	/*Clear previous frame and the depth buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*----Define the current eye position and the eye-coordinate system---*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyedirection[0]+ my.body.x, eyedirection[1] + my.body.y, eyedirection[2] + my.body.z,
		my.body.x, my.body.y, my.body.z, 0, 1, 0);
	//gluLookAt(position[0] + 20.0*cos(self_ang3*PI / 180.0), position[1] + yaxe, position[2] + 20.0*sin(self_ang3*PI / 180.0), position[0], position[1], position[2], 0.0, 1.0, 0.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width / (double)height, 1, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	//跳躍
	int xxx,yyy ,zzz;
	zzz = (my.body.z + 155) / 10;
	xxx = (my.body.x + 155) / 10;
	if (jump>=1) {
		if (jump>8) {
			jump=0;
		}
		else {
			my.body.y+=speed;
		jump++;
		speed--;
		}
	}
	else {
		if (my.body.y>15) {
			my.body.y -= 3;
			jump = 0;
		}
		yyy = (my.body.y-5) / 10;
		if (terrain[xxx][yyy][zzz].ONOROFF == 1) {
			my.body.y +=3;
		}
	}

	
	DrawPerson(my);
	draw_ball();
	DrawBox();
	drawing_monster();
	monstermove();
	CreatGround();
	drawSkybox(150);
	gameTest();
	//球移動
	for (int i = 0; i < my.myBag.particlesBall.size(); i++) {
		ballsmove(i);
		my.myBag.particlesBall[i].vel[1] -= 0.6;
		rangeTest(i);
	}
	
	//drawing_human();
	/*-------Swap the back buffer to the front --------*/
	glutSwapBuffers();
	return;
}

/*--------------------------------------------------
* Keyboard callback func. When a 'q' key is pressed,
* the program is aborted.
*/
void my_quit(unsigned char key, int x1, int y2)
{
	int xxx, zzz,yyy;
	//printf("%f  %f  %f\n", a, b, c);
	if (key=='w') {
		angP3 = 0;
		if (angP1 >= 30)
			range = -2;
		if (angP1 <= -30)
			range = 2;
		angP1 += range;
		angP2 -= range;
		/////////////////////////////////
		eye[0] += ahead[0];
		eye[2] += ahead[2];
		my.body.x += ahead[0];
		my.body.z += ahead[2];
		xxx = (my.body.x + 155) / 10;
		yyy = (my.body.y)/10;
		zzz = (my.body.z + 155) / 10;
		if (terrain[xxx][yyy][zzz].ONOROFF == 1) {
			eye[0] -= ahead[0];
			eye[2] -= ahead[2];
			my.body.x -= ahead[0];
			my.body.z-= ahead[2];
		}
	}
	if (key == 's') {
		angP3 = 0;
		if (angP1 >= 30)
			range = -2;
		if (angP1 <= -30)
			range = 2;
		angP1 += range;
		angP2 -= range;
		/////////////////////////
		eye[0] -= ahead[0];
		eye[2] -= ahead[2];
		my.body.x -= ahead[0];
		my.body.z -= ahead[2];
		xxx = (my.body.x + 155) / 10;
		yyy = (my.body.y) / 10;
		zzz = (my.body.z + 155) / 10;
		if (terrain[xxx][yyy][zzz].ONOROFF == 1) {
			eye[0] += ahead[0];
			eye[2] += ahead[2];
			my.body.x += ahead[0];
			my.body.z += ahead[2];
		}
	}
	if (key == ' ') {
		speed = 8;
		jump = 1;
	}
	if (key == 'a') {
		angx -= 5;

		rotateY(eyedirection[0], eyedirection[2], PI / 180 * 5);
		rotateY(ahead[0], ahead[2], PI / 180 * 5);
		my.rotation = -angx;
	}
	if (key == 'd') {
		angx +=5;
		
		rotateY(eyedirection[0], eyedirection[2], -PI / 180*5 );
		rotateY(ahead[0], ahead[2], -PI / 180*5 );
		my.rotation = -angx;
	}

	if (key == '+') {
		angP3 = 210;
	}
		
	if (key == '-') {
		
	}
}

//void KeyboardDown(unsigned char key, int ix, int iy)
//{
//	int    i;
//	float  x[3], y[3];
//	if (key == 'c') {
//		culling = 1;
//	}
//	else if (key == 'z') {
//		culling = 0;
//	}
//
//	if (key == 'x') {
//		eyeDy += 0.5;       /* move down */
//		for (i = 0; i<3; i++) eye[i] -= 0.5*u[1][i];
//	}
//	if (key == ' ') {
//		eyeDy += -0.5;       /* move up */
//		for (i = 0; i<3; i++) eye[i] += 0.5*u[1][i];
//	}
//	if (key == 'd') {
//		angP3 = 0;
//		if (angP1 >= 30)
//			range = -2;
//		if (angP1 <= -30)
//			range = 2;
//		angP1 += range;
//		angP2 -= range;
//		eyeDx += -0.5;       /* move right */
//		for (i = 0; i < 3; i++) {
//			Person.pos[i] += 0.5*u[0][i];
//			eye[i] += 0.5*u[0][i];
//		}
//	}
//	if (key == 'a') {
//		angP3 = 0;
//		if (angP1 >= 30)
//			range = -2;
//		if (angP1 <= -30)
//			range = 2;
//		angP1 += range;
//		angP2 -= range;
//		eyeDx += 0.5;        /* move left */
//		for (i = 0; i < 3; i++) {
//			Person.pos[i] -= 0.5*u[0][i];
//			eye[i] -= 0.5*u[0][i];
//		}
//	}
//	if (key == 'w') {
//		angP3 = 0;
//		if (angP1 >= 30)
//			range = -2;
//		if (angP1 <= -30)
//			range = 2;
//		angP1 += range;
//		angP2 -= range;
//		eyeDz += 0.5;        /* forward */
//		for (i = 0; i < 3; i++) {
//			Person.pos[i] -= 0.5*u[2][i];
//			eye[i] -= 0.5*u[2][i];
//		}
//	}
//	if (key == 's') {
//		angP3 = 0;
//		if (angP1 >= 30)
//			range = -2;
//		if (angP1 <= -30)
//			range = 2;
//		angP1 += range;
//		angP2 -= range;
//		eyeDz += -0.5;       /*back */
//		for (i = 0; i < 3; i++) {
//			Person.pos[i] += 0.5*u[2][i];
//			eye[i] += 0.5*u[2][i];
//		}
//	}
//
//	if (key == '+') {
//		angP3 = 210;
//	}
//
//	if (key == '-') {
//
//	}
//
//	glFinish();
//}

void KeyboardUp(unsigned char key, int x, int y)
{
	if (key == '+') {
		angP3 = 90;
		throwBall(my.body.pos, -PI / 180 * angx);
	}

	if (key == '-') {
		buildBox(my.body.pos, -PI / 180 * angx);
	}
	glFinish();
}

void Mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state)		MOUSE_LEFT = false;
		else		MOUSE_LEFT = true;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state)		MOUSE_RIGHT = false;
		else		MOUSE_RIGHT = true;
		break;
	}
	glFinish();
}

int oldx = 0;
int oldy = 0;
void Motion(int x, int y)
{
	int    i;
	float  ix[3], iy[3], iz[3], aX = 0;
	if (MOUSE_LEFT) {
		if (angx > 360.0) {
			aX -= 360.0;
			angx -= 360.0;
		}
		angx += (x - oldx);
		aX = (x - oldx);
		oldx = x;
		//
		rotateY(eyedirection[0], eyedirection[2], -PI / 180 * aX);
		rotateY(ahead[0], ahead[2], -PI / 180 * aX);
		my.rotation = -angx;
		//
		glFinish();
		glutPostRedisplay();
	}
}

/*---------------------------------------------------
* Main procedure which defines the graphics environment,
* the operation style, and the callback func's.
*/
void main(int argc, char **argv)
{
	/*-----Initialize the GLUT environment-------*/
	glutInit(&argc, argv);

	/*-----Depth buffer is used, be careful !!!----*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1000, 1000);
	glutCreateWindow("windmill");

	myinit();      /*---Initialize other state varibales----*/

	/*----Associate callback func's whith events------*/
	glutDisplayFunc(display);
	//glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutKeyboardFunc(my_quit);
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutTimerFunc(50, timerfun, 1);

	glutMainLoop();
}

