
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "face.h"


// Runs on a string and loads its contents into a face.
int setFaceFromStr(Face* face, char* str)
{
	face->size = 0;
	char* line;
	char* delimeter = " ";
	void* temp;

	face->vertex = (int*)malloc(1 * sizeof(int));
	if (!face->vertex)
		return 0;

	line = strtok(str, delimeter);

	while (line != NULL)
	{
		if (isdigit(line[0]))
		{
			if (line != NULL)
			{
				temp = (int*)realloc(face->vertex, (++face->size) * sizeof(int));
				if (!temp)
					return 0;
				face->vertex = temp;
			}
			(void)sscanf(line, "%d", &face->vertex[(face->size - 1)]);
		}
		line = strtok(NULL, delimeter);
	}
	return 1;
}


//Saves a face to Text file.
void saveFaceToTextFile(Face* face, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}
	fprintf(fp, "%d ", face->size);

	for (int i = 0; i < face->size; i++)
		fprintf(fp, "%d ", face->vertex[i]);

	fprintf(fp, "\n");
}

//Saves a face to Binary file.
void saveFaceToBinFile(Face* face, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	fwrite(&face->size, sizeof(int), 1, fp);

	for (int i = 0; i < face->size; i++)
		fwrite(&face->vertex[i], sizeof(int), 1, fp);
}

int loadFaceFromFile(Face* face, FILE* fp, enum FileType type)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return 0;
	}

	if (type == 0)
		(void)fscanf(fp, "%d ", &face->size);
	else
		fread(&face->size, sizeof(int), 1, fp);

	face->vertex = (int*)malloc(face->size * sizeof(int));
	if (!face->vertex)
		return 0;

	if (type == 0)
		loadFaceFromTextFile(face, fp);
	else
		loadFaceFromBinFile(face, fp);

	return 1;
}

//Loads a face from Text file.
void loadFaceFromTextFile(Face* face, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	for (int i = 0; i < face->size; i++)
		(void)fscanf(fp, "%d ", &face->vertex[i]);

	(void)fscanf(fp, "\n");
}

//Loads a face from Binary file.
void loadFaceFromBinFile(Face* face, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	for (int i = 0; i < face->size; i++)
		fread(&face->vertex[i], sizeof(int), 1, fp);
}

//Frees face from memory.
void freeFace(Face* face)
{
	free(face->vertex);
}
