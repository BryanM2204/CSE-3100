#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{
    // TODO
    
    // create structure that contains id and matricies of thread from p_arg
    thread_arg_t * t_arg = (thread_arg_t *)p_arg;
    // set the bounds - only half of the array is used for each thread
    int start, end;

    // check the id of t_arg - checks which thread is being used
    if(t_arg->id == 0){
        // if its the first thread - set the bounds from the beginning to halfway
        start = 0;
        end = t_arg->m->nrows / 2;
    } else{
        // else - set the bounds from halfway as the beginning to the end
        start = t_arg->m->nrows / 2;
        end = t_arg->m->nrows;
    }

    // create a nested for loop using the bounds for the first for loop
    // the second for loop goes through all the columns of the matrix
    for (int i = start; i < end; i++)  {
        for (int j = 0; j < t_arg->m->ncols; j++) {
            // this is similar to the regular addMatrix function in the matrix.c file
            // adds both values from matrix m and n up at the same location 
            t_arg->t->data[i][j] = t_arg->m->data[i][j] + t_arg->n->data[i][j];
        }
    }
}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;

    // TODO

    // divide and conquer
    int half = m->nrows / 2;

    // create the arguments to be passed on to thread_main
    thread_arg_t arg1 = {0, m, n, t};
    thread_arg_t arg2 = {1, m, n, t};

    // create the threads - check if threads are succesfully made 
    pthread_t threads[NUM_THREADS];
    if(pthread_create(&threads[0], NULL, thread_main, &arg1) != 0){
        perror("pthread_create");
        exit(1);
    }
    if(pthread_create(&threads[1], NULL, thread_main, &arg2) != 0){
        perror("pthread_create");
        exit(1);
    }

    // wait for the threads to finish before returning t
    if(pthread_join(threads[0], NULL) != 0){
        perror("pthread_join");
        exit(1);
    }
    if(pthread_join(threads[1], NULL) != 0){
        perror("pthread_join");
        exit(1);
    }

    // returns the final matrix
    return t;
}
