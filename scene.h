

#pragma once

#include "linkedList.h"
#include "object.h"

typedef struct {
	LIST objList;
	int count;
} Scene;

Scene* createScene(char* fileName, ...);

void perform(Scene* scene, void(*func)(Object*, void*), char* type, char* str);
int setType(char* type, void** var);
void sumResults(char* type, void* result, void* temp);
void printResults(char* type, void* result);

void saveScene(Scene* scene, char* fileName, enum FileType type);

Scene* loadScene(char* fileName, enum FileType type);


void freeScene(Scene* scene);