#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t child1, child2;
    int status, status2;

    // at least, there should be 3 arguments
    // 2 for the first command, and the rest for the second command
    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }

    // TODO

    // create fork
    child1 = fork();

    // if fork was not correctly created
    if (child1 == -1) {
        perror("fork()");
        exit(-1);
    } else if (child1 == 0) {
        // execlp takes in an established number of parameters - last one must be a NULL
        execlp(argv[1], argv[1], argv[2], NULL);
        // only executes if execlp failed
        perror("execlp())");
        exit(-1);
    } else {
        // waits for the child to finish
        if(waitpid(child1, &status, 0) > 0){
            // if the child succesfully terminated
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                printf("exited=%d exitstatus=%d\n", WIFEXITED(status), WEXITSTATUS(status));
            } else {
                printf("1st child didn't terminate properly\n");
            }
            
            // in parent - create a new child 
            child2 = fork();

            // only executes if child was not properly created
            if(child2 == -1){
                perror("fork()");
                exit(-1);

            // if child is properly created
            } else if(child2 == 0) {
                // pointer arithmetic used to move argv past the first 3 command line arguments - first 2 used in the first child
                // this moves it to the second part that we need to use
                argv += 3;
                execvp(argv[0], argv);
                // executes only if execvp fails
                perror("execvp");
                exit(-1);

            } else {
                // waits for the child to finish
                if(waitpid(child2, &status2, 0) > 0){
                    // if succesful
                    if(WIFEXITED(status2) && !WEXITSTATUS(status2)) {
                        printf("exited=%d exitstatus=%d\n", WIFEXITED(status2), WEXITSTATUS(status2));
                    } else {
                        printf("2nd child didn't terminate properly");
                    }
                }
            }

        }
    }

    return 0;
}