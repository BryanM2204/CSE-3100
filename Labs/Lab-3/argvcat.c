#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    // TODO 
    // assign dynamically memory - add a +1 to account for 0 at end
    char *string = malloc(strlen(s1) + strlen(s2) + 1);
    if (string == NULL){
        my_error("Malloc used incorrectly");
    }
    strcpy(string, s1);
    strcat(string, s2);
    return string;
}

int main(int argc, char *argv[])
{
    char    *s;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        char *temp = my_strcat(s, argv[i]);
        //free the old s
        free(s);
        // assign the temp with s
        s = temp;
    }

    printf("%s\n", s);

    // free s 
    free(s);

    return 0;
}