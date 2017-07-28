#include "Function.h"

int groundSize = 30;

void CreatGround() {
	int a;
	for (int i = 0;i<groundSize;i++) {
			for (int k = 0; k < groundSize; k++) {
				a = ground[i][k];
				glPushMatrix();
				glColor3f(0.1, 0.5, 0.1);
				glScalef(10, 10, 10);
				glTranslated(i*1- groundSize/2, a, k*1- groundSize/2);
				draw_cube();
				glPopMatrix();
			}
	}
	/*for (int i = 0; i<groundSize; i++) {
			for (int k = 0; k < groundSize ; k++) {
				for (int j = 0; j<20; j++) {
					a = ground[i][k];
					if (j < a) {
						glPushMatrix();
						glTranslated(i * 1 - groundSize / 2, j, k * 1 - groundSize / 2);
						draw_cube();
						glPopMatrix();
				}
			}
		}
	}*/
}

void fixground(int a) {
	int howmuch[100];
	int x=0;
	
	for (int i = 0; i<groundSize; i++) {
		for (int j = 0; j<groundSize; j++) {
			if (ground[i][j]==a) {
				x++;
			}
		}
		howmuch[i] = x;
		x = 0;
		//printf("%d\n", howmuch[i]);
	}
}

void recordGround() {
	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < groundSize; i++) {
			for (int j = 0; j < groundSize; j++) {
				if (k == 0) {
					terrain[i][k][j].ONOROFF = 1;
				}
				if (k == 1) {
					if (ground[i][j] == 1) {
						terrain[i][k][j].ONOROFF = 1;
					}
				}
				
			}
		}
	}
}