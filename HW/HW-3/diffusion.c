#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{
	int x = 0, y = 0, z = 0;

	int random;
	
	// for loop used to have the particle move randomly for n amount of times
	for(int i=0; i<n; i++){
		// random number is chosen between 0 - 5
		random = rand() % 6;	
		
		// switch cases used to move in designated directions in x, y, z
		switch(random){
			case 0:
				x--;
				break;
			case 1:
				x++;
				break;
			case 2:
				y++;
				break;
			case 3:
				y--;
				break;
			case 4:
				z++;
				break;
			case 5:
				z--;
				break;
		}

	}
	// after arriving to the final location - location is calculated which serves as the index in grid[]
	int location = (x + n) + (2 * n + 1) * (y + n) + (2 * n + 1) * (2 * n + 1) * (z + n);

	// number of particles that visisted this specific point is incrememnted by 1
	grid[location]++;

}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{
	// declare and initialize count and particles 
	// particles keeps track of all visited particles in the cube and count keeps track of all points inside the radius of sphere
	int count = 0, particles=0;

	// max distance that a point can be located from the center to be counted 
	int max_distance_squared = (int)((r * n) * (r * n));

	// nested for loops used to iterate through every possible (x, y, z) combination
	for(int x=-n; x<=n; x++){
		for(int y=-n; y<=n; y++){
			for(int z=-n; z<=n; z++){
				// location of each point calculated - result is an index in grid array
				int location = (x + n) + (2 * n + 1) * (y + n) + (2 * n + 1) * (2 * n + 1) * (z + n);
				// checks to see if there are particles that have been visited at this location 
				if(grid[location] > 0){
					// the number of particles that have visited this location are accessed by grid[location] and added to int particles
					particles += grid[location];
					// the distance the current iteration particle is at is calculated and assigned to distance_squared
					int distance_squared = (x*x) + (y*y) + (z*z);
					// if distance_squared is below the maximum_distance_squared - then it is added to count
					if(distance_squared <= max_distance_squared){
						count += grid[location];
					}

				}
			}
		}
	}
	// returns fraction of proportion of number of particles inside the boundary and total particles
	return (double)count/ particles;
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below

	// dynamically allocate memory to array - size is all possible points inside the cube times the byte size of an int
	int *grid = (int *)malloc((2 * n + 1) * (2 * n + 1) * (2 * n + 1) * sizeof(int));

	// initialize all possible points through use of foor loops through (x, y, z) with 0
	for (int x = -n; x <= n; x++) {
		for (int y = -n; y <= n; y++) {
			for (int z = -n; z <= n; z++) {
				// location of point is calculated - serves as the index inside the grid array
				int location = (x + n) + (2 * n + 1) * (y + n) + (2 * n + 1) * (2 * n + 1) * (z + n);
				// assign 0
				grid[location] = 0;
			}
		}
	}


	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);
	//fill in some code below
	free(grid);

}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}