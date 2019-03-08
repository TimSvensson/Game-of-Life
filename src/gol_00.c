// Game of Life, v 0.1
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define xy_to_i(x,y,y_size) ( y*y_size + x )

#define X_SIZE 5
#define Y_SIZE 5
#define STEPS 10

char* create_grid(int x_size, int y_size)
{
	printf("X:%d, Y:%d, char:%llu, grid:%llu\n",
		x_size, y_size, sizeof(char), x_size*y_size*sizeof(char));
	
	char* grid = (char*)(calloc( x_size*y_size, sizeof(char) ));
	for (int y = 0; y < Y_SIZE; ++y)
		for (int x = 0; x < X_SIZE; ++x)
		{
			int r = rand() % 2;
			char c;
			if (r == 0) c = '.';
			else 		c = 'X';
			grid[xy_to_i(x,y,Y_SIZE)] = c;
		}
	return grid;
}

void destroy_grid(char* grid)
{
	free(grid);
}

void print_grid(char* grid)
{
	for (int i = 0; i<2*X_SIZE; i++)
		printf("=");
	printf("\n");
	for (int y = 0; y < Y_SIZE; ++y)
	{
		for (int x = 0; x < X_SIZE; ++x)
		{
			printf("%c ", grid[xy_to_i(x,y,Y_SIZE)]);
		}
		printf("\n");
	}
	for (int i = 0; i<2*X_SIZE; i++)
		printf("=");
	printf("\n");
}

int is_alive(char* grid, int x, int y, int y_size)
{
	if (grid[xy_to_i(x,y,y_size)] == 'X') return 1;
	else return 0;
}

int get_live_neighbour(char* grid, int x, int y, int x_size, int y_size)
{
	int live_neighbours = 0;

	for (int yy = -1; yy < 2; yy++)
		for (int xx = -1; xx < 2; xx++)
		{
			if (xx + x < 0 || xx + x >= x_size) continue;
			if (yy + y < 0 || yy + y >= y_size) continue;
			if (xx == 0 && yy == 0) continue;

			if (is_alive(grid, x, y, y_size)) live_neighbours++;
		}

	return live_neighbours;
}

/*
 *	RULES OF GAME OF LIFE
 *
 *	1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 *	2. Any live cell with two or three live neighbours lives on to the next generation.
 *	3. Any live cell with more than three live neighbours dies, as if by overpopulation.
 *	4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 */
void step_grid(char* prev_grid, char* crnt_grid, int x_size, int y_size)
{
	for (int y = 0; y < y_size; y++)
	{
		for (int x = 0; x < x_size; x++)
		{
			int live_neighbours = get_live_neighbour(prev_grid, x, y, x_size, y_size);
			if (is_alive(prev_grid, x, y, y_size))
			{
				if (2 <= live_neighbours && live_neighbours < 4)
					crnt_grid[xy_to_i(x,y,y_size)] = 'X';
				else
					crnt_grid[xy_to_i(x,y,y_size)] = '.';
			}
			else
				if (live_neighbours == 3)
					crnt_grid[xy_to_i(x,y,y_size)] = 'X';
				else
					crnt_grid[xy_to_i(x,y,y_size)] = '.';
		}
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));   // Initialization, should only be called once.
	char* prev = create_grid(X_SIZE, Y_SIZE);
	char* crnt = create_grid(X_SIZE, Y_SIZE);
	
	printf("Hello, world!\n\n");

	print_grid(crnt);
	for (int i = 0; i < STEPS; ++i)
	{
		step_grid(prev, crnt, X_SIZE, Y_SIZE);
		print_grid(crnt);
		
		char* tmp = prev;
		prev = crnt;
		crnt = tmp;
	}

	destroy_grid(prev);
	destroy_grid(crnt);

	return 0;
}