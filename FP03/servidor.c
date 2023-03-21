#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char linha[200];
    char s1[3] = "", s2[100] = "";
    int a, b;
    fgets(linha, 200, stdin);
    sscanf(linha, "%s %d %d %s", s1, &a, &b, s2);
    printf("%s %d %d %s\n", s1, a, b, s2);

    if (a == 0)
    {
        printf("ola");
    }
    
    int pid;
    if (strcmp(s1, "NG"))
    {
        printf("aaaa");
        pid = fork();
        if (0 == pid)
        {
            int fd = open(s2, O_RDONLY);
            printf("entrei aqui");
        }
        main();
    }
    else if (s1 == "NE")
    {
        return 0;
    }
    return 0;
}

