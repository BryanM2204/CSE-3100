#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100000

//Return the next index and update a[]
int next_index(int a[], int k, int n)
{

	int new_index = (k+a[k]) % n; // finds index that fits in range

	// stops the walker when it reaches 0
	if(a[k] == 0){
		return k;
	}
	
	// decrements by 1 if outside range
	a[k]--;

	// returns new index
	return new_index;
	
}

int main(int argc, char *argv[])
{

	if(argc!=2)
	{
		printf("Usage: %s n\n", argv[0]);
		return -1;
	}
	int a[MAX];

	int n = atoi(argv[1]);
	assert(n >= 1 && n <= MAX);
	for(int i=0; i<n; i++)
	{
		a[i] = i + 1;
	}	

	int k = 0;
	while(a[k] > 0)
	{
		printf("k=%d a[%d] = %d\n", k, k, a[k]);
		k = next_index(a, k, n);
	}
	printf("finally:\nk=%d a[%d] = %d\n", k, k, a[k]);
	return 0;
}