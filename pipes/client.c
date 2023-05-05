#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <wait.h>

#define FIFO1 "/tmp/f1"
#define FIFO2 "/tmp/f2"
#define PERMS 0666

int pipe1[2];
int pipe2[2];

void client(){
    int x,y,res;
    scanf("%d %d", &x, &y);
    write(pipe1[1], &x, 4);
    write(pipe1[1], &y, 4);
    read(pipe2[0], &res, 4);
    printf("%d\n", res);
}

int main(){
    pipe1[1] = open(FIFO1, 1);
    pipe2[0] = open(FIFO2, 0);

    //ola teste

    client();
}

