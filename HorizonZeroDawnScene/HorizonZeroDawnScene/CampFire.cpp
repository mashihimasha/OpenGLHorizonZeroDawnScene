#include "headers/CampFire.h"
#include <glut.h>
#include <random>

#define PI 3.14159265358979323846
#define MAX_DISTANCE 800

void CampFire::drawLog(float height) {

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);


	//log body
	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);

	//log
	glColor3f(0.51, 0.36, 0.30);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluCylinder(quad, 1.0, 1.0, height, 20, 10);

	//log closing disk lower
	glColor3f(0.20, 0.6, 0.47);
	gluQuadricOrientation(quad, GLU_INSIDE);
	gluDisk(quad, 0.0, 1.0, 20, 1);
	glPopMatrix();

	//log closing disk upper
	glPushMatrix();
	glColor3f(0.20, 0.6, 0.47);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	glTranslatef(0.0, height, 0.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	gluDisk(quad, 0.0, 1.0, 20, 1);
	glPopMatrix();

	gluDeleteQuadric(quad);
}

void CampFire::drawCampLogSection(float height, float circleRadius) {
	const int numLogs = 2; // Number of logs in the circular arrangement

	for (int i = 0; i < numLogs; ++i) {
		float angle = (360.0 / numLogs) * i;
		float cosAngle = cos(angle * PI / 180.0);
		float sinAngle = sin(angle * PI / 180.0);

		float x = circleRadius * cosAngle;
		float y = circleRadius * sinAngle;

		glPushMatrix();
		glTranslatef(x, 0.0, y);

		float rot_angle = (i == 0) ? 20.0 : -20.0;
		glRotated(rot_angle, 0.0, 0.0, 1.0);

		drawLog(height);

		glPopMatrix();
	}
}

void CampFire::drawCampFireSections(float height, float circleRadius, int numLogs) {
	for (int i = 0; i < numLogs; ++i) {


		float angle = (360.0 / numLogs) * i;
		float x = circleRadius * cos(angle * PI / 180.0);
		float y = circleRadius * sin(angle * PI / 180.0);


		glPushMatrix();
		glRotatef(angle, 0.0, 1.0, 0.0);

		glPushMatrix();
		drawCampLogSection(height, circleRadius);
		glPopMatrix();

		glPopMatrix();

	}
}

void CampFire::drawCampFire() {
	drawCampFireSections(16.0, 8.0, 12);

	glPushMatrix();
	glRotatef(45, 0.0, 1.0, 0.0);
	drawCampFireSections(15.0, 8.0, 8);
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0.0, 1.0, 0.0);
	drawCampFireSections(12.0, 8.1, 6);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	drawCampFireSections(10.0, 8.2, 8);
	glPopMatrix();
}

void CampFire::drawRock() {

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);

	glColor3f(0.37, 0.35, 0.42);
	gluSphere(quad, 1.0, 32, 32);

	gluDeleteQuadric(quad);

}

void CampFire::drawCampfireSurroundRock(float circleRadius) {
	const int numRocks = 20; // Number of logs in the circular arrangement

	for (int i = 0; i < numRocks; ++i) {

		float angle = (360.0 / numRocks) * i;
		float x = circleRadius * cos(angle * PI / 180.0);
		float y = circleRadius * sin(angle * PI / 180.0);

		glPushMatrix();
		glTranslatef(x, 0.0, y);
		glScaled(2.0, 1.0, 2.0);
		drawRock();
		glPopMatrix();

	}
}

void CampFire::drawLootLine() {

	glLineWidth(1.2);

	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 24.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
}

void CampFire::drawCircle(float radius, int n) {

	glLineWidth(1.3);
	glPushMatrix();
	glTranslatef(0.0, 25.5, 0.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i <= n; ++i) {
		float angle = 2 * PI * i / n;
		float x = radius * cos(angle);
		float y = radius * sin(angle);

		// Calculate the normal for each vertex
		glNormal3f(x, 0.0f, y);

		glVertex2d(x, y);  // Vertex i
	}
	glEnd();
	glPopMatrix();

}

void CampFire::displayFireIco() {
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.5f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.5f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.5f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.5f, 1.0f);
	glEnd();
	glDisable(GL_BLEND);
	
}

void CampFire::drawSky() {
	glBegin(GL_QUADS);
	glColor3f(0.14, 0.58, 0.75);
	for (int i = 0; i < 180; i += 10) {
		for (int j = 0; j < 360; j += 10) {
			// Convert degrees to radians
			double theta1 = i * PI / 180;
			double theta2 = (i + 10) * PI / 180;
			double phi1 = j * PI / 180;
			double phi2 = (j + 10) * PI / 180;

			// Define vertices and corresponding texture coordinates
			double x1 = MAX_DISTANCE * sin(theta1) * cos(phi1);
			double y1 = MAX_DISTANCE * sin(theta1) * sin(phi1);
			double z1 = MAX_DISTANCE * cos(theta1);

			double x2 = MAX_DISTANCE * sin(theta1) * cos(phi2);
			double y2 = MAX_DISTANCE * sin(theta1) * sin(phi2);
			double z2 = MAX_DISTANCE * cos(theta1);

			double x3 = MAX_DISTANCE * sin(theta2) * cos(phi2);
			double y3 = MAX_DISTANCE * sin(theta2) * sin(phi2);
			double z3 = MAX_DISTANCE * cos(theta2);

			double x4 = MAX_DISTANCE * sin(theta2) * cos(phi1);
			double y4 = MAX_DISTANCE * sin(theta2) * sin(phi1);
			double z4 = MAX_DISTANCE * cos(theta2);


			// Calculate texture coordinates based on the current angles
			double u1 = static_cast<double>(j) / 360.0;
			double v1 = (static_cast<double>(i) / 180.0 + 0.5);

			double u2 = static_cast<double>(j + 10) / 360.0;
			double v2 = (static_cast<double>(i) / 180.0 + 0.5);

			double u3 = static_cast<double>(j + 10) / 360.0;
			double v3 = (static_cast<double>(i + 10) / 180.0) + 0.5;

			double u4 = static_cast<double>(j) / 360.0;
			double v4 = (static_cast<double>(i + 10) / 180.0) + 0.5;

			// Calculate normals based on vertex positions
			double nx1 = -x1 / MAX_DISTANCE;
			double ny1 = -y1 / MAX_DISTANCE;
			double nz1 = -z1 / MAX_DISTANCE;

			double nx2 = -x2 / MAX_DISTANCE;
			double ny2 = -y2 / MAX_DISTANCE;
			double nz2 = -z2 / MAX_DISTANCE;

			double nx3 = -x3 / MAX_DISTANCE;
			double ny3 = -y3 / MAX_DISTANCE;
			double nz3 = -z3 / MAX_DISTANCE;

			double nx4 = -x4 / MAX_DISTANCE;
			double ny4 = -y4 / MAX_DISTANCE;
			double nz4 = -z4 / MAX_DISTANCE;

			// Draw each quad with corrected texture coordinates
			glTexCoord2d(u1, v1);
			glNormal3d(nx1, ny1, nz1);
			glVertex3d(x1, y1, z1);

			glTexCoord2d(u2, v2);
			glNormal3d(nx2, ny2, nz2);
			glVertex3d(x2, y2, z2);

			glTexCoord2d(u3, v3);
			glNormal3d(nx3, ny3, nz3);
			glVertex3d(x3, y3, z3);

			glTexCoord2d(u4, v4);
			glNormal3d(nx4, ny4, nz4);
			glVertex3d(x4, y4, z4);
		}
	}

	glEnd();
}

void CampFire::drawLand() {

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glColor3f(0.95, 0.73, 0.24);

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);

	glRotated(-90, 1.0, 0.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	gluPartialDisk(quad, 0.0, MAX_DISTANCE, 20, 1, 0, 360);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void CampFire::drawBigRock() {

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);

	glColor3f(0.37, 0.35, 0.42);
	gluSphere(quad, 20.0, 32, 32);
	gluDeleteQuadric(quad);

}

void CampFire::drawGrassBlade(float height, float width) {

	glBegin(GL_POLYGON);
	glColor3f(0, 0.2, 0); // Green color

	// Set normals
	glNormal3f(0.0, 0.0, 1.0);

	// Set texture coordinates
	glTexCoord2f(0.0, 0.0);
	glVertex3f(width / 2, height, 0.0);

	glTexCoord2f(0.5, 0.0);
	glVertex3f(0.0, 0.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(width, 0.0, 0.0);

	glTexCoord2f(1.0, 0.5);
	glVertex3f(width / 2, 0.0, 0.0);

	glEnd();
}

void CampFire::generateGrassBlades(std::vector<GrassBlade>& grassBlades, int numRows, int numCols, float spacing, float bladeWidth, float bladeHeight) {
	grassBlades.clear(); // Clear existing grass blades

	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			GrassBlade blade;

			bladeRotationAxisIndex = int(rand() % 6);
			bladeRotationAngleIndex = int(rand() % 9);

			float rotationAxis[] = { 1.0, 1.0, 1.0, -1.0,-1.0,-1.0 };
			float rotationAngle[] = { 5.0, 10.0, 5.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0 };

			blade.active = true;
			blade.height = bladeHeight;
			blade.width = bladeWidth;
			blade.rotationAngle += rotationAngle[bladeRotationAngleIndex];
			blade.rotationAxis += rotationAxis[bladeRotationAxisIndex];
			blade.x = j * spacing;
			blade.y = 0.0;
			blade.z = i * spacing;

			grassBlades.push_back(blade);
		}
	}

}

void CampFire::drawLeaf() {
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glColor3f(0.5, 0.0, 0.0);
	GLUquadric* quad_leaf = gluNewQuadric();
	gluQuadricTexture(quad_leaf, GL_TRUE);
	glRotated(-90, 1.0, 0.0, 0.0);
	glNormal3f(0.0, 0.0, -1.0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	gluDisk(quad_leaf, 0.0, 4.0, 20, 4);
	glPopMatrix();
}

void CampFire::drawBranch(double baseRadius, double height) {
	glPushMatrix();

	glTranslated(0.0, height, 0.0);
	glRotated(30.0, 0.0, 0.0, 1.0);
	glRotated(-90, 1.0, 0.0, 0.0);

	glPushMatrix();
	GLUquadric* branchQuad = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture2);
	gluQuadricTexture(branchQuad, GL_TRUE);
	// Draw the branch
	glColor3f(0.37, 0.35, 0.42);
	glNormal3f(0, 0, -1);
	gluCylinder(branchQuad, baseRadius, baseRadius / 2.0, height / 2.0, 32, 32);
	gluDeleteQuadric(branchQuad);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.5, height / 2);
	drawLeaf();
	glPopMatrix();

	glPopMatrix();

}

void CampFire::drawTree() {

	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	GLUquadric* quad_tree = gluNewQuadric();
	gluQuadricTexture(quad_tree, GL_TRUE);

	glColor3f(0.37, 0.35, 0.42);
	glNormal3f(0, 0, -1);

	glBindTexture(GL_TEXTURE_2D, texture2);
	gluCylinder(quad_tree, 3.0, 2.0, 40.0, 32, 32);

	gluDeleteQuadric(quad_tree);
	glPopMatrix();

	//draw huge leaves
	glPushMatrix();
	glTranslated(0.0, 45.0, 0.0);
	glScaled(2.0, 2.5, 2.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawLeaf();
	glPopMatrix();


	// draw branches
	glPushMatrix();
	glTranslated(0.0, -2.0, 0.0);
	drawBranch(0.5, 25.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 4.0, 0.0);
	drawBranch(0.5, 25.0);
	glPopMatrix();

	glPushMatrix();
	glRotated(170,0.0, 1.0, 0.0);
	drawBranch(0.5, 25.0);
	glPopMatrix();

	glPushMatrix();
	glScaled(1.0, 0.8, 1.0);
	glTranslated(0.0, -1.5, 0.0);
	glRotated(170, 0.0, 1.0, 0.0);
	drawBranch(0.5, 25.0);
	glPopMatrix();

}

void CampFire::setTextures(GLuint tex1, GLuint tex2) {
	texture1 = tex1;
	texture2 = tex2;
}

void CampFire::setTranslate(int seed) {
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution(1, 10);
	change = distribution(generator);
}

void CampFire::drawForest() {
	glPushMatrix();
	const double startX = -250.0;
	const double endX = 230.0;
	const double startZ = 200.0;
	const double endZ = 300.0;
	double spacingX = 0.0;
	double spacingZ = 0.0;
	double rotateY = 0.0;

	if (change <= 1) {
		spacingX = 40.0;
		spacingZ = 40.0;
		rotateY = 40;
	}
	else if (change <= 4) {
		spacingX = 40.0;
		spacingZ = 60.0;
		rotateY = 80;
	}
	else if (change > 5) {
		spacingX = 40.0;
		spacingZ = 70.0;
		rotateY = 190;
	}

	for (double z = startZ; z <= endZ; z += spacingZ) {
		for (double x = startX; x <= endX; x += spacingX) {
			glPushMatrix();
			glTranslated(x, 0.0, z);
			glRotated(rotateY, 0.0, 1.0, 0.0);
			drawTree();
			glPopMatrix();
			setTranslate(spacingX + x);
		}
	}
	glPopMatrix();
}

void CampFire::drawWarMachine() {
	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);

	glColor3f(0.1, 0.007, 0.0);
	glPushMatrix();
	glScaled(1.5, 0.8, 1.5);
	gluSphere(quad,4.0, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glScaled(3.5, 1.2, 3.0);
	glTranslated(0.0, -3.2, 0.0);
	gluSphere(quad, 4.0, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-11.0, 2.2, 0.0);
	glRotated(90, 0.0, 1.0, 0.0);
	gluQuadricTexture(quad, GL_TRUE);
	gluCylinder(quad, 0.45, 0.45, 10.0, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-11.0, 2.2, -1.5);
	glRotated(90, 0.0, 1.0, 0.0);
	gluCylinder(quad, 0.45, 0.45, 10.0, 32, 32);
	glPopMatrix();
	gluDeleteQuadric(quad);

}

void CampFire::setLightingCampFire() {
	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Set lighting intensity and color
	GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight[] = { 1.0, 0.6, 0.6, 1.0 };  // Pinkish hue
	GLfloat qaSpecularLight[] = { 1.0, 0.8, 0.8, 1.0 };  // Light pinkish hue


	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	GLfloat qaLightPosition0[] = { 300.0, 10.0, -200.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	GLfloat qaLightPosition1[] = { 2.0, 100.0, -100.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

	glShadeModel(GL_SMOOTH);

	GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
	glMateriali(GL_FRONT, GL_SHININESS, 128.0);

}