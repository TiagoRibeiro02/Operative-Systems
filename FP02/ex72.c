// ./ex72 ex72.c backup.c

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFSIZE 128

void ioCopy(int IN, int OUT);

int main(int argc, char *argv[])
{
    int fdIn = open(argv[1], O_RDONLY);
    if (fdIn == -1){
        printf("Erro %d\n", errno);
        perror("open failed");
    }
    
    int fdOut = creat(argv[2], S_IRUSR | S_IWUSR); 
    if(fdOut == -1){
        printf("Error % d\n", errno);  
        perror("creat failed");  
    }
    ioCopy(fdIn, fdOut);

    return 0;
}

void ioCopy (int IN, int OUT)
{ 
  int n;
  char buf[BUFFSIZE];
  while ( ( n = read (IN, buf, BUFFSIZE)) > 0)
  { 
    if (write (OUT, buf, n) != n)
      perror("Erro de escrita!\n");
  }
  if (n < 0)
    perror("Erro de leitura!\n");
}