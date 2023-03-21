#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
            if (s2 == NULL)
            {
                printf("Protocolo desconhecido\n");
                continue;
            }
            else
            {
                FILE *file = fopen(s2, "rb");
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
        }
        else if (strcmp(s1, "NE") == 0)
        {
            int pid = fork();
            if (pid < 0)
            {
                printf("Erro ao criar processo filho\n");
                return;
            }
            if (pid == 0)
            { // processo filho
                if (s2 == NULL)
                {
                    printf("Protocolo desconhecido\n");
                    continue;
                }
                else
                {
                    FILE *file = fopen(s2, "rb");
                    if (file == NULL)
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
                    break;
                }
            }
            else
            { // processo pai
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
