#include "Function.h"

float  global_ambient[] = { 0.1, 0.1, 0.4, 1.0 };

 unsigned int   textName[3];
 unsigned int   skybox[6];
 unsigned char star[64][64][4];
 unsigned char textures[10];
 int width = 1000, height = 1000;
int ground[30][30];
struct human my;

char *fileName[1] = { "skybox_px.bmp" };

//球的位置
struct ball balls;

struct cube terrain[30][10][30];
struct Monster monster[10];

void  humaninit() {
	my.body.x = 0;
	my.body.y = 15;
	my.body.z = 0;
	my.body.L = 5;
	my.body.W = 2.5;
	my.body.H = 8;
	my.rotation = 0;
}



void Monsterinit() {
	int xxx, yyy, zzz;
	for (int i = 0; i<10; i++) {
		monster[i].humanmonster.body.x = rand() % 299 - 150;
		monster[i].humanmonster.body.y = 15;
		monster[i].humanmonster.body.z = rand() % 299 - 150;
		monster[i].humanmonster.rotation = rand() % 90;
		monster[i].humanmonster.body.L = 5;
		monster[i].humanmonster.body.W = 2.5;
		monster[i].humanmonster.body.H = 8;

		monster[i].humanmonster.vec_y = 6;

		xxx = (monster[i].humanmonster.body.x + 155) / 10;
		zzz = (monster[i].humanmonster.body.z + 155) / 10;
		ground[xxx][zzz] = 0;
	}
}

unsigned char *LoadBitmapFile(char *fileName, BITMAPINFO *bitmapInfo)
{
	FILE               *fp;
	BITMAPFILEHEADER   bitmapFileHeader;   // Bitmap file header 
	unsigned char       *bitmapImage;      // Bitmap image data 
	unsigned int      lInfoSize;         // Size of information 
	unsigned int      lBitSize;         // Size of bitmap 

	unsigned char change;
	int pixel;
	int p = 0;

	fp = fopen(fileName, "rb");
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);         //讀取 bitmap header 

	lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);   //Info的size 
	fread(bitmapInfo, lInfoSize, 1, fp);


	lBitSize = bitmapInfo->bmiHeader.biSizeImage;                  //配置記憶體 
	bitmapImage = new BYTE[lBitSize];
	fread(bitmapImage, 1, lBitSize, fp);                        //讀取影像檔 

	fclose(fp);

	//此時傳回bitmapImage的話，顏色會是BGR順序，下面迴圈會改順序為RGB 
	pixel = (bitmapInfo->bmiHeader.biWidth)*(bitmapInfo->bmiHeader.biHeight);

	for (int i = 0; i < pixel; i += 1, p += 3)
	{
		//交換bitmapImage[p]和bitmapImage[p+2]的值 
		change = bitmapImage[p];
		bitmapImage[p] = bitmapImage[p + 2];
		bitmapImage[p + 2] = change;
	}

	return bitmapImage;
}

void texture() {
	int width2;
	int height2;
	unsigned char *image;
	BITMAPINFO bmpinfo;

	image = LoadBitmapFile("Asset/aa.bmp", &bmpinfo);
	width2 = bmpinfo.bmiHeader.biWidth;
	height2 = bmpinfo.bmiHeader.biHeight;

	glBindTexture(GL_TEXTURE_2D, textName[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_TEXTURE_BORDER_COLOR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_TEXTURE_BORDER_COLOR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	char * picS[6] = { "Asset/skybox/txStormydays_front.bmp" ,
		"Asset/skybox/txStormydays_right.bmp" ,
		"Asset/skybox/txStormydays_left.bmp" ,
		"Asset/skybox/txStormydays_back.bmp" ,
		"Asset/skybox/txStormydays_up.bmp" ,
		"Asset/skybox/txStormydays_down.bmp" };

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(6, skybox);
	for (int i = 0; i < 6; i++) {

		image = LoadBitmapFile(picS[i], &bmpinfo);
		width = bmpinfo.bmiHeader.biWidth;
		height = bmpinfo.bmiHeader.biHeight;

		glBindTexture(GL_TEXTURE_2D, skybox[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_TEXTURE_BORDER_COLOR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_TEXTURE_BORDER_COLOR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	}
}

void  myinit()
{
	//ground
	for (int i=0;i<groundSize;i++) {
		for (int j=0;j<groundSize;j++) {
			if (rand()%2==0) {
				ground[i][j] = 1;
			}
		}
	}
	ground[groundSize/2][groundSize / 2] = 0;

	//人的座標
	humaninit();
	//怪物的座標
	Monsterinit();
	//計入3為座標
	recordGround();

	texture();
	//讀入圖片+texture mapping
	
	
	

	srand(time(NULL));

	glClearColor(0.0, 0.0, 0.0, 1.0);      /*set the background color BLACK */
										   /*Clear the Depth & Color Buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	//光的顏色
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);  /*Enable depth buffer for shading computing */
	glEnable(GL_NORMALIZE);   /*Enable mornalization  */

	float light0_amb[4] = { 0.0,0.0,0.0,1 };
	float light0_dif[4] = { 1.0,1.0,1.0,1 };
	float light0_spe[4] = { 0.3,0.3,0.3,1 };
	float light0_dir[4] = { 0, 100, 500, 100.0 };
	glEnable(GL_LIGHTING);    /*Enable lighting effects */
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_dir);

	glEnable(GL_COLOR_MATERIAL);


	float light1_dif[4] = { 1.0,1.0,1.0,1 };
	float light1_dir[4] = { 0, 0, 200, 0.0 };
	//glEnable(GL_LIGHTING);    /*Enable lighting effects */
	//glEnable(GL_LIGHT1);      /*Turn on light0 */
	//						  /*-----Define light0 ---------*/
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 360);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_dif);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light0_spe);
	//glLightfv(GL_LIGHT0, GL_POSITION, light1_dir);
							  /*-----Define some global lighting status -----*/
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); /* local viewer */
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); /*global ambi


															/*-----Enable face culling -----*/
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

}

void timerfun(int a) {
	display();
	glutTimerFunc(30, timerfun, 1);
}

void my_reshape(int w, int h)
{

}

