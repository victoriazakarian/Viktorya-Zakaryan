#include "vector.h"
#include <ctype.h>
#include <stdio.h>

void vector_print(Vector* vec)
{
	for(size_t i = 0; i < vector_size(vec); i++)
	{
		int number;
		vector_get(vec, i, &number);
		printf("%d ", number);
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	char* filename = argv[1];

	FILE *file = fopen(filename, "r");
	if(file == NULL)
	{
		printf("Error opening file \n");
		return 1;
	}

	char buffer[4096];

	Vector vec;
	if(!vector_init(&vec,sizeof(int),16))
	{
		printf("Error initializing vector");
		return 1;
	}

	while (fgets(buffer,sizeof(buffer), file))
	{
		int i = 0;
		while(buffer[i] != '\0')
		{
			if(isdigit(buffer[i]))
			{
				int number  = 0;
				while(isdigit(buffer[i]))
				{
					number = number * 10 + (buffer[i] - '0');
					i++;
				}
				vector_push_back(&vec, &number);
			}
			else
				i++;
		}

	}
	fclose(file);
	vector_print(&vec);

	return 0;
}
