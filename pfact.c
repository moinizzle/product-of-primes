#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>


#include "eratosthenes.h"

#define PRIME "%d is prime\n"
#define FILTNUM "Number of filters = %d\n"
#define MAXFILT 255

int scanFacts(int, int, int*);

int main(int argc, char *argv[]) {
    
    // 0 is read
    // 1 is write

    // file descriptor
    int factor = 0; 
    int pipes[2];

    // i kept forgetting to set it to 2
    int two;

    // error handling
    // add print msgs after

    // if there's no args or too many
    
    if(argc != 2){
        fprintf(stderr, "Usage:\n\tpfact n\n");
        exit(1);
    }

    char *p;
    int n = strtol(argv[1], &p, 10);

    // if 1 is given

    if( atoi(argv[1]) == 1){
        printf(PRIME, atoi(argv[1]) );
        printf(FILTNUM, 0);
        exit(0);
    }

    // if a natural number is not given
    // also covers the negative number case

    if( atof(argv[1]) < 1 || atof(argv[1]) != atoi(argv[1]) ){
        fprintf(stderr, "Usage:\n\tpfact n\n");
        exit(1);
    }

    // Turning off sigpipe
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // pipe error

    int *pointer_ftr;
    pointer_ftr = &factor; 

    if (pipe(pipes) == -1){
        exit(2);
    }

    int pid = fork();

    // fork error 

    // if everything goes well


    //PARENT

    if (pid < 0){
        exit(2);
    }

    else if(pid > 0) {
        //int i;
        //close read
        //int filter = 0;
        if (close(pipes[0]) < 0){
            exit(2);
        }
        // start from 2
        for(int i = 2; i <= n; i++){
            if(write(pipes[1], &i, sizeof(int)) != sizeof(int)){
                if(close(pipes[1]) < 0){
                    exit(2);
                }
            }
        }

    // exit after
    if(close(pipes[1]) < 0){
        exit(2);
    }

    int waitTemp;
    if(wait(&waitTemp) > 0){
        //printf("%d", waitTemp);
        if(WIFEXITED(waitTemp)){
            int filter = WEXITSTATUS(waitTemp);
            // max filter
            if (filter == MAXFILT){
                exit(2);
            }
            printf(FILTNUM, filter);
            exit(0);
        }
    }
    // handle more errs
    }

    // 0 is child    
    
    else if(pid == 0){

        int t = 0;

        if (close(pipes[1]) < 0 ){
            exit(3);
        }


        int dummy = pipes[0];

        two = 2;

        while(scanFacts(n, two, pointer_ftr) == 1){

            int *fd_stage;

            int stage = make_stage(two, dummy, &fd_stage);

            if(stage == 0){
                // pass in the pointer
                dummy = fd_stage[0];
                read(dummy, &two, sizeof(int));
            }

            else {
                int w;
                
                if(wait(&w) > 0) {
                    if(WIFEXITED(w)){
                        t = WEXITSTATUS(w);

                        if (close(dummy) < 0 ){
                            exit(3);
                        }

                        if(t == MAXFILT){
                            exit(3);
                        }

                        else {
                            int x = t + 1; 
                            exit(x);
                        }
                    }
                }
                else {
                    exit(3);
                }
            }

        }
    exit(0);
    }
    exit(0);
}

int scanFacts(int n, int f, int *factor){

    // if factor

    if(n%f == 0){
        
        if( (n/f) % f  == 0  ){
            printf("%d is not the product of two primes\n", n);
            return 0;
        }

        if(*factor == 0) {
            *factor = f;
            return 1;
        }

        else {

            if(n == *factor * f ){
                printf("%d %d %d\n", n, *factor, f);
                return 0;
            }

            else{
                printf("%d is not the product of two primes\n", n);
                return 0;
            }
        }
    }

    if(n == f){
        printf("%d is prime\n", n);
        return 0;
    }

    if((*factor == 0) && (f > (int) sqrt(n)) ){
        printf("%d is prime\n", n);
        return 0;
    }

    if(n == f*f){
        printf("%d %d %d\n", n, f, f);
        return 0;
    }

    if( (*factor != 0) && (f >= sqrt(n) )){
        printf("%d %d %d\n", n, *factor, n / (*factor));
        return 0;
    }

    // if nothing works
    else {
        return 1;
    }

}


