
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "func.h"

//Reads a string and sets it into a float.
float setFloat(char* str, int* index, float num, int posOrNeg)
{
	int afDecPnt = 10;//Decimal point of the float.
	int isDone = 0;

	while (!isDone)
	{
		if (isdigit(str[*index]))
		{
			num = num * 10 + str[*index] - '0';
			*index = (*index) + 1;
		}
		else if (str[*index] == '.')
		{
			*index = (*index) + 1;
			while (isdigit(str[*index]))
			{
				num = num * afDecPnt + ((str[*index] - '0'));
				num = num / afDecPnt;
				afDecPnt *= 10;
				*index = (*index) + 1;
			}
		}
		else
		{
			isDone = 1;
			*index = (*index) - 1;
		}
	}

	return num * posOrNeg;
}