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

int main(){
    int pid;
    
    pipe(pipe1);
    pipe(pipe2);
}