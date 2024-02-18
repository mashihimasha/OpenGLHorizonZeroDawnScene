#include <glut.h>
#include <math.h>
#include <SOIL2.h>
#include <stdio.h>
#include "headers/TextureLoader.h"
#include "headers/CampFire.h"
#include "headers/FireParticleSystem.h"

// Camera position
GLfloat camX = 0.0;
GLfloat camY = 0.0;
GLfloat camZ = 0.0;

// Object rotation and scene translation
double objR = 0.0;
double sceneX = 0.0;
double sceneY = 0.0;
double sceneZ = 0.0;
double rotateSceneY = 0.0;
double rotateSceneX = 0.0;

std::vector<GrassBlade> grassBlades;
std::vector<GrassBlade> grassBladesForPatch;

TextureLoader textureLoader;
FireParticleSystem fireParticleSystem;
CampFire campFire;

GLfloat vertices[][3] = {
	{1, 1, -1}, {1, 1, 1}, {-1, 1, 1}, {-1, 1, -1},
	{0, 2, 0} //Pyramid apex
};
GLfloat texCoord[][2] = {
	{0,0}, {0.4,1}, {1,0}
};
GLuint indices[] = {
	4, 2, 1,
	4, 2, 3,
	4, 3, 0,
	4, 1, 0
};

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	textureLoader.loadLandTexture();
	textureLoader.loadRockTexture();
	textureLoader.loadLogTexture();
	textureLoader.loadFireIconTexture();
	textureLoader.loadFireParticleTexture();
	textureLoader.loadSkyTexture();
	textureLoader.loadLeafTexture();
	textureLoader.loadGrassTexture();
	textureLoader.loadMountainTexture();
	textureLoader.loadTreeTexture();
	textureLoader.loadRustTexture();
}

void drawGrassField() {
	const int numRows = 30;
	const int numCols = 20;
	const float spacing = 2.2;
	const float bladeWidth = 0.5;
	const float bladeHeight = 10.0;
	const int numTranslations = 80;
	const float circleRadius = 250.0;

	campFire.generateGrassBlades(grassBlades, numRows, numCols, spacing, bladeWidth, bladeHeight);

	for (int i = 0; i <= numTranslations; ++i) {
		float angle = 2.0 * PI * i / numTranslations;
		float xTranslation = circleRadius * cos(angle);
		float zTranslation = circleRadius * sin(angle);

		glPushMatrix();
		glTranslated(xTranslation, 0.0, zTranslation);

		for (const auto& blade : grassBlades) {
			if (blade.active) {
				glPushMatrix();
				glTranslatef(blade.x, blade.y, blade.z);
				glRotatef(blade.rotationAngle, blade.rotationAxis, blade.rotationAxis, blade.rotationAxis);

				static GLuint grassBladeList = 0;
				if (grassBladeList == 0) {
					grassBladeList = glGenLists(1);
					glNewList(grassBladeList, GL_COMPILE);
					campFire.drawGrassBlade(blade.height, blade.width);
					glEndList();
				}

				glCallList(grassBladeList);

				glPopMatrix();
			}
		}

		glPopMatrix();
	}

}

void drawGrassPatch() {
	const int numRows = 35;
	const int numCols = 30;
	const float spacing = 0.8;
	const float bladeWidth = 0.2;
	const float bladeHeight = 12.0;

	campFire.generateGrassBlades(grassBladesForPatch, numRows, numCols, spacing, bladeWidth, bladeHeight);

	for (const auto& blade : grassBladesForPatch) {
		if (blade.active) {
			glPushMatrix();
			glTranslatef(blade.x, blade.y, blade.z);
			glRotatef(blade.rotationAngle, blade.rotationAxis, blade.rotationAxis, blade.rotationAxis);

			static GLuint grassBladeList = 0;
			if (grassBladeList == 0) {
				grassBladeList = glGenLists(1);
				glNewList(grassBladeList, GL_COMPILE);
				campFire.drawGrassBlade(blade.height, blade.width);
				glEndList();
			}

			glCallList(grassBladeList);

			glPopMatrix();
		}
	}
}

void drawMountain() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.mountainTexture);

	glColor3f(0.93, 0.74, 0.74);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);

	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_TEXTURE_2D);
}

void drawMountainRange(const double& xTranslation, const double& yTranslation, const double& zTranslation,
	const double& xScale, const double& yScale, const double& zScale) {
	glPushMatrix();
	glTranslated(xTranslation, yTranslation, zTranslation);
	glScaled(xScale, yScale, zScale);
	drawMountain();
	glPopMatrix();
}

void drawSceneWithLight() {
	glEnable(GL_DEPTH_TEST);

	campFire.setLightingCampFire();

	//draw sky dome
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.skyTexture);
	glPushMatrix();
	glRotated(170, 0.0, 1.0, 0.0);
	campFire.drawSky();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	/////////////////////////////////////////////////////////////////////////

	// Draw land with texture
	glBindTexture(GL_TEXTURE_2D, textureLoader.landTexture);
	campFire.drawLand();
	////////////////////////////////////////////////////////////////////////
	
	// draw mountains
	drawMountainRange(100.0, -60.0, -400.0, 100.0, 60.0, 60.0);
	drawMountainRange(20.0, -100.0, -500.0, 100.0, 100.0, 100.0);
	drawMountainRange(-30.0, -60.0, -400.0, 80.0, 60.0, 60.0);
	drawMountainRange(-90.0, -40.0, -400.0, 100.0, 40.0, 60.0);
	//////////////////////////////////////////////////////////////////////////
	
	//draw grass field
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.grassTexture);
	drawGrassField();
	/////////////////////////////////////////////////////////////////////////

	//reed patch
	glPushMatrix();
	glTranslated(30.0, 0.0, 8.0);
	glBindTexture(GL_TEXTURE_2D, textureLoader.logTexture);
	drawGrassPatch();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-50.0, 0.0, -8.0);
	glBindTexture(GL_TEXTURE_2D, textureLoader.logTexture);
	drawGrassPatch();
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	/////////////////////////////////////////////////////////////////////////


	//big rock
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.mountainTexture);

	//rock set 1
	glPushMatrix();
	glTranslated(5.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(1.0, 0.8, 1.0);
	glTranslated(50.0, 0.0, 20.0);
	glRotated(40, 0.0, 1.0, 0.0);
	campFire.drawBigRock();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.6, 0.5);
	glTranslated(80.0, 0.0, 60.0);
	glRotated(90, 0.0, 1.0, 0.0);
	campFire.drawBigRock();
	glPopMatrix();
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////

	//rock set 2
	glPushMatrix();
	glScaled(2.0, 2.0, 8.5);
	glTranslated(-115.0,0.0,-5.0);
	glRotated(180, 0.0, 0.0, 1.0);
	glPushMatrix();
	glScaled(1.0, 0.8, 1.0);
	glTranslated(50.0, 0.0, 20.0);
	glRotated(40, 0.0, 1.0, 0.0);
	campFire.drawBigRock();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.6, 0.5);
	glTranslated(80.0, 0.0, 60.0);
	glRotated(90, 0.0, 1.0, 0.0);
	campFire.drawBigRock();
	glPopMatrix();
	glPopMatrix();
    ////////////////////////////////////////////////////////////////////////////

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////

	//draw war machine
	float specRust[] = { 0.2, 0.1,0.0, 1.0 };
	float diffuseRust[] = { 0.0, 0.0,0.0, 1.0 };

	glPushMatrix();
	glScaled(2.5, 2.5, 2.5);
	glTranslated(-60.0, 6.5, 5.0);
	glRotated(120, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specRust);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseRust);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.rustTexture);
	campFire.drawWarMachine();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	
	//draw loot mark 
	campFire.drawLootLine();
	campFire.drawCircle(1.5, 32);
	//////////////////////////////////////////////////////////////////////////

	//draw fire icon
	glPushMatrix();
	glTranslatef(0.0, 25.5, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.fireIconTexture);
	campFire.displayFireIco();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	
	//start camp fire logs
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.logTexture);
	campFire.drawCampFire();
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////////////////////////

	//rock
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureLoader.rockTexture);
	campFire.drawCampfireSurroundRock(8.5);
	campFire.drawCampfireSurroundRock(8.8);
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////////////////////////
	
	//forest
	glEnable(GL_TEXTURE_2D);
	campFire.setTextures(textureLoader.leafTexture, textureLoader.treeTexture);
	glPushMatrix();
	campFire.drawForest();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//////////////////////////////////////////////////////////////////////////
	glDisable(GL_LIGHTING);

	//fire
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);			// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);
	fireParticleSystem.setLighting();
	glBindTexture(GL_TEXTURE_2D, textureLoader.fireParticleTexture);		

	glPushMatrix();
	fireParticleSystem.drawFire();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);								
	glPopMatrix();

	//////////////////////////////////////////////////////////////////////////

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glTranslated(camX, camY, camZ);
	glRotatef(rotateSceneX, 1.0, 0.0, 0.0);
	glRotatef(rotateSceneY, 0.0, 1.0, 0.0);
	//camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 0.0, 120.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glRotatef(objR, 0.0, 1.0, 0.0);
	glTranslated(0.0, -10.0, 0.0);
	drawSceneWithLight();
	glPopMatrix();

	glPopMatrix();
	glutPostRedisplay();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / static_cast<float>(1) : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
	gluPerspective(35.0, aspect_ratio, 1.0, 1000.0);
}

void keyboardSpecial(int key, int x, int y) {
	const float ROTATION_SPEED = 1.0f;

	switch (key) {
		case GLUT_KEY_UP: //Pitch camera up
			if (rotateSceneX > -90) {
				rotateSceneX--;
			}
			break;

		case GLUT_KEY_DOWN: //Pitch camera down upto ground level
			if (rotateSceneX < 0) {
				rotateSceneX++;
			}
			break;
		case GLUT_KEY_RIGHT: // rotate camera to the right (yaw)
			rotateSceneY += ROTATION_SPEED;
			break;

		case  GLUT_KEY_LEFT: // rotate camera to the left (yaw)
			rotateSceneY -= ROTATION_SPEED;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'l': // obj rotate clockwise
		objR++;
		break;

	case 'r': // obj rotate anti-clockwise
		objR--;
		break;
	case 'a': // move camera right
		camX++;
		break;

	case 'd': // move camera left
		camX--;
		break;

	case 'w': // move camera forward
		camZ++;
		break;

	case 's': // move camera backward
		camZ--;
		break;

	case ' ': // move camera up
		camY-= camY<=0.0?8.0:camY;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void animate(int value) {
	camY += camY >= 0.0 ? camY : 1.0;
	glutPostRedisplay();
	glutTimerFunc(5, animate, 0);
}

int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1080, 720);
	glutInitWindowPosition(145, 0);
	glutCreateWindow("Horizon ZeroDawn");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutTimerFunc(5, animate, 0);
	init();
	glutMainLoop();
	return 0;
}