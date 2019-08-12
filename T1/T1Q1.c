#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
    int v[20];
    int t;

    printf("Digite vinte valores inteiros: \n");

    int i;
    for(i = 0; i < 20; i++){
        scanf("%d", &v[i]);
    }

    printf("Digite o intervalo de impressão por segundo: ");
    scanf("%d",&t);
    
    int j = 0;
    for(i = 1; i <= 20; i++){
        if (j == t) {
            sleep(1);
            j = 0;
        }
        printf("Item %d: %d \n", i, v[i-1]);
        j++;
    }


    return 0;
}
