#include <stdio.h>
#include <dirent.h>
#include "shell.h"

void listar(char *pasta){
    if (pasta == NULL)
    {
        pasta = ".";
    }

    DIR *d;
    struct dirent *dir;
    d = opendir(pasta);
    if(d){
        while ((dir = readdir(d)) != NULL)
        {
            printf("%lld %s %i\n ", (long long)dir->d_ino, dir->d_name, dir->d_reclen);
        }
        closedir(d);
    }
    
}