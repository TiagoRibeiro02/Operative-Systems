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

int pipe1[2];

void client(){
    int x,y,res;
    scanf("%d %d", &x, &y);
    write(pipe1[1], &x, 4);
    write(pipe1[1], &y, 4);
    read(pipe1[0], &res, 4);
    printf("%d\n", res);
}

void server(){
    int x,y,res;
    read(pipe1[0], &x, 4);
    read(pipe1[0], &y, 4);
    res = x+y;
    write(pipe1[1], &res, 4);
}

int main(){
    int pid;
    
    pipe(pipe1);
    pid=fork();
    if (0==pid)
    {
        server();
    }
    else{
        client();
    }
    
}