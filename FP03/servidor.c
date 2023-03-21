#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void shownum(int a, int b)
{
    FILE *file = fopen("ints.bin", "rb");
    if (file == "")
    {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    int nums[100];
    fread(nums, sizeof(int), 100, file);
    fclose(file);
    printf("Números no intervalo [%d, %d]:\n", a, b);
    for (int i = a; i <= b; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void shownumtofile(char *fileName, int a, int b)
{
    FILE *file = fopen("ints.bin", "rb");
    FILE *file2 = fopen(fileName, "w");
    if (file == "")
    {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    
    if (file2 == "")
    {
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    int nums[100];
    fread(nums, sizeof(int), 100, file);
    fclose(file);
    printf("Números no intervalo [%d, %d] foram guardados\n", a, b);
    for (int i = a; i <= b; i++)
    {
        fwrite(&nums[i], sizeof(int), 1, file2);
    }
    fclose(file2);
    
}

int main()
{

    while (1)
    {
        char linha[200];
        char s1[3] = "", s2[100] = "";
        int a, b;
        fgets(linha, 200, stdin);
        sscanf(linha, "%s %d %d %s", s1, &a, &b, s2);
        // printf("%s %d %d %s\n", s1, a, b, s2);

        if (strcmp(s1, "EX") == 0)
        {
            printf("Terminando...\n");
            break;
        }
        else if (strcmp(s1, "NG") == 0)
        {
            if (strcmp(s2, "") == 0)
            {
                shownum(a,b);
                continue;
            }
            else
            {
                shownumtofile(s2,a,b);
                continue;
            }
        }
        else if (strcmp(s1, "NE") == 0)
        {
            int pid = fork();
            if (pid == 0)
            {
                if (strcmp(s2, "") == 0)
                {
                    shownum(a,b);
                    break;
                }
                else
                {
                    shownumtofile(s2,a,b);
                    break;
                }
            }
            else
            {
                wait(NULL);
            }
        }
        else
        {
            printf("Protocolo desconhecido\n");
        }
    }

    return 0;
}
