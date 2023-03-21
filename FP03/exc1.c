#include <stdio.h>
void main(){
    int pid, x = 3;  
    pid = fork();    
    if(0 == pid)  
    {  
        fork();  
        pid = fork();  
        x--; 
        if (0 == pid){ x--;} 
    } else { 
        x++;
    }   
    printf("x=%d\n ",x);
}