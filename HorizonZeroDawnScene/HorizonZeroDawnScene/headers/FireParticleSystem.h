#pragma once
#include <glut.h>

// Default Window 
#define WIN_WIDTH	640
#define WIN_HEIGHT	480

#define MAX_PARTICLES 10000

// Projection parameters
#define FOVY		20.0
#define ZNEAR_3D	1
#define ZFAR_3D	1000.0

struct Particle {
    bool active; //active (yes/no)
    float life;  //particle life
    float fade;  //fade speed
    float r;     //red
    float g;     //green
    float b;     //blue
    float x;     //x-position
    float y;     //y-position
    float z;     //z-position
    float xi;    //x-direction
    float yi;    //y-direction
    float zi;    //z-direction
    float xg;    //x-gravity
    float yg;    //y-gravity
    float zg;    //z-gravity
};

class FireParticleSystem {
public:
    FireParticleSystem();
    ~FireParticleSystem();

    void init();
    void setLighting();
    void drawFire();

private:
    GLuint g_mainWnd;
    GLuint g_nWinWidth;
    GLuint g_nWinHeight;

    GLuint loop;

    GLfloat white[3];
    GLfloat blue[3];
    GLfloat yellow[3];
    GLfloat orange[3];
    GLfloat red[3];

    float posX;
    float posY;
    float posZ;

    float gravX;
    float gravY;
    float gravZ;

    Particle particle[MAX_PARTICLES];
};