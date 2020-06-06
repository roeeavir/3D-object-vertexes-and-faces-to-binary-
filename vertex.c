
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vertex.h"

// Runs on a string and loads its contents into a vertex.
void setVertexFromStr(Vertex* ver, char* str)
{
	char c = 'x';
	char* line;
	char* delimeters = " ";
	line = strtok(str, delimeters);

	while (line != NULL)
	{
		if (isdigit(line[0]) || line[0] == '-')
		{
			if (c == 'x')
				(void)sscanf(line, "%f", &ver->x);
			else if (c == 'y')
				(void)sscanf(line, "%f", &ver->y);
			else if (c == 'z')
				(void)sscanf(line, "%f", &ver->z);
			c++;
		}
		line = strtok(NULL, delimeters);
	}
}

//Transforms coordinates of vertex.
void transformVertex(Vertex* ver, float num)
{
	ver->x = (float)((ver->x) * num);
}

//Saves a vertex to Text file.
void saveVertexToTextFile(Vertex* ver, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	fprintf(fp, "%f %f %f\n", ver->x, ver->y, ver->z);
}


//Saves a vertex to Binary file.
void saveVertexToBinFile(Vertex* ver, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	fwrite(&ver->x, sizeof(float), 1, fp);
	fwrite(&ver->y, sizeof(float), 1, fp);
	fwrite(&ver->z, sizeof(float), 1, fp);
}

//Loads a vertex from Text file.
void loadVertexFromTextFile(Vertex* ver, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	(void)fscanf(fp, "%f %f %f\n", &ver->x, &ver->y, &ver->z);
}

//Loads a vertex from Binary file.
void loadVertexFromBinFile(Vertex* ver, FILE* fp)
{
	if (!fp)
	{
		printf("Cannot open file.");
		return;
	}

	fread(&ver->x, sizeof(float), 1, fp);
	fread(&ver->y, sizeof(float), 1, fp);
	fread(&ver->z, sizeof(float), 1, fp);
}