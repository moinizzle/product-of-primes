# Instructions
```shell
$ make
gcc -Wall -Werror -std=gnu99 -c pfact.c 
gcc -Wall -Werror -std=gnu99 -c filter.c 
gcc -Wall -Werror -std=gnu99 -c pipeline_stage.c 
gcc -Wall -Werror -std=gnu99 -o pfact pfact.o filter.o pipeline_stage.o -lm

$ ./pfact 33
33 3 11
Number of filters = 3
```
