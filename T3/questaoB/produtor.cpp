#include "semaforo.h"
#include <time.h>
#include <sys/shm.h>

#define CHAVE_MEM 1       //Chave que ira identificar a memoria compartilhada a ser criada.
#define CHAVE_MEM2 2       //Chave que ira identificar a memoria compartilhada a ser criada.
#define CHAVE_SEM_0 121   //Chave que ira identificar o primeiro semaforo a ser criado.

#define TAM_BUFFER 5

struct itemBuffer{
    pid_t pid;
    time_t tempo_real;
    clock_t num_clocks;
};

const int TAM_MBUFFER = sizeof(itemBuffer)*5;  //Tamanho da memoria compartilhada que sera criada.
const int TAM_MCOUNT = sizeof(int);  //Tamanho da memoria compartilhada que sera criada.

int main(){

    int memID;                  //Identificador da memoria compartilhada a ser criada.
    void *memAux = (void *) 0;  //Ponteiro para a memoria compartilhada a ser criada.
    struct itemBuffer *mem;          //Ponteiro para a manipular a memoria compartilhada a ser criada.
 
    memID = shmget((key_t) CHAVE_MEM, TAM_MBUFFER, 0666|IPC_CREAT);    //Criacao de uma memoria compartilhada.
    if (memID == -1){
        //Houve erro durante a criacao da memoria compartilhada.
        fprintf(stderr, "Shmget da memoria falhou\n");       //Impressao do erro ocorrido.
        exit(EXIT_FAILURE);	                             //Saida do processo por erro.
    }

    memAux = shmat(memID, (void *) 0, 0);  //Associacao da memoria compartilhada criada ao processo atual.
    if (memAux == (void *) -1){
        //Houve ero durante a associacao da memoria criada ao processo atual.
        fprintf(stderr, "Shmat da memoria falhou\n");       //Impressao do erro ocorrido.
        exit(EXIT_FAILURE);                                 //Saida do processo por erro.
    }

    mem = (struct itemBuffer*) memAux;   //Conversao para viabilizar a manipulacao da memoria compartilhada criada e associado ao processo atual.
    
    int memID2;                  //Identificador da memoria compartilhada a ser criada.
    void *memAux2 = (void *) 0;  //Ponteiro para a memoria compartilhada a ser criada.
    int *qItens;          //Ponteiro para a manipular a memoria compartilhada a ser criada.
    
    memID2 = shmget((key_t) CHAVE_MEM2, TAM_MCOUNT, 0666|IPC_CREAT);    
    if (memID2 == -1){
        fprintf(stderr, "Shmget da memoria falhou\n");     
        exit(EXIT_FAILURE);	                          
    }

    memAux2 = shmat(memID2, (void *) 0, 0);  
    if (memAux2 == (void *) -1){
        fprintf(stderr, "Shmat da memoria falhou\n");
        exit(EXIT_FAILURE);                                
    }
    
    qItens = (int*) memAux2;

    Semaforo    S0(CHAVE_SEM_0, 0, 0666|IPC_CREAT);

    pid_t pid = fork();
    switch(pid){
        case -1:
            printf("Erro na criacao dos processos!\n");
            exit(EXIT_FAILURE);
            break;
        case 0:
            execv("consumidor", NULL);
            break;
        default:
            *qItens = 0;
            break;
    }
    
    while(1){
        S0.down();
        if(*qItens < TAM_BUFFER){
                printf("Inserção de item iniciada!\n");
                
                mem[*qItens].pid = getpid();
                mem[*qItens].tempo_real= time((time_t *) 0);
                mem[*qItens].num_clocks = clock(); 
                
                printf("Inserção de item no buffer bem-sucedida!\n");
                
                printf("---Buffer---\n");
                for(int i = 0; i <= *qItens; i++){
                    printf("PID do processo produtor: %d\n", mem[*qItens].pid);
                    printf("Tempo real (em segundos): %ld\n", mem[*qItens].tempo_real);
                    printf("Numero de ciclos de CPU alocados: %ld\n", mem[*qItens].num_clocks);
                    printf("Posição: %d\n", *i+1);
                    printf("\t---\n");
                }
                printf("------\n");
                *qItens += 1;
        }
        S0.up();
        printf("Produtor dormindo por 5 segundos!\n");
        sleep(5);
    }
    
}