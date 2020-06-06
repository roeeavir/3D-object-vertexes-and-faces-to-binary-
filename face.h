
#pragma once#define __FACE__

#include "vertex.h"

typedef struct {
	int size;	// Number of vertexes of the face	
	int* vertex;	// Array of Ids of the vertexes
} Face;

int setFaceFromStr(Face* face, char* str);

void saveFaceToTextFile(Face* face, FILE* fp);
void saveFaceToBinFile(Face* face, FILE* fp);

int loadFaceFromFile(Face* face, FILE* fp, enum FileType type);
void loadFaceFromTextFile(Face* face, FILE* fp);
void loadFaceFromBinFile(Face* face, FILE* fp);


void freeFace(Face* face);