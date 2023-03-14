#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int v[10];
    int descriptor = 0;

    descriptor = open(argv[1], O_RDONLY);

    if (descriptor < 0)
    {
        sprintf("oops error %s", argv[1]);
    }
    

    read(descriptor, v, sizeof(int)*10);
    
    printf("Array de inteiros lido: ");
    for(int i = 0; i < 10; i++){
        printf("%d ", v[i]);   
    }
    printf("\n");
       
    close(descriptor);

    return 0;
}


//usando strace vai mostrar 3 pois o canal 1 e 2 já está ocupado pelo stdin e stdout