#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    // TODO

    // assign the p_arg to t_arg 
    thread_arg_t * t_arg = (thread_arg_t *)p_arg;

    // declare int variables start and end
    int start, end;

    // if its the first thread - then assign start to the beginning and the end to the middle of matrix m
    if(t_arg->id == 0){
        start = 0;
        end = t_arg->m->nrows / 2;
    } else {
        // else - second thread deals with second half
        start = t_arg->m->nrows / 2;
        end = t_arg->m->nrows;
    }

    // nested for loop created that goes through every row and column of each matrix
    for(int i= start; i < end; i++){
        for(int j = 0; j < t_arg->m->ncols; j++){
            TElement sum = (TElement)0;
            for(int k = 0; k < t_arg->m->ncols; k++){
                // multiples and then add to the total sum
                sum += t_arg->m->data[i][k] * t_arg->n->data[k][j];
            }
            // assign the sum to that specific index in the matrix
            t_arg->t->data[i][j] = sum;
        }
    }

    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    if (t == NULL)
        return t;

    // TODO


    // create 2 thread_arg_t structs - initialize the arguments
    thread_arg_t arg1 = {0, m, n, t};
    thread_arg_t arg2 = {1, m, n, t};

    // create array of threads
    pthread_t threads[NUM_THREADS];

    // create thread - if thread does not work - return perror 
    if(pthread_create(&threads[0], NULL, thread_main, &arg1) != 0){
        perror("pthread_create");
        exit(1);
    } 
    if(pthread_create(&threads[1], NULL, thread_main, &arg2) != 0){
        perror("pthread_create");
        exit(1);
    }

    if(pthread_join(threads[0], NULL) != 0){
        perror("pthread_join");
        exit(1);
    } 

    if(pthread_join(threads[1], NULL) != 0){
        perror("pthread_join");
        exit(1);
    }

    return t;
}
