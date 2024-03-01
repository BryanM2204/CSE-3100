#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i;

	printf("n = ");
	scanf("%d", &n);

	double pi = 0.;
	//TODO
	//add code below 

    // initialize and declare power variable in order to multiply 16 by itself
    double power = 1.0;
    
    // for loop iterates from 1 to user-inputted n
    for(i=0; i<=n; ++i){
        // checks to see if greater than 0, multiplies power variable with 16 with each iteration of for loop
        if (i > 0){
            power *= 16.0;
        }
        // adds pi (initialized to 0.) with summation from 0 to n in order to approximate pi
        pi += ((4.0 / (8*i + 1)) - (2.0 / (8*i + 4)) - (1.0 / (8*i + 5)) - (1.0 / (8*i + 6))) * (1.0 / (power));
    }

	printf("PI = %.10f\n", pi);
	return 0;
}