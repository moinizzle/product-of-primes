#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"

#include <errno.h>

pid_t make_stage(int n, int read_fd, int **fds) {
    
    // malloc
    (*fds) = malloc(2*sizeof(int));

    // malloc fail
    if((*fds) == NULL){
        exit(3);
    }

    // pipe fail
    if(pipe(*fds) == -1){
        exit(3);
    }

    // malloc errors

    int a = fork();

    // CHILD
    // PARENT

    if (a > 0){

        if (filter(n, read_fd, (*fds)[1]) == 1) {
            close(*fds[1]);
            exit(3);
        }

        if(close((*fds)[0]) != 0){
            exit(3);
        }

        if(close((*fds)[1]) != 0){
            exit(3);
        }

        return n;
    }

    else if (a == 0){

        if(close(read_fd) != 0){
            exit(3);
        }
        
        if(close((*fds)[1]) != 0){
            exit(3);
        }
        
        // read_fd didn't close
        
        return 0;
    }

    else {
        exit(3);
    }
}



