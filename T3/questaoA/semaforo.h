#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun 
{
	int val;
};

class Semaforo
{
	public:
		int sem_id;               //Identificador do semáforo
		int num_sems;             //Número de semáforos- sugere-se valor igual a 1: semáforo escalar
		union  semun sem_union;   //union utilizada para a função semtcl()
		struct sembuf sem_b;      //Estrutura utilizado para semop()
		int retorno_inicio, valor_final;

		Semaforo(key_t chave, int val_inicial, int sem_flags)
		{

			//val_inicial - valor sugerido = 1
			//sem_flags - valor sugerido = 0666 | IPC_CREAT

			num_sems = 1;
			sem_b.sem_num = 0; //Uma operação
			sem_b.sem_flg = SEM_UNDO;

			sem_union.val = val_inicial;

			//Criando um semáforo.
			sem_id = semget(chave,num_sems, sem_flags); 

			//Iniciando o semáforo.
			retorno_inicio = semctl(sem_id,0,SETVAL, sem_union);
		}

		Semaforo(key_t chave,int sem_flags)
		{

			//val_inicial - valor sugerido = 1
			//sem_flags - valor sugerido = 0666 | IPC_CREAT

			num_sems = 1;
			sem_b.sem_num = 0; //Uma operação
			sem_b.sem_flg = SEM_UNDO;


			//Criando um semáforo.
			sem_id = semget(chave,num_sems, sem_flags); 

		}

		void down(void)
		{
			sem_b.sem_op = -1;
			semop(sem_id, &sem_b,1);
		}

		void up(void)
		{
			sem_b.sem_op = 1; 
			semop(sem_id, &sem_b,1);
		}

		~Semaforo(void)
		{
			//union semun sem_union2;
			valor_final = semctl(sem_id,0,IPC_RMID,sem_union);
		}
};

