#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    time_t tp = time((time_t *) 0);
    
    time_t dataHora;
    (void) time(&dataHora);
    
    int n;
    printf("Digite o n-esimo indice de Fibonacci: ");
    scanf("%d",&n);
    
    int a = 0;
    int b = 1;
    int atual;
    
    int i;
    
    for(i = 0; i < n; i++){

        printf("Tempo de CPU alocado ao programa ate o momento: %ld\n", clock());
        printf("Tempo real transcorrido desde o inicio da execucao do programa: %ld\n", (time_t) difftime(time((time_t *) 0), tp));
        printf("Data/Hora local do sistema: %s", ctime(&dataHora));
        
        printf("#%d: %d\n\n", i+1, a);
        sleep(a);
        
        atual = a;
        a += b;
        b = atual;
    }    
    
    return 0;
}

