#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_THREADS 10

pthread_mutex_t th;
sem_t s;

volatile int bilDisp = 45522;
volatile int vendas[10] = {0};

volatile int vez[NUM_THREADS];
volatile int interessado[NUM_THREADS];

int semente;
int metodo;



void *funcao4(void *args)
{
    int id = *(int *)args;
    srand(semente + id);
    int numVendidos_na_Thread = 0;

    while (numVendidos_na_Thread < 1500) {
        int b = 1 + rand() % 4;

        if (numVendidos_na_Thread + b > 1500) {
            b = 1500 - numVendidos_na_Thread;
        }

        numVendidos_na_Thread += b;

        // Início da seção crítica
        interessado[id] = 1;
        vez[id] = 1;
        for (int j = 0; j < NUM_THREADS; j++) {
            if (j != id) {
                vez[id] = j;
                while (interessado[j] && vez[id] == j)
                    ; // Espera ocupada
            }
        }

        // Seção crítica
        bilDisp -= b;
        vendas[id] += b;

        interessado[id] = 0;
        // Fim da seção crítica
    }

    pthread_exit(NULL);
    return NULL;
}


 void *funcao3(void *args){
    int id = *(int *)args;

    //printf("Thread %d\n", id);
    srand(semente + id);
    int numVendidos_na_Thread=0;
    while(numVendidos_na_Thread<1500){
         int b = 1 + rand() % 4;
         
         if(numVendidos_na_Thread + b > 1500){
            
            b = (1500 ) -(numVendidos_na_Thread );

         }
         
         numVendidos_na_Thread +=b;
         sem_wait(&s);
         bilDisp -= b;
         vendas[id] += b;
         sem_post(&s);
    }   
    
    pthread_exit(NULL);


    return (NULL);
    
 }   

void peterson()
{
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        interessado[i] = 0;
        vez[i] = 0;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, funcao4, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    int total = 0;
    for (int i = 0; i < 10; i++) {
        total += vendas[i];
    }
    int capacidade = bilDisp + total;

    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
}


void semaforo(){
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];
    sem_init(&s,0,1);
    for (i = 0; i < NUM_THREADS; i++) ids[i]=i;
    
    for(i=0;i < NUM_THREADS;i++)
         pthread_create(&threads[i], NULL, funcao3, &ids[i]);
    
     for(i=0;i < NUM_THREADS;i++) 
         pthread_join(threads[i],NULL);

    int total =0;
    for(i= 0; i<10; i++)
    {
        total += vendas[i];
    }    
    int capacidade = bilDisp + total; 
    
    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
}


void *funcao2(void *args)
{
    

    int id = *(int *)args;

    //printf("Thread %d\n", id);
    srand(semente + id);
    int numVendidos_na_Thread=0;
    while(numVendidos_na_Thread<1500){
         int b = 1 + rand() % 4;
         
         if(numVendidos_na_Thread + b > 1500){
            
            b = (1500 ) -(numVendidos_na_Thread );

         }
         numVendidos_na_Thread +=b;
         pthread_mutex_lock(&th);
         bilDisp -= b;
         vendas[id] += b;
         pthread_mutex_unlock(&th);
    }   
    
    pthread_exit(NULL);


    return (NULL);
}   

void mutex(){
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];
    pthread_mutex_init(&th,NULL);
    for (i = 0; i < NUM_THREADS; i++) ids[i]=i;
    
    for(i=0;i < NUM_THREADS;i++)
         pthread_create(&threads[i], NULL, funcao2, &ids[i]);
    
     for(i=0;i < NUM_THREADS;i++) 
         pthread_join(threads[i],NULL);

    int total =0;
    for(i= 0; i<10; i++)
    {
        total += vendas[i];
    }    
    int capacidade = bilDisp + total; 
    
    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
}

void *funcao(void *args)
{
    

    int id = *(int *)args;

    //printf("Thread %d\n", id);
    srand(semente + id);
    int numVendidos_na_Thread=0;
    while(numVendidos_na_Thread<1500){
         int b = 1 + rand() % 4;
         
         if(numVendidos_na_Thread + b > 1500){
            
            b = (1500 ) -(numVendidos_na_Thread );

         }
         numVendidos_na_Thread +=b;
         bilDisp -= b;
         vendas[id] += b;
    }   
    
    pthread_exit(NULL);


    return (NULL);
}   
int main (int argc ,char * argv[])
{
    printf("\nBilheteira do EstÃ¡dio de Anfield\n");
    semente = atoi(argv[1]);
    metodo = atoi(argv[2]);
    pthread_t threads[NUM_THREADS];
    int i, ids[NUM_THREADS];
    if(1== metodo) mutex();
    else if (2 == metodo) semaforo();
    else if(3 == metodo ) peterson();
   else{
    for (i = 0; i < NUM_THREADS; i++) ids[i]=i;
    
    for(i=0;i < NUM_THREADS;i++)
         pthread_create(&threads[i], NULL, funcao, &ids[i]);
    
     for(i=0;i < NUM_THREADS;i++) 
         pthread_join(threads[i],NULL);

    int total =0;
    for(i= 0; i<10; i++)
    {
        total += vendas[i];
    }    
    int capacidade = bilDisp + total; 
    
    fprintf(stderr, "Capacidade calculada %d (45522?)\n", capacidade);
    }
     return 0 ; 
}