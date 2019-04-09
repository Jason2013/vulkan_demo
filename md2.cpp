#include <cassert>
#include "md2.h"

// CMD2Model constructor
CMD2Model::CMD2Model(const char *modelFile, const char *skinFile)
{
     numVertices = 0;    // vertices
     numTriangles = 0;   // triangles
     numFrames = 0;      // frames
     numST = 0;          // texture coordinates
     frameSize = 0;      // needed?
     triIndex = NULL;    // triangle indices
     st = NULL;          // texture coordinate indices
     vertexList = NULL;  // vertices

	if (modelFile != NULL)
	{
		Load(modelFile, skinFile);
	}
}


// CMD2Model destructor
CMD2Model::~CMD2Model()
{
	Unload();
}


// CMD2Model::Load()
// access: public
// desc: loads model and skin
bool CMD2Model::Load(const char *modelFile, const char *skinFile)
{
     FILE *filePtr;                          // file pointer
     int fileLen;                            // length of model file
     char *buffer;                           // file buffer

     modelHeader_t *modelHeader;             // model header

     stIndex_t *stPtr;                       // texture data
     frame_t *frame;                         // frame data
     vector_t *vertexListPtr;                // index variable
     mesh_t *bufIndexPtr;                    // index variables
     int i, j;                               // index variables

     // open the model file
     errno_t err = fopen_s(&filePtr, modelFile, "rb");
     assert(!err);
     if (err)
         return false;


     // find length of file
     fseek(filePtr, 0, SEEK_END);
     fileLen = ftell(filePtr);
     fseek(filePtr, 0, SEEK_SET);

     // read entire file into buffer
     buffer = new char [fileLen+1];
     fread(buffer, sizeof(char), fileLen, filePtr);

     // extract model file header from buffer
     modelHeader = (modelHeader_t*)buffer;

     vertexList = new vector_t [modelHeader->numXYZ * modelHeader->numFrames];

     numVertices = modelHeader->numXYZ;
     numFrames = modelHeader->numFrames;
     frameSize = modelHeader->framesize;

     for (j = 0; j < numFrames; j++)
     {
          frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];

          vertexListPtr = (vector_t*)&vertexList[numVertices * j];
          for (i = 0; i < numVertices; i++)
          {
               vertexListPtr[i].point[0] = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
               vertexListPtr[i].point[1] = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
               vertexListPtr[i].point[2] = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
          }
     }

     numST = modelHeader->numST;
     st = new texCoord_t [numST];

     stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];

     for (i = 0; i < numST; i++)
     {
         st[i].s = (float)stPtr[i].s / (float)modelHeader->skinwidth;
         st[i].t = (float)stPtr[i].t / (float)modelHeader->skinheight;
     }


     numTriangles = modelHeader->numTris;
     triIndex = new mesh_t [numTriangles];

     // point to triangle indexes in buffer
     bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];

     // create a mesh (triangle) list
     for (i = 0; i < numTriangles; i++)
     {
         triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
         triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
         triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
         triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
         triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
         triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
     }

     for (i = 0; i < numTriangles; i++)
     {
         indices.push_back(triIndex[i].meshIndex[0]);
         indices.push_back(triIndex[i].meshIndex[2]);
         indices.push_back(triIndex[i].meshIndex[1]);
     }

     texCoords.resize(numVertices);
     for (i = 0; i < numTriangles; i++)
     {
         assert(triIndex[i].meshIndex[0] < numVertices);
         assert(triIndex[i].meshIndex[1] < numVertices);
         assert(triIndex[i].meshIndex[2] < numVertices);

         assert(triIndex[i].stIndex[0] < numST);
         assert(triIndex[i].stIndex[1] < numST);
         assert(triIndex[i].stIndex[2] < numST);

         texCoords[triIndex[i].meshIndex[0]] = st[triIndex[i].stIndex[0]];
         texCoords[triIndex[i].meshIndex[1]] = st[triIndex[i].stIndex[1]];
         texCoords[triIndex[i].meshIndex[2]] = st[triIndex[i].stIndex[2]];
     }

     // close file and free memory
     fclose(filePtr);
	delete buffer;

     return true;
}


// Unload()
// desc: unloads model data from memory
void CMD2Model::Unload()
{
     if (triIndex != NULL)
          delete [] triIndex;
     if (vertexList != NULL)
          delete [] vertexList;
     if (st != NULL)
          delete [] st;
}
