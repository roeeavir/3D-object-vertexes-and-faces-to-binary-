

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "object.h"
#include "face.h"
#include "vertex.h"
#include "def.h"

//A function that returns a created object from file.
Object* createObject(char* filename)
{

	Object* obj = (Object*)malloc(1 * sizeof(Object));
	if (!obj)
		return NULL;

	if (!setObject(filename, obj))
	{
		free(obj);
		return NULL;
	}

	return obj;
}

//Setting the object from file.
int setObject(char* fileName, Object* obj)
{
	FILE* fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("%s", FILEERROR);
		return 0;
	}

	char line[MAXSIZE];//Max size possible for each line.

	if (!getNumOfVersAndFaces(fp, obj, line))
	{
		fclose(fp);
		return 0;
	}

	rewind(fp);//Sets file pointer to the beginning of the file.

	if (!createArraysofVertexesAndFaces(obj))
	{
		fclose(fp);
		return 0;
	}

	if (!addAllVertexesAndFaces(fp, obj, line))
	{
		fclose(fp);
		return 0;
	}

	fclose(fp);
	return 1;
}

//Checks the needed size of each array;
int getNumOfVersAndFaces(FILE* fp, Object* obj, char* line)
{
	if (!fp)
	{
		printf("%s", FILEERROR);
		return 0;
	}

	obj->numberOfVertexes = 0;
	obj->numberOfFaces = 0;

	while (fgets(line, MAXSIZE, fp) != NULL)
	{
		if (line[0] == 'v' && line[1] == ' ')
			obj->numberOfVertexes++;
		else if (line[0] == 'f' && line[1] == ' ')
			obj->numberOfFaces++;
	}

	return 1;
}

//Creates vertex and face arrays with malloc
int createArraysofVertexesAndFaces(Object* obj)
{
	obj->vertexes = (Vertex*)malloc((obj->numberOfVertexes) * sizeof(Vertex));
	if (!obj->vertexes)
		return 0;

	obj->faces = (Face*)malloc((obj->numberOfFaces) * sizeof(Face));
	if (!obj->faces)
	{
		free(obj->vertexes);
		return 0;
	}

	return 1;
}

//Adds the vertexes and faces to object.
int addAllVertexesAndFaces(FILE* fp, Object* obj, char* line)
{
	if (!fp)
	{
		printf("%s", FILEERROR);
		return 0;
	}

	int indexVertexes = 0;
	int indexFaces = 0;

	while (fgets(line, MAXSIZE, fp) != NULL)
	{
		if (line[0] == 'v' && line[1] == ' ')
			setVertexFromStr(&(obj->vertexes)[indexVertexes++], line);
		else if (line[0] == 'f' && line[1] == ' ')
			if (!setFaceFromStr(&(obj->faces)[indexFaces++], line))
				return 0;
	}

	return 1;
}

//Counts the number of triangular faces and sets it into a generic variable.
void printFaces(Object* ptr, void* numberOfTriangularFaces)
{
	*((int*)numberOfTriangularFaces) = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++)
	{
		if (ptr->faces[i].size == 3)
			//((int)numberOfTriangularFaces)++; triple-hatzil check

			(*((int*)numberOfTriangularFaces))++;
	}

}

// Sets into a generic variable the number of vertexes.
void printVertexes(Object* ptr, void* numberOfVertexes)
{
	*((int*)numberOfVertexes) = ptr->numberOfVertexes;
}

// Sets the total area of all triangular faces in the object into a generic variable.
void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces)
{
	double temp;
	*((double*)totalAreaOfTriangularFaces) = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++)
	{
		if (ptr->faces[i].size == 3)
			*((double*)totalAreaOfTriangularFaces) += getAreaOfTriangularFace(ptr, i);
		temp = *((double*)totalAreaOfTriangularFaces);
	}
}

// Calculates the total area of all triangular faces in the object.
double getAreaOfTriangularFace(Object* pObj, int index)
{
	double edge1, edge2, edge3; //Edges of triangular face.
	int indexVer1, indexVer2, indexVer3;//Indexes of each vertex in triangular face.
	double s;//Vriable that helps calculating the area (A part of a formula).

	indexVer1 = pObj->faces[index].vertex[0] - 1;
	indexVer2 = pObj->faces[index].vertex[1] - 1;
	indexVer3 = pObj->faces[index].vertex[2] - 1;

	edge1 = getEdgeOfTriangle(pObj->vertexes[indexVer1], pObj->vertexes[indexVer2]);
	edge2 = getEdgeOfTriangle(pObj->vertexes[indexVer1], pObj->vertexes[indexVer3]);
	edge3 = getEdgeOfTriangle(pObj->vertexes[indexVer2], pObj->vertexes[indexVer3]);

	s = (edge1 + edge2 + edge3) / 2;

	// Heron's formula.
	return sqrt(s * (s - edge1) * (s - edge2) * (s - edge3));

}

//Length of each edge.
double getEdgeOfTriangle(Vertex ver1, Vertex ver2)
{
	return sqrt(pow((double)(ver1.x - ver2.x), 2)
		+ pow((double)(ver1.y - ver2.y), 2)
		+ pow((double)(ver1.z - ver2.z), 2));
}

//Saves the object to a text file.
void saveObjectToTextFile(Object* obj, FILE* fp)
{
	int i;
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	//Saves the number of vertexes in an object to file.
	fprintf(fp, "%d\n", obj->numberOfVertexes);
	//Saves the number of faces in an object to file.
	fprintf(fp, "%d\n", obj->numberOfFaces);

	for (i = 0; i < obj->numberOfVertexes; i++)
		saveVertexToTextFile(&obj->vertexes[i], fp);

	for (i = 0; i < obj->numberOfFaces; i++)
		saveFaceToTextFile(&obj->faces[i], fp);

}

//Saves the object to a binary file.
void saveObjectToBinFile(Object* obj, FILE* fp)
{
	int i;
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	//Saves the number of vertexes in an object to file.
	fwrite(&obj->numberOfVertexes, sizeof(int), 1, fp);
	//Saves the number of faces in an object to file.
	fwrite(&obj->numberOfFaces, sizeof(int), 1, fp);

	for (i = 0; i < obj->numberOfVertexes; i++)
		saveVertexToBinFile(&obj->vertexes[i], fp);

	for (i = 0; i < obj->numberOfFaces; i++)
		saveFaceToBinFile(&obj->faces[i], fp);

}

Object* loadObjectFromFile(FILE* fp, enum FileType type)
{
	if (!fp)
	{
		printf("%s", FILEERROR);
		return NULL;
	}

	Object* obj;

	obj = (Object*)malloc(1 * sizeof(Object));
	if (!obj)
		return NULL;
	//Loads the number of vertexes and faces in an object from file.
	if (type == 0)
	{
		(void)fscanf(fp, "%d", &obj->numberOfVertexes);
		(void)fscanf(fp, "%d", &obj->numberOfFaces);
	}
	else
	{
		fread(&obj->numberOfVertexes, sizeof(int), 1, fp);
		fread(&obj->numberOfFaces, sizeof(int), 1, fp);
	}

	if (!createArraysofVertexesAndFaces(obj))
		return NULL;

	if (type == 0)
		obj = loadObjectFromTextFile(obj, fp, type);
	else
		obj = loadObjectFromBinFile(obj, fp, type);

	return obj;
}

//Loads the object from a text file.
Object* loadObjectFromTextFile(Object* obj, FILE* fp, enum FileType type)
{
	if (!fp)
	{
		printf("%s", FILEERROR);
		return NULL;
	}

	int i;

	for (i = 0; i < obj->numberOfVertexes; i++)
		loadVertexFromTextFile(&obj->vertexes[i], fp);

	for (i = 0; i < obj->numberOfFaces; i++)
		loadFaceFromFile(&obj->faces[i], fp, type);

	return obj;
}

//Loads the object from a binary file.
Object* loadObjectFromBinFile(Object* obj, FILE* fp, enum FileType type)
{
	if (!fp)
	{
		printf("%s", FILEERROR);
		return NULL;
	}

	int i;

	for (i = 0; i < obj->numberOfVertexes; i++)
		loadVertexFromBinFile(&obj->vertexes[i], fp);

	for (i = 0; i < obj->numberOfFaces; i++)
		loadFaceFromFile(&obj->faces[i], fp, type);

	return obj;
}

//Transforms a vertex in an obj file and sets it to a new file.
void transformObject(char* originalObjectFileName, char* deformedObjectFileName)
{
	// Opening new file.
	FILE* fpDef = fopen(deformedObjectFileName, "w");
	if (!fpDef)
	{
		printf("%s", FILEERROR);
		return;
	}

	// Opening originl file.
	FILE* fpOrg = fopen(originalObjectFileName, "r");
	if (!fpOrg)
	{
		printf("%s", FILEERROR);
		fclose(fpDef);
		return;
	}

	char line[MAXSIZE];
	Vertex* ver = (Vertex*)malloc(sizeof(Vertex));
	if (!ver)
	{
		fclose(fpOrg);
		fclose(fpDef);
		return;
	}
	while (fgets(line, MAXSIZE, fpOrg) != NULL)
	{
		if (line[0] == 'v' && line[1] == ' ')//Checks if a line is a vertex.
		{
			setVertexFromStr(ver, line);// Setting a new vertex for each line.
			transformVertex(ver, (float)0.3);//Transforming the vertex.
			fprintf(fpDef, "v %f %f %f\n", ver->x, ver->y, ver->z);//Saving vertex to file.
		}
		else
			fputs(line, fpDef);
	}

	free(ver);
	fclose(fpOrg);
	fclose(fpDef);
}

//Frees object from memory.
void freeObject(Object* obj)
{
	free(obj->vertexes);

	freeFace(obj->faces);

	free(obj);
}
