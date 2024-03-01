#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;

	printf("n = ");
	scanf("%d", &n);

	int m = n;
	//TODO
	//add code below
	
	// while loop breaks only if 1 or 4 is the result - indicates whether it is a happy num 
	while (n != 1 && n != 4) {
		int total = 0;
		// while loop that squares individual digits using modulo - completes calculations when n=0
		while(n != 0) {
			total += (n%10) * (n%10);
			n /= 10;
		}
		
		printf("%d\n", total); // Print the total value for every loop

		n = total;
		
	} 
	

	if(n==1) printf("%d is a happy number.\n", m);
	else printf("%d is NOT a happy number.\n", m);
	return 0;
}