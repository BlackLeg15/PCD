#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("\n---------------------------------\n");
        char message[15];
        strcpy(message, "Processo Avo");
	printf("%s: \n", message);

	pid_t pai1, pai2;

	pai1 = fork();
        switch(pai1){
            case -1:
                exit(1);
                break;
            case 0:
                execv("pai1", NULL);
                break;
            default:
                pai2 = fork();
                switch(pai2){
                    case -1:
                        exit(1);
                        break;
                    case 0:
                        execv("pai2", NULL);
                        break;
                    default:
                        break;
                } 
                break;
        }              
        printf("\n---------------------------------\n");
        printf("%s suspendendo ate que os processos pais sejam concluidos.\n", message);
        printf("\n---------------------------------\n");
        wait();
        printf("\n---------------------------------\n");
        wait();
        printf("\n---------------------------------\n");                        
        printf("%s finalizado!\n", message);
        printf("\n---------------------------------\n");
        exit(0);
}

