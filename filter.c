#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "eratosthenes.h"

int filter(int m, int readfd, int writefd) {

    int status;
    int n;

    while((status = read(readfd, &n, sizeof(int)) == sizeof(int))){
        
        if(0 != (n % m)){
            status = write(writefd, &n, sizeof(int));
            if(status != sizeof(int)){
                return 1;
            }
        }  
    }
    return 0;
}

