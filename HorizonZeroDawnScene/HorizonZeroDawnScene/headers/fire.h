#pragma once

// Default Window 
#define WIN_WIDTH	640
#define WIN_HEIGHT	480

// Projection parameters
#define FOVY		20.0
#define ZNEAR_3D	1
#define ZFAR_3D	1000.0
#define ZNEAR_2D	-50.0
#define ZFAR_2D	50.0

// Shading mode : 0 Polygon, 1 Wireframe
#define SHADE_POLYGON 0		
#define SHADE_WIREFRAME 1

// Define number of vertex 
#define NUM_VERTEX_PER_FACE 3 // Triangle = 3, Quad = 4 

// Define Basic Structures
struct DEFINE_Point {
	float x;
	float y;
	float z;
};

struct DEFINE_RGBA {
	float r;
	float g;
	float b;
	float a;
};

typedef DEFINE_Point  DEFINE_Normal;

struct  DEFINE_UVcoord {

	float u;
	float v;
};

struct  DEFINE_Triangle {

	unsigned int v1;
	unsigned int v2;
	unsigned int v3;
	unsigned int n1;
	unsigned int n2;
	unsigned int n3;
	unsigned int t1;
	unsigned int t2;
	unsigned int t3;
};

struct  DEFINE_Quad {

	unsigned int v1;
	unsigned int v2;
	unsigned int v3;
	unsigned int v4;
	unsigned int n1;
	unsigned int n2;
	unsigned int n3;
	unsigned int n4;
	unsigned int t1;
	unsigned int t2;
	unsigned int t3;
	unsigned int t4;
};

