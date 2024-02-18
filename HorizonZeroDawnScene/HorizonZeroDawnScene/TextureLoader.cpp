#include "headers/TextureLoader.h"
#include <stdio.h>

// Constants for texture file paths
const char* LAND_TEXTURE_PATH = "img/land.jpg";
const char* LOG_TEXTURE_PATH = "img/log.jpg";
const char* ROCK_TEXTURE_PATH = "img/rock.jpg";
const char* FIRE_ICON_TEXTURE_PATH = "img/fire.png";
const char* FIRE_PARTICLE_TEXTURE_PATH = "img/particle.png";
const char* SKY_TEXTURE_PATH = "img/sky.jpg";
const char* LEAF_TEXTURE_PATH = "img/leaves.jpg";
const char* GRASS_TEXTURE_PATH = "img/grass.jpg";
const char* MOUNTAIN_TEXTURE_PATH = "img/mountain.png";
const char* TREE_TEXTURE_PATH = "img/tree_bark.jpg";
const char* RUST_TEXTURE_PATH = "img/rust.jpg";

TextureLoader::~TextureLoader() {
    // Clean up texture resources
    if (landTexture != 0) {
        glDeleteTextures(1, &landTexture);
    }

    if (logTexture != 0) {
        glDeleteTextures(1, &logTexture);
    }

    if (rockTexture != 0) {
        glDeleteTextures(1, &rockTexture);
    }

    if (fireIconTexture != 0) {
        glDeleteTextures(1, &fireIconTexture);
    }

    if (fireParticleTexture != 0) {
        glDeleteTextures(1, &fireParticleTexture);
    }

    if (skyTexture != 0) {
        glDeleteTextures(1, &skyTexture);
    }

    if (leafTexture != 0) {
        glDeleteTextures(1, &leafTexture);
    }

    if (grassTexture != 0) {
        glDeleteTextures(1, &grassTexture);
    }

    if (mountainTexture != 0) {
        glDeleteTextures(1, &mountainTexture);
    }

    if (treeTexture != 0) {
        glDeleteTextures(1, &treeTexture);
    }
}

// Error handling function
void handleTextureLoadingError(const char* textureType, const char* errorMessage) {
    printf("%s loading failed: %s\n", textureType, errorMessage);
}

// Generic function to load textures
GLuint loadTexture(const char* filePath, int flags) {
    GLuint texture = SOIL_load_OGL_texture(
        filePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        flags
    );

    if (!texture) {
        handleTextureLoadingError(filePath, SOIL_last_result());
    }

    return texture;
}

void TextureLoader::loadLandTexture() {
    landTexture = loadTexture(LAND_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadLogTexture() {
    logTexture = loadTexture(LOG_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadRockTexture() {
    rockTexture = loadTexture(ROCK_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadFireIconTexture() {
    fireIconTexture = loadTexture(FIRE_ICON_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}


void TextureLoader::loadFireParticleTexture() {
    fireParticleTexture = loadTexture(FIRE_PARTICLE_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadSkyTexture() {
    skyTexture = loadTexture(SKY_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadLeafTexture() {
    leafTexture = loadTexture(LEAF_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}


void TextureLoader::loadGrassTexture() {
    grassTexture = loadTexture(GRASS_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadMountainTexture() {
    mountainTexture = loadTexture(MOUNTAIN_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadTreeTexture() {
    treeTexture = loadTexture(TREE_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

void TextureLoader::loadRustTexture() {
    rustTexture = loadTexture(RUST_TEXTURE_PATH, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}