#ifndef __MD2_H
#define __MD2_H

/*
	MD2.H

	The CMD2Model class

	Author: Kevin Hawkins
	Date: 3/29/2001
	Description: The CMD2Model class loads, animates, and displays
			   Quake 2 (TM id Software) .MD2 model files. 

*/

#include <windows.h>			// standard Windows app include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <gl/gl.h>				// standard OpenGL include
//#include <gl/glu.h>				// OpenGL utilties

#include <vector>

//#include "object.h"
//#include "texture.h"
//#include "vector.h"

#define MAX_FRAMES 512

/*
	Vector Functionality
*/
// a single vertex
typedef struct
{
   float point[3];
} vector_t;

vector_t operator-(vector_t a, vector_t b);
vector_t operator*(float f, vector_t b);
vector_t operator/(vector_t a, vector_t b);
vector_t operator+(vector_t a, vector_t b);

void CalculateNormal( float *p1, float *p2, float *p3 );


/* 
	MD2 Model Functionality
*/


// texture coordinate
typedef struct
{
   float s;
   float t;
} texCoord_t;

// texture coordinate index
typedef struct
{
   short s;
   short t;
} stIndex_t;

// info for a single frame point
typedef struct
{
   unsigned char v[3];
   unsigned char normalIndex;	// not used
} framePoint_t;

// information for a single frame
typedef struct
{
   float scale[3];
   float translate[3];
   char name[16];
   framePoint_t fp[1];
} frame_t;

// data for a single triangle
typedef struct
{
   unsigned short meshIndex[3];		// vertex indices
   unsigned short stIndex[3];		// texture coordinate indices
} mesh_t;

typedef struct
{
   int ident;		 // identifies as MD2 file "IDP2"
   int version;	 // mine is 8
   int skinwidth;    // width of texture
   int skinheight;   // height of texture
   int framesize;    // number of bytes per frame
   int numSkins;     // number of textures
   int numXYZ;       // number of points
   int numST;        // number of texture
   int numTris;      // number of triangles
   int numGLcmds;
   int numFrames;    // total number of frames
   int offsetSkins;  // offset to skin names (64 bytes each)
   int offsetST;     // offset of texture s-t values
   int offsetTris;   // offset of triangle mesh
   int offsetFrames; // offset of frame data (points)
   int offsetGLcmds; // type of OpenGL commands to use
   int offsetEnd;    // end of file
} modelHeader_t;


class CMD2Model// : public CObject
{
//private:
public:

     int numFrames;			// number of model frames
     int numVertices;         // number of vertices
     int numTriangles;        // number of triangles
     int numST;               // number of skins
     int frameSize;           // size of each frame in bytes
     mesh_t *triIndex;        // triangle list
     texCoord_t *st;          // texture coordinate list
     vector_t *vertexList;    // vertex list
     //CTexture *modelTex;     // texture data
     std::vector<uint32_t> indices;
     std::vector<texCoord_t> texCoords;

     //void SetupSkin(CTexture *thisTexture);

//protected:
public:
	//modelState_t modelState;	// current model animation state
     //int currentFrame;        // current frame # in animation
     //int nextFrame;           // next frame # in animation

public:
     //float interpol;          // percent through current frame
	 //modelState_t modelState;	// current model animation state

     CMD2Model(const char *modelFile = NULL, const char *skinFile = NULL);        // constructor
     ~CMD2Model();       // destructor

     // load model and skin/texture at the same time
     int Load(const char *modelFile, const char *skinFile);

     // load model only
     int LoadModel(const char *modelFile);

     // load skin only
     int LoadSkin(const char *skinFile);

     // set model's texture/skin
     //int SetTexture(CTexture *texture);

     // render model with interpolation to get animation
     //int AnimateModel(int startFrame, int endFrame, float percent);
	 int AnimateModel(int startFrame, int endFrame, float percent, int & currentFrame, int & nextFrame, float & interpol);

     // render a single frame
     int RenderFrame(int keyFrame);

     // free memory of model
     void Unload();

	//// set animation state of model
	//void SetState(modelState_t state);	

	//// retrieve animation state of model
	//modelState_t GetState();
};

#endif
