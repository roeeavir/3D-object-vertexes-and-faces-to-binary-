
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#include "scene.h"
#include "object.h"




//Creates scene from obj files.
Scene* createScene(char* fileName, ...)
{
	Scene* scene = (Scene*)malloc(1 * sizeof(Scene));
	if (!scene)
		return NULL;

	L_init(&scene->objList);// Initializing linked list.

	FILE* fp;
	va_list allFiles;
	char* currentFile;
	NODE* ptr;

	va_start(allFiles, fileName);// Initializing variadic list.
	currentFile = fileName;// Sets current file to be the first file name.

	ptr = &scene->objList.head; //Add to list one after the other
	scene->count = 0;

	while (currentFile != NULL)// While there is a file to read.
	{
		fp = fopen(currentFile, "r");
		if (!fp)
		{
			printf("%s", FILEERROR);
			return NULL;
		}
		// Inserts object into linked list.
		ptr = L_insert(ptr, createObject(currentFile));
		if (ptr->key == NULL)
			return NULL;
		scene->count++;
		// Sets current file to be the next file name.
		currentFile = va_arg(allFiles, char*);
		fclose(fp);
	}
	va_end(allFiles); // End of variadic list.

	return scene;
}

// A function that uses generic variables and function to preform a desired command.
void perform(Scene* scene, void(*func)(Object*, void*), char* type, char* str)
{
	void* result = NULL;
	void* temp = NULL;
	NODE* current_entry = scene->objList.head.next;

	if (!setType(type, &temp))// Sets temp to wanted type.
		return;
	setType(type, &result);// Sets result to wanted type.	

	printf("%s ", str);

	for (int i = 0; i < scene->count; i++)
	{
		// Sets in temp the wanted result for each object.
		func(current_entry->key, temp);

		current_entry = current_entry->next;

		// Sums results of each object.
		sumResults(type, result, temp);

	}

	printResults(type, result);

	free(temp);
	free(result);

}

//Sets variable to wanted type.
int setType(char* type, void** var)
{
	if (type == "ïnt" || type == "INT")
	{
		*var = malloc(sizeof(int));
		if (*((int**)var))
			*(*((int**)var)) = 0;

	}
	else if (type == "double" || type == "DOUBLE")
	{
		*var = malloc(sizeof(double));
		**((double**)var) = 0.0;
	}
	else
		printf("Invalid type!\n");
	if (!*var)
		return 0;
	else
		return 1;
}

//Sums wanted result.
void sumResults(char* type, void* result, void* temp)
{
	if (type == "ïnt" || type == "INT")
	{
		*((int*)result) += *((int*)temp);
	}
	else
	{
		*((double*)result) += *((double*)temp);
	}
}

//Prints result of generic type.
void printResults(char* type, void* result)
{
	if (type == "int" || type == "INT")
	{
		printf("%d\n", *((int*)result));
	}
	else
	{
		// Prints a double as far as 5 digits after the decimal point.
		printf("%lf\n", *((double*)result));
	}
}

//Saves scene in file, by wanted file type.
void saveScene(Scene* scene, char* fileName, enum FileType type)
{
	FILE* fp;
	if (type == 0)// Checks file type and opens it accorindly.
		fp = fopen(fileName, "w");
	else
		fp = fopen(fileName, "wb");

	if (!fp)
	{
		printf("%s", FILEERROR);
		return;
	}

	NODE* current_entry = scene->objList.head.next;

	if (type == 0)
	{
		fprintf(fp, "%d\n", scene->count);
		for (int i = 0; i < scene->count; i++)
		{
			saveObjectToTextFile(current_entry->key, fp);
			current_entry = current_entry->next;
		}
	}
	else
	{
		fwrite(&scene->count, sizeof(int), 1, fp);
		for (int i = 0; i < scene->count; i++)
		{
			saveObjectToBinFile(current_entry->key, fp);
			current_entry = current_entry->next;
		}
	}

	fclose(fp);
}

// Loads scene from a file, by wanted filetype.
Scene* loadScene(char* fileName, enum FileType type)
{
	Scene* scene;
	FILE* fp;
	NODE* ptr;
	Object* temp;

	if (type == 0)
		fp = fopen(fileName, "r");
	else
		fp = fopen(fileName, "rb");

	if (!fp)
	{
		printf("%s", FILEERROR);
		return NULL;
	}

	scene = (Scene*)malloc(1 * sizeof(Scene));
	if (!scene)
		return NULL;

	L_init(&scene->objList);// Initialization of linked list.
	ptr = &scene->objList.head;

	// prints the amount of objects to files head.
	if (type == 0)
		(void)fscanf(fp, "%d", &scene->count);
	else
		fread(&scene->count, sizeof(int), 1, fp);

	for (int i = 0; i < scene->count; i++)
	{
		temp = loadObjectFromFile(fp, type);
		if (!temp)
			return NULL;
		ptr = L_insert(ptr, temp);
	}

	fclose(fp);
	return scene;
}

//Frees scene from memory.
void freeScene(Scene* scene)
{
	NODE* ptr, * tmp;
	ptr = scene->objList.head.next;
	for (int i = 0; i < scene->count; i++)
	{
		tmp = ptr;
		if (ptr->next != NULL)
			ptr = ptr->next;
		freeObject(tmp->key);
	}
	L_free(&scene->objList);
}

