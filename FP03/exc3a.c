#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
int main() { 
  srand(46346);  //xxxx no aluno 
  int vetor[100], inicio=rand();   
  for ( int i=0; i <100 ; i++ )  vetor[i]=inicio+i; 
  int fd = creat ( "ints.bin", S_IRUSR | S_IWUSR); 
  write(fd, vetor, 100*sizeof(int) ); 
}