#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define MAX 1000000

int main(int argc, char *argv[]){
    char*args[] = {"ls", NULL};
    execv(args[0], args);
    printf("This is bad\n");
    return 0;
}   