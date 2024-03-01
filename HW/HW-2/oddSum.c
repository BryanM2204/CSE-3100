#include <stdio.h>
#include <stdlib.h>

int oddSumHelp(int count, int bound, int value)
{
    //fill in your code below

    // base case - if count and value are 0, then it returns value of 1 (true)
    if(count==0 && value==0) return 1;
    
    // base case - if value is 0 or bound is less than or equal to 0, returns 0 (false)
    if (value < 0 || bound <=0) return 0;

    // intialize and declare result with a recursive call 
    //with every recursive call - count reduces by 1 as it is the number of times it should run
    //bound reduces by 2 as it is assumed it is at an odd number - subtract 2 to reach the next subsequent odd
    // and the value is reduced by bound in order to reach a value of 0
    int result = oddSumHelp(count-1, bound-2, value-bound);

    // after all recursive calls are done - result is checked to see if it's 1
    // if true - prints out bound and returns true
    if(result == 1){
        printf("%d ", bound);
        return 1;
    }
    // checks to see any other possible combinations of odd numbers to reach the value
    // starts at a bound smaller by 2 than the original 
    return oddSumHelp(count, bound - 2, value);
}

//Do not change the code below
void oddSum(int count, int bound, int value)
{   
    if(value <= 0 || count <= 0 || bound <= 0) return;

    if(bound % 2 == 0) bound -= 1;

    if(!oddSumHelp(count, bound, value)) printf("No solutions.\n");
    
    else printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc != 4) return -1;

	int count = atoi(argv[1]);
	int bound = atoi(argv[2]);
	int value = atoi(argv[3]);

	//oddSum(12,30,200);
	//oddSum(10,20,100);
	//oddSum(20,20,200);
	oddSum(count, bound, value);
	return 0;
}