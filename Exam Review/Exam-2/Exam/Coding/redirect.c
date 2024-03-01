#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/stat.h>

//redirect standard input to the specified file
void redirectStdin(const char *filename)
{
        int fd = open(filename, O_RDONLY);
        if(fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
	//TODO
        //fill in the code below
        dup2(fd, 0);
        close(fd);

}

//redirect standad output to the specified file
void redirectStdout(const char *filename)
{
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if(fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
	//TODO
	//fill in the code below
        dup2(fd, 1);
        close(fd);
}

//TODO: imeplement the following function
// if word has letters in strict alphabetical order, return 1 else return 0
int increasing(char *word)
{
        if(strlen(word)<5) return 0;
        //TODO
        int i, j;

        // two for loops used to cycle through every letter and compare each letter to one letter at a time
        for (i = 0; i < strlen(word) - 1; i++) {
                // this for loop has i keep the same letter and compare all other letters that go after
                for (j = i + 1; j < strlen(word); j++) {
                        // makes comparison - if the letter before is bigger - then it return 0
                        if (word[i] >= word[j]) {
                                return 0;
                        // if the letters are in order - for loop continues
                        } else {
                                continue;
                        }
                }
        }
        // if the for loops did not return 0 - that means the word is in order 
        return 1;
}
