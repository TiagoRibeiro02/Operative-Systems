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

void calc(char *value1, char *op, char *value2);

void bits(char *op1, char *op, char *op2);

int isjpeg(int fileDescriptor);

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args, int numargs);


/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
