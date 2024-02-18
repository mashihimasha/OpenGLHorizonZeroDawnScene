#pragma once
#include <glut.h>
#include <SOIL2.h>

class TextureLoader {
public:
    ~TextureLoader();

    GLuint landTexture, logTexture, rockTexture, fireIconTexture, fireParticleTexture, skyTexture, leafTexture, grassTexture, mountainTexture, treeTexture, rustTexture;

    void loadLandTexture();
    void loadLogTexture();
    void loadRockTexture();
    void loadFireIconTexture();
    void loadFireParticleTexture();
    void loadSkyTexture();
    void loadLeafTexture();
    void loadGrassTexture();
    void loadMountainTexture();
    void loadTreeTexture();
    void loadRustTexture();
};