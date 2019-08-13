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
		int sem_id;               //Identificador do sem�foro
		int num_sems;             //N�mero de sem�foros- sugere-se valor igual a 1: sem�foro escalar
		union  semun sem_union;   //union utilizada para a fun��o semtcl()
		struct sembuf sem_b;      //Estrutura utilizado para semop()
		int retorno_inicio, valor_final;

		Semaforo(key_t chave, int val_inicial, int sem_flags)
		{

			//val_inicial - valor sugerido = 1
			//sem_flags - valor sugerido = 0666 | IPC_CREAT

			num_sems = 1;
			sem_b.sem_num = 0; //Uma opera��o
			sem_b.sem_flg = SEM_UNDO;

			sem_union.val = val_inicial;

			//Criando um sem�foro.
			sem_id = semget(chave,num_sems, sem_flags); 

			//Iniciando o sem�foro.
			retorno_inicio = semctl(sem_id,0,SETVAL, sem_union);
		}

		Semaforo(key_t chave,int sem_flags)
		{

			//val_inicial - valor sugerido = 1
			//sem_flags - valor sugerido = 0666 | IPC_CREAT

			num_sems = 1;
			sem_b.sem_num = 0; //Uma opera��o
			sem_b.sem_flg = SEM_UNDO;


			//Criando um sem�foro.
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

