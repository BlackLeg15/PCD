#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("\n---------------------------------\n");
    char message[15];
    strcpy(message, "Processo Pai1");
    printf("%s: \n", message);

    pid_t neto1, neto2;
    int cochilo;
    

    neto1 = fork();
    switch(neto1){
        case -1:
            exit(1);
            break;
        case 0:
            execv("neto1", NULL);
            break;
        default:
            neto2 = fork();
            switch(neto2){
                case -1:
                    exit(1);
                    break;
                case 0:
                    execv("neto2", NULL);
                    break;
                default:
                    break;
            }
            break;
    }
    
    cochilo = 5*(getpid() - getppid());
    printf("%s dormindo por %d segundos.\n", message, cochilo);
    printf("\n---------------------------------\n");
    sleep(cochilo);
    printf("%s acordou.\n", message);
    
    printf("%s suspendendo ate que os processos neto 1 e neto 2 sejam concluidos.\n", message);
    printf("\n---------------------------------\n");
    wait();
    printf("\n---------------------------------\n");
    wait();
    printf("\n---------------------------------\n");
    printf("%s finalizado!\n", message);
    exit(0);
}
