#include <stdio.h>

int main(void)
{
    int sum = 0, i = 0;

    while(i < 200)
    {
        sum += i;
        i += 2;
    }


    printf("Hello, World!\n");
    printf("%d", sum);
    return 0;
}
