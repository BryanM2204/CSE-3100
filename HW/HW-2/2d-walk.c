#include <stdio.h>
#include <stdlib.h>


double two_d_random(int n)
{

	//Fill in code below
	//When deciding which way to go for the next step, generate a random number as follows.
	//r = rand() % 4;
	//Treat r = 0, 1, 2, 3 as up, right, down and left respectively.

	//The random walk should stop once the x coordinate or y coordinate reaches $-n$ or $n$. 
	//The function should return the fraction of the visited $(x, y)$ coordinates inside (not including) the square.

	// intialize a 2-D array that has the equivalent size to all possible points in square n
	int visited_points[2 * n + 1][2 * n + 1];

	// for every pair, sets to 0 to start out
	for (int i=0; i < 2 * n; i++){
		for (int j=0; j< 2 * n; j++){
			visited_points[i][j] = 0;
		}
	}

	//declare and assign values to x and y at the starting point - as the starting point is already hit
	// assign unique_points to 1
	int x=0, y=0;
	int unique_points = 0; 
	

	// while loop to keep the program running until x or y hit an edge
	while(x > -n && x < n && y > -n && y < n){
		// checks to see that the x and y values are inside the square and that the coordinate pair has not been visited yet
		if (x > -n && x < n && y > -n && y < n && visited_points[x+n][y+n] == 0) {
			// assigns coordinate pair to 1 and increments unique_points by 1
			visited_points[x+n][y+n] = 1;
			unique_points++;
		}

		int r = rand() % 4;
		
		// switch case used to do the corresponding movement depending on the randomized num
		switch(r){
			case 0:
				y++;
				break;

			case 1:
				x++;
				break;

			case 2:
				y--;
				break;

			case 3:
				x--;
				break;

		}	
	}
	// calculates the fraction of unique points hit with the amount of actual points inside the square
	double calculation = (double)unique_points / ((2 * n  - 1) * (2 * n - 1));

	return calculation;

}



//Do not change the code below
int main(int argc, char *argv[])
{
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;
}
