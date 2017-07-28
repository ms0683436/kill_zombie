#include <iostream> 
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h> 
#include<vector>
#define   TSIZE  64
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5
using namespace std;

extern int width , height ;
//texture
extern unsigned int   textName[];
extern unsigned int   skybox[];

extern unsigned char *image;

extern BITMAPINFO bmpinfo;
extern unsigned char textures[10];
//地板
extern int groundSize;
extern int ground[30][30];
//方塊
struct cube {
	float pos[3] = { 0,0,0, }, x = 0, y = 0, z = 0;//位置
	float L = 1, W = 1, H = 1;//長寬高
	float R = 1, Y = 1, P = 1;
	float ONOROFF;
};

struct Particle {
	float pos[3];
	float color[3];
	float vel[3];
	float radius = 2;
	float ONOROFF;
};

struct bag {
	vector<Particle> particlesBall;
	vector<Particle> particlesBox;
};
//人
struct human {
	cube head, leftHend, rightHend, body, leftLeg, rightLeg;
	float vec_x = 0;
	float vec_y = 0;
	float vec_z = 0;
	float rotation;
	bag myBag;
};
extern struct human my;
extern struct cube terrain[30][10][30];

//球
struct ball {
	float x = 0, y = 0, z = 0;//位置
	float x_speed, y_speed, z_speed;
	float radius;
	float ONOROFF;
};
//extern struct ball balls;

//怪物
struct Monster {
	human humanmonster;
	int jump = 0;
	int life = 0;
	float ONOROFF;
};

extern struct Monster monster[10];

//眼睛
extern float  eye[3] ;
extern float  eyedirection[3] ;
void display();
void my_quit(unsigned char, int, int);
void my_reshape(int, int);
void  myinit();
void timerfun(int);
void draw_cube();
void drawSkybox(double D);
void CreatGround();
void recordGround();
void fixground(int);
