#include "Function.h"

//cube information
float  points[][3] = { { -0.5, -0.5, -0.5 },{ 0.5, -0.5, -0.5 },
{ 0.5, 0.5, -0.5 },{ -0.5, 0.5, -0.5 },
{ -0.5, -0.5, 0.5 },{ 0.5, -0.5, 0.5 },
{ 0.5, 0.5, 0.5 },{ -0.5, 0.5, 0.5 } };
/* face of box, each face composing of 4 vertices */
int    face[][4] = { { 0, 3, 2, 1 },{ 0, 1, 5, 4 },{ 1, 2, 6, 5 },
{ 4, 5, 6, 7 },{ 2, 3, 7, 6 },{ 0, 4, 7, 3 } };

float  normals[6][3] = { { 0.0,0.0,-1.0 },{ 0.0,-1.0,0.0 },{ 1.0,0.0,0.0 },
{ 0.0,0.0,1.0 },{ 0.0,1.0,0.0 },{ -1.0,0.0,0.0 } };

void draw_cube()
{
	int    i;
	float  range;

	//texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textName[0]);

	for (i = 0; i<6; i++) {
		range = 1.0;
		glNormal3fv(normals[i]);
		glBegin(GL_POLYGON);  /* Draw the face */
		glTexCoord2f(0.0, 0.0);     glVertex3fv(points[face[i][0]]);
		glTexCoord2f(0.0, range);   glVertex3fv(points[face[i][1]]);
		glTexCoord2f(range, range); glVertex3fv(points[face[i][2]]);
		glTexCoord2f(range, 0.0);   glVertex3fv(points[face[i][3]]);
		glEnd();
	}
}

void drawSkybox(double D)
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	/* Sides */
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_RIGHT]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-D, -D, -D);
	glTexCoord2f(1, 0); glVertex3f(+D, -D, -D);
	glTexCoord2f(1, 1); glVertex3f(+D, +D, -D);
	glTexCoord2f(0, 1); glVertex3f(-D, +D, -D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_FRONT]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(+D, -D, -D);
	glTexCoord2f(1, 0); glVertex3f(+D, -D, +D);
	glTexCoord2f(1, 1); glVertex3f(+D, +D, +D);
	glTexCoord2f(0, 1); glVertex3f(+D, +D, -D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_LEFT]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(+D, -D, +D);
	glTexCoord2f(1, 0); glVertex3f(-D, -D, +D);
	glTexCoord2f(1, 1); glVertex3f(-D, +D, +D);
	glTexCoord2f(0, 1); glVertex3f(+D, +D, +D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_BACK]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-D, -D, +D);
	glTexCoord2f(1, 0); glVertex3f(-D, -D, -D);
	glTexCoord2f(1, 1); glVertex3f(-D, +D, -D);
	glTexCoord2f(0, 1); glVertex3f(-D, +D, +D);
	glEnd();

	/* Top and Bottom */
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_UP]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-D, +D, -D);
	glTexCoord2f(1, 0); glVertex3f(+D, +D, -D);
	glTexCoord2f(1, 1); glVertex3f(+D, +D, +D);
	glTexCoord2f(0, 1); glVertex3f(-D, +D, +D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, skybox[SKY_DOWN]);
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 1); glVertex3f(+D, -D, -D);
	glTexCoord2f(0, 1); glVertex3f(-D, -D, -D);
	glTexCoord2f(0, 0); glVertex3f(-D, -D, +D);
	glTexCoord2f(1, 0); glVertex3f(+D, -D, +D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}