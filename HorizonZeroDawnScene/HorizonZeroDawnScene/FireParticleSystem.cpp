#include "headers/FireParticleSystem.h"
#include <SOIL2.h>
#include <iostream>

float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
float	zoom = 0.0f;				// Used To Zoom Out

using namespace std;

FireParticleSystem::FireParticleSystem(){
    init();
    g_nWinWidth = WIN_WIDTH;
    g_nWinHeight = WIN_HEIGHT;

    posX = 0.0f;
    posY = 1.3f;
    posZ = 0.0f;

    gravX = 0.0f;
    gravY = 0.0f;
    gravZ = 0.0f;

    white[0] = 1.0f; white[1] = 1.0f; white[2] = 1.0f;
    blue[0] = 0.0f; blue[1] = 0.0f; blue[2] = 1.0f;
    yellow[0] = 1.0f; yellow[1] = 1.0f; yellow[2] = 0.0f;
    orange[0] = 1.0f; orange[1] = 0.5f; orange[2] = 0.0f;
    red[0] = 1.0f; red[1] = 0.1f; red[2] = 0.0f;
}

FireParticleSystem::~FireParticleSystem() {

}

void FireParticleSystem::init() {
    glShadeModel(GL_SMOOTH);							
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				
    glClearDepth(1.0f);									
    glDisable(GL_DEPTH_TEST);

    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        particle[loop].active = true;
        particle[loop].life = 1.0f;
        particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;
        particle[loop].r = white[0];
        particle[loop].g = white[1];
        particle[loop].b = white[2];
        particle[loop].xi = float((rand() % 50) - 25.0f) * 10.0f;
        particle[loop].yi = float((rand() % 50) - 25.0f) * 10.0f;
        particle[loop].zi = float((rand() % 50) - 25.0f) * 10.0f;
        particle[loop].xg = 0.0f;
        particle[loop].yg = 0.8f;
        particle[loop].zg = 0.0f;
    }

}

void FireParticleSystem::setLighting() {
    float direction[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    float diffintensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glLightfv(GL_LIGHT2, GL_POSITION, direction);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffintensity);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);

    glEnable(GL_LIGHT2);
}

void FireParticleSystem::drawFire() {
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        if (particle[loop].active) {
            float x = particle[loop].x;
            float y = particle[loop].y;
            float z = particle[loop].z + zoom;

            glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);

            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z);
            glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z);
            glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z);
            glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z);
            glEnd();

            particle[loop].x += particle[loop].xi / (400.0f);
            particle[loop].y += particle[loop].yi / (1100.0f);
            particle[loop].z += particle[loop].zi / (400.0f);

            if ((particle[loop].x > posX) && (particle[loop].y > (0.1 + posY))) {
                particle[loop].xg = -0.3f;
            }
            else if ((particle[loop].x < posX) && (particle[loop].y > (0.1 + posY))) {
                particle[loop].xg = 0.3f;
            }
            else {
                particle[loop].xg = 0.0f;
            }

            particle[loop].xi += (particle[loop].xg + gravX);
            particle[loop].yi += (particle[loop].yg + gravY);
            particle[loop].zi += (particle[loop].zg + gravZ);
            particle[loop].life -= particle[loop].fade;

            if (particle[loop].life < 0.0f) {
                particle[loop].life = 1.0f;
                particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;
                particle[loop].x = posX;
                particle[loop].y = posY;
                particle[loop].z = posZ;
                particle[loop].xi = xspeed + float((rand() % 60) - 30.0f);
                particle[loop].yi = yspeed + float((rand() % 60) - 30.0f);
                particle[loop].zi = float((rand() % 60) - 30.0f);
                particle[loop].r = white[0];
                particle[loop].g = white[1];
                particle[loop].b = white[2];
            }
            else if (particle[loop].life < 0.4f) {
                particle[loop].r = red[0];
                particle[loop].g = red[1];
                particle[loop].b = red[2];
            }
            else if (particle[loop].life < 0.6f) {
                particle[loop].r = orange[0];
                particle[loop].g = orange[1];
                particle[loop].b = orange[2];
            }
            else if (particle[loop].life < 0.75f) {
                particle[loop].r = yellow[0];
                particle[loop].g = yellow[1];
                particle[loop].b = yellow[2];
            }
            else if (particle[loop].life < 0.85f) {
                particle[loop].r = blue[0];
                particle[loop].g = blue[1];
                particle[loop].b = blue[2];
            }
        }
    }
}
