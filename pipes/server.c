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

void server(){
    int x,y,res;
    read(pipe1[0], &x, 4);
    read(pipe1[0], &y, 4);
    res = x+y;
    write(pipe2[1], &res, 4);
}

int main(){
    mknod(FIFO1,S_IFIFO|PERMS,0);
    mknod(FIFO2,S_IFIFO|PERMS,0);
    pipe1[0] = open(FIFO1, 0);
    pipe2[1] = open(FIFO2, 1);
    server();
}