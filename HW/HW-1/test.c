#include <endian.h>
#include <stdio.h>

int main(){
    int value;
    scanf("%d", &value);


    int num1, num2, num3;

    if (value < 100){
        num2 = value % 10;
        num1 = value / 10;
        printf("Number 1: %d,     Number 2: %d", num1, num2);
    }

    if (value >= 100){
        num1 = value / 100;
        num2 = value % 10;
        num3 = value % 100;
        printf("Number 1: %d   Number 2: %d    Number 3: %d", num1, num2, num3);
    }    
    
    return 0;
}