#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>


#include <stdbool.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>

#include "meeseeks.c"

int main(int argc, char** argv)
{
    char cmd, opt;

    while (1)
    {
        printf("Hola! Un gusto volver a verte! ¿Deseas hacer una solicitud nueva? (S/N) ");
        scanf("%s", &opt);
        if(opt == 'S' || opt == 's'){                   
            printf("Ha elegido %c\n", opt);
            pid_t pid_init = fork();
            if(pid_init == 0){
                mrMesseks();
                //while(wait(NULL) >0 );                
                break;
            }
            else {
                wait(NULL);
            }
        }
        else if (opt == 'N' || opt == 'n'){
            printf("Ha elegido %c\n", opt);
            break;
        }
        else {
            printf("Opcion invalida");
            break;
        }
    }

    return 0;
}
