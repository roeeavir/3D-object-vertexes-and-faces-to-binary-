

#pragma once

#include "vertex.h"
#include "face.h"

typedef struct {
	int numberOfVertexes;
	Vertex* vertexes; // Array of all Vertexes
	int  numberOfFaces;
	Face* faces; // Array of all Faces
} Object;

Object* createObject(char* filename);
int getNumOfVersAndFaces(FILE* fp, Object* obj, char* line);
int setObject(char* fileName, Object* obj);
int createArraysofVertexesAndFaces(Object* obj);
int addAllVertexesAndFaces(FILE* fp, Object* obj, char* line);

void printFaces(Object* ptr, void* numberOfTriangularFaces);
void printVertexes(Object* ptr, void* numberOfVertexes);
void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces);

double getAreaOfTriangularFace(Object* pObj, int index);
double getEdgeOfTriangle(Vertex ver1, Vertex ver2);

void saveObjectToTextFile(Object* obj, FILE* fp);
void saveObjectToBinFile(Object* obj, FILE* fp);

Object* loadObjectFromFile(FILE* fp, enum FileType type);
Object* loadObjectFromTextFile(Object* obj, FILE* fp, enum FileType type);
Object* loadObjectFromBinFile(Object* obj, FILE* fp, enum FileType type);

void transformObject(char* originalObjectFileName, char* deformedObjectFileName);

void freeObject(Object* obj);