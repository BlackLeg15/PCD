#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("\n---------------------------------\n");
    int cochilo;
    char message[15];
    strcpy(message, "Processo Neto2");
    printf("%s: \n", message);
    printf("\n---------------------------------\n");
    cochilo = 10*(getpid() - getppid());
    printf("%s dormindo por %d segundos.\n", message, cochilo);
    printf("\n---------------------------------\n");
    sleep(cochilo);
    printf("\n---------------------------------\n");
    printf("%s acordou.\n", message);
    printf("\n---------------------------------\n");
    printf("%s finalizado!\n", message);
    printf("\n---------------------------------\n");
    exit(0);
}