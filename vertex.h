
#pragma once

typedef struct {
	float x; // Coordinates of Vertex
	float y;
	float z;
} Vertex;

void setVertexFromStr(Vertex* ver, char* str);

void transformVertex(Vertex* ver, float num);

void saveVertexToTextFile(Vertex* ver, FILE* fp);
void saveVertexToBinFile(Vertex* ver, FILE* fp);

void loadVertexFromTextFile(Vertex* ver, FILE* fp);
void loadVertexFromBinFile(Vertex* ver, FILE* fp);