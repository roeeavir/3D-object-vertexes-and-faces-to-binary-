#pragma once



typedef void* DATA; // A generic data type.
typedef enum { False, True } BOOL;	// A boolean type.
enum FileType { TextFormat, BinaryFormat }; // A file type.

#define MAXSIZE 200 // Maximum size for possible line in a file.
#define FILEERROR "\nCannot open file.\n" // Error message.

