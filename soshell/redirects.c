#include "shell.h"

#define FILE_MODE (S_IRUSR | S_IWUSR)

// redirects.c

// redirects tratamento dos simbolos por ordem inversa: i) 2> ii) > OU > iii) <

int redirects(int numargs, char *args[])
{
    // i tratar do redirect do 2>
    if (numargs < 3){
        return numargs; // Guard the following section
    }
    if (strcmp(args[numargs - 2], "2>") == 0)
    {
        int fd = creat(args[numargs - 1], FILE_MODE);
            if (fd < 0)
            {
                perror(NULL);
                exit(1); /*indicar um erro*/
            }
        dup2(fd, STDERR_FILENO);
        close(fd);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }
    // ii tratar do redirect do >
    if (numargs < 3){
        return numargs; // Guard the following section
    }
    if (strcmp(args[numargs - 2], ">") == 0)
    {
        int fd1 = creat(args[numargs -1], FILE_MODE);
        if (fd1 < 0)
        {
            perror(NULL);
            return -1;
        }
        dup2(fd1, STDOUT_FILENO);
        close(fd1);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
        
    }
    else
    {
        // verificar casos de (>) ou append (>>)
        // tratar do > creat ou >> open O_WRONLY | O_APPEND
        if (strcmp(args[numargs -2], ">>") == 0)
        {
            int fd2 = open(args[numargs -1], O_WRONLY | O_APPEND);
            if (fd2 < 0)
            {
                perror(NULL);
                return -1;
            }
            dup2(fd2, STDOUT_FILENO);
            close(fd2);
            args[numargs - 2] = NULL;
            numargs = numargs - 2;
        }
    }
    if (numargs < 3){
        return numargs; // Guard the following section
    }
    // iii tratar do < open O_RDONLY
    if (strcmp(args[numargs -2], "<") == 0)
    {
        int fd3 = open(args[numargs -1], O_RDONLY);
        if (fd3 < 0)
        {
            perror(NULL);
            return -1;
        }
        dup2(fd3, STDIN_FILENO);
        close(fd3);
        args[numargs - 2] = NULL;
        numargs = numargs - 2;
    }
    
    return numargs; // devolver o numero de argumentos a passar para execvp
}