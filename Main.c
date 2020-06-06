
#include <stdio.h>
#include <stdlib.h>

#include "scene.h"


void main() {

	Scene* scene;
	Scene* scene1, * scene2;

	// Create a Scene of Objects received 
	// from files GoingMerry.obj, Donald.obj, Pony_cartoon.obj
	scene = createScene("GoingMerry.obj", "Donald.obj", "Pony_cartoon.obj", NULL);

	// Checks if scene isn't null.
	if (scene != NULL)
	{
		// Print out all Vertexes
		perform(scene, printVertexes, "INT", "The number of vertexes of all objects is");

		// Count the number of all Triangular faces of all objects in Scene 
		perform(scene, printFaces, "INT", "The number of Triangular faces of all objects is");

		// Count the total area of all Triangular faces of all objects in Scene 
		perform(scene, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");

		// Save the world to file in Text and in Binary formats
		saveScene(scene, "FirstScene.dat", TextFormat);
		saveScene(scene, "SecondScene.dat", BinaryFormat);

		// Retrieve the saved data

		scene1 = loadScene("FirstScene.dat", TextFormat);
		scene2 = loadScene("SecondScene.dat", BinaryFormat);

		if (scene1 != NULL)
		{
			// Check Retrieve the saved data of text format
			perform(scene1, printVertexes, "INT", "The number of vertexes of all objects is");
			perform(scene1, printFaces, "INT", "The number of Triangular faces of all objects is");
			perform(scene1, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");
		}

		if (scene2 != NULL)
		{
			// Check Retrieve the saved data of binary format
			perform(scene2, printVertexes, "INT", "The number of vertexes of all objects is");
			perform(scene2, printFaces, "INT", "The number of Triangular faces of all objects is");
			perform(scene2, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects is");
		}

		// Free all memory allocated for the Scene
		freeScene(scene);
		if (scene1 != NULL)
			freeScene(scene1);
		if (scene2 != NULL)
			freeScene(scene2);
	}

	// Make transformation based on the original object defined in all 3 given files
	transformObject("GoingMerry.obj", "StrangeGoingMerry.obj");
	transformObject("Pony_cartoon.obj", "StrangePony_cartoon.obj");
	transformObject("Donald.obj", "StrangeDonald.obj");

	system("pause"); // Pauses the program at its end.
}
