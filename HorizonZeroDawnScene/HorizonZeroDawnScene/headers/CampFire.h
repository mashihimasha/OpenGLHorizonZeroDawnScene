#pragma once
#include <glut.h>
#include <math.h>
#include <vector>

#define PI 3.14159265358979323846
#define MAX_BLADES 500

struct GrassBlade {
    bool active = false;
    float height = 0.0;
    float width = 0.0;
    float rotationAngle = 0.0;
    float rotationAxis = 0.0;
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
};

class CampFire {
public:
    GLuint texture1, texture2;

    void drawLog(float height);
    void drawCampLogSection(float height, float circleRadius);
    void drawCampFireSections(float height, float circleRadius, int numLogs);
    void drawCampFire();
    void drawRock();
    void drawCampfireSurroundRock(float circleRadius);
    void drawLootLine();
    void drawCircle(float radius, int n);
    void drawSky();
    void drawLand();
    void drawBigRock();
    void drawTree();
    void drawForest();
    void drawBranch(double baseRadius, double height);
    void drawLeaf();
    void drawGrassBlade(float height, float width);
    void drawWarMachine();
    void generateGrassBlades(std::vector<GrassBlade>& grassBlades, int numRows, int numCols, float spacing, float bladeWidth, float bladeHeight);
    void displayFireIco();
    void setTextures(GLuint tex1, GLuint tex2);
    void setLightingCampFire();

private:
    void setTranslate(int seed);
    int change = 0;
    int rotateY = 0;
    int bladeRotationAxisIndex = 0;
    int bladeRotationAngleIndex = 0;
    GrassBlade grassBlade[MAX_BLADES];
};