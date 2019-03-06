// Game of Life, v 0.1
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define xy_to_i(x,y,y_size) ( y*y_size + x )

#define X_SIZE 5
#define Y_SIZE 5
#define STEPS 10

char* create_field(int x_size, int y_size)
{
	printf("X:%d, Y:%d, char:%llu, field:%llu\n",
		x_size, y_size, sizeof(char), x_size*y_size*sizeof(char));
	
	char* field = (char*)(calloc( x_size*y_size, sizeof(char) ));
	for (int y = 0; y < Y_SIZE; ++y)
		for (int x = 0; x < X_SIZE; ++x)
		{
			int r = rand() % 2;
			char c;
			if (r == 0) c = '.';
			else 		c = 'X';
			field[xy_to_i(x,y,Y_SIZE)] = c;
		}
	return field;
}

void destroy_field(char* field)
{
	free(field);
}

void print_field(char* field)
{
	for (int y = 0; y < Y_SIZE; ++y)
	{
		for (int x = 0; x < X_SIZE; ++x)
		{
			printf("%c ", field[xy_to_i(x,y,Y_SIZE)]);
		}
		printf("\n");
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));   // Initialization, should only be called once.
	char* field = create_field(X_SIZE, Y_SIZE);
	
	printf("Hello, world!\n\n");

	print_field(field);

	destroy_field(field);

	return 0;
}