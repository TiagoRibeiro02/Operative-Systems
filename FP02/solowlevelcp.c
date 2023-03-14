#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

void ioCopy(int IN, int OUT, int BS);

int main(int argc, char *argv[])
{
    int BUFFSIZE = atoi(argv[3]);

    int fdIn = open(argv[1], O_RDONLY);
    if (fdIn == -1)
    {
        printf("Error Number % d\n", errno);
        perror("open failed");
    }

    int fdOut = creat(argv[2], S_IRUSR | S_IWUSR);
    if (fdOut == -1)
    {
        printf("Error Number % d\n", errno);
        perror("creat failed");
    }

    clock_t inicio, fim;
    float tempoUsado;
    inicio = clock();

    ioCopy(fdIn, fdOut, BUFFSIZE);

    fim = clock();
    tempoUsado = (float)(fim - inicio) / (float)CLOCKS_PER_SEC;

    fprintf(stderr, "Copia Feita com BlockSize %d Tempo do CPU %f\n", BUFFSIZE, tempoUsado);

    return (0);
}
void ioCopy(int IN, int OUT, int BS) // no error reporting
{
    int n;
    char *buf = malloc(BS);
    while ((n = read(IN, buf, BS)) > 0)
    {
        if (write(OUT, buf, n) != n)
            perror("Erro de escrita!\n");
    }
    if (n < 0)
        perror("Erro de leitura!\n");
}