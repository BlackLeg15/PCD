#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("\n---------------------------------\n");
    char message[15];
    strcpy(message, "Processo Pai2");
    printf("%s: \n", message);

    pid_t neto3, neto4;
    int cochilo;
    

    neto3 = fork();
    switch(neto3){
        case -1:
            exit(1);
            break;
        case 0:
            execv("neto3", NULL);
            break;
        default:
            neto4 = fork();
            switch(neto4){
                case -1:
                    exit(1);
                    break;
                case 0:
                    execv("neto4", NULL);
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
    
    printf("%s suspendendo ate que os processos neto 3 e neto 4 sejam concluidos.\n", message);
    printf("\n---------------------------------\n");
    wait();
    printf("\n---------------------------------\n");
    wait();
    printf("\n---------------------------------\n");
    printf("%s finalizado!\n", message);
    exit(0);
}
