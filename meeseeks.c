#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>	
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h> 
#include <assert.h>
#include <errno.h>
#include <signal.h>

static sem_t *sem;
static int *meeseeksQuan;
static int *maxLevel;
static char *flag;
static clock_t *timer;
static clock_t *meeseeks_clock;

void caos();
void init();
void start_clock();
void getLineAnySize(char** textoEntrada);
int askForHelp(double dificulty);
bool done(int level, double dificulty, int quantity, int maxLevel);
int mrMeeseeks();

typedef struct {
	int slavesNum;
	int slaveId;
	int level;
} status;

int mrMesseks()
{
    init();
    
    pid_t pid; 
	char aux;
    char *job = (char*)malloc ( 16*sizeof(char) ); //Dynamic pointer to save the job
	double ease_lvl = 0;
	int globalVar = 0, newMeeseeks = 0;
    int num1, num2, result; // For math operations
    char prog[100], *argsp[100]; // For external program execution
    status state;
	state.slavesNum = 0;
	state.slaveId = 0;
	state.level = 0;
    int qua = 0;
    int max = 1000;
    int jobPipe[2]; //Pipe used to send the job
	int statePipe[2]; //Pipe used to send the structure created

	if(pipe(jobPipe) == -1){ //Job pipe initialization 
		fprintf(stderr,"Pipe Failed");
		return 1;
	}

	if(pipe(statePipe) == -1){ //Struct pipe initialization
		fprintf(stderr,"Pipe Failed");
		return 1;
	}

    srand(time(NULL));

    setbuf(stdin, NULL);

    printf("\n¿Qué desea que haga? ");
    getLineAnySize(&job);
    setbuf(stdin, NULL);
    printf("Bien, voy a intentar %s\n", job);

    if (strstr(job,"Suma") || strstr(job,"suma"))
    {
        ease_lvl = 100;
        newMeeseeks = 1;

        printf("Inserte el primer valor: ");
        scanf("%d", &num1);
        printf("Inserte el segundo valor: ");
        scanf("%d", &num2);
        while(wait(NULL)>0);
        printf("El resultado es %d\n", (num1 + num2));
    }

    else if (strstr(job,"Resta") || strstr(job,"resta"))
    {
        ease_lvl = 100;
        newMeeseeks = 1;

        printf("Inserte el primer valor: ");
        scanf("%d", &num1);
        printf("Inserte el segundo valor: ");
        scanf("%d", &num2);
        while(wait(NULL)>0);
        printf("El resultado es %d\n", (num1 - num2));
    }

    else if (strstr(job,"Multiplicar") || strstr(job,"multiplicar"))
    {
        ease_lvl = 100;
        newMeeseeks = 1;

        printf("Inserte el primer valor: ");
        scanf("%d", &num1);
        printf("Inserte el segundo valor: ");
        scanf("%d", &num2);
        while(wait(NULL)>0);
        printf("El resultado es %d\n", (num1 * num2));
    }

    else if (strstr(job,"Dividir") || strstr(job,"dividir"))
    {
        ease_lvl = 100;
        newMeeseeks = 1;

        printf("Inserte el primer valor: ");
        scanf("%d", &num1);
        printf("Inserte el segundo valor: ");
        scanf("%d", &num2);

        if (num2 == 0)
        {
           printf("El divisor debe ser diferente de cero.\n");
           return 0;
        }
        else
        {
            printf("El resultado de la división entera es %d\n", (num1 / num2));
        }
    }

    else if (strstr(job,"Elevar") || strstr(job,"elevar"))
    {
        ease_lvl = 100;
        newMeeseeks = 1;

        printf("Inserte la base: ");
        scanf("%d", &num1);
        printf("Inserte el exponente: ");
        scanf("%d", &num2);
    }

    else if (strstr(job,"Raiz cuadrada") || strstr(job,"raiz cuadrada"))
    {
        ease_lvl = 100;
        newMeeseeks = 1;

        printf("Inserte el valor: ");
        scanf("%d", &num1);
    }
    
    else if (strstr(job,"Ejecutar") || strstr(job,"ejecutar"))
    {
        ease_lvl = 100;
        newMeeseeks = 1;

        printf("Inserte la ruta del programa: ");
        scanf("%s", &prog);
        char *args[] = {prog, NULL};
        *argsp = args;
        system(prog);
    }

    else {
        printf("\n¿Conoce la dificultad del trabajo que desea realizar? (S/N) ");
        aux = getchar();
        printf("Eligió %c\n", aux);
        // Here the Meeseek(s) can do the task(s) based on the ease level
        // determined by the end user.
        if (aux == 'S' || aux == 's')
        {
            printf("¿Cuál es? ([0 - 100], Entre más cercano sea el valor a 0, mayor será la dificultad) ");
            scanf("%lf", &ease_lvl);
            // low ease levels mean more difficult tasks.

            if(ease_lvl < 0 || ease_lvl > 100)
            {
                printf("ERROR: Valor fuera de rango\n");
            }
        }
        // Here the Meeseek(s) job depends on luck, this means the ease
        // level is purely random.
        else if (aux == 'N' || aux == 'n')
        {
            ease_lvl = rand() % 101;
        }
        // Invalid selection error
        else
        {
            printf("El valor ingresado no es válido, vuelva a intentarlo\n");
            return 1;
        }

        printf("La dificultad de su trabajo es %lf \n", ease_lvl);
        
        if(ease_lvl >= 0 && ease_lvl <= 45)
        {
            newMeeseeks = 3;
        }
        else if(ease_lvl > 45 && ease_lvl <= 85)
        {
            newMeeseeks = 2;
        }
        else
        {
            newMeeseeks = 1;
        }
    }

    begin:

    caos();

    newMeeseeks = state.level == 0 ? newMeeseeks : askForHelp(ease_lvl);
    //printf("\nNewMeeseeks: %d\n", newMeeseeks);

    for (int i = 0; i < newMeeseeks; ++i) //New Meeseeks
    {
        state.slavesNum += 1;

        pid = fork();
        
        if(pid < 0) //Error
        {         
            return 0;
        }
        else if(pid > 0) //We send the current state to the slave created
        {
            close(statePipe[0]);  
            write(statePipe[1], &state, sizeof(state));
            close(statePipe[1]);

            close(jobPipe[0]);
            write(jobPipe[1], job, sizeof(job));
            close(jobPipe[1]);

        }
        else if (pid == 0) //The slave receives the current state
        {
            close(statePipe[1]);
            read(statePipe[0], &state, sizeof(state)); 
            close(statePipe[0]);

            close(jobPipe[1]);
            read(jobPipe[0], job, sizeof(job)); 
            close(jobPipe[0]);
            
            break;
        }
    }

    if(pid > 0) //Case of the caller (parent)
    {
        start_clock();
        if(state.level == 0) //If it is the user
        {
            printf("Hola yo soy Mr. Meeseeks! Te voy a ayudar a resolver el problema (pid: %d, ppid: %d, N: %d, Gi: %d, i:%d)\n", getpid(), getppid(), state.level, globalVar, state.slaveId);
            while(wait(NULL)>0); //Wait until is done
            sem_destroy(sem);
            printf("\x1b[34m%s\x1b[0m\n", flag); //Print the Meeseek who solves
            sem_wait(sem);
            clock_t t; 
            t = *meeseeks_clock - clock(); 
            double seconds = -1*((double)t/100);
            printf("La solicitud tardó %f segundos\n", seconds*0.2);
            sem_post(sem);
        }
        else
        {            
            sleep(drand48() * 4.5 + 0.5); //Time to wait for the job to be done            
            sem_wait(sem);//Semaphore is open to warranty exclusive access
            if(flag[0]=='$') //If the job isn't done yet
            {
                if(done(state.level, ease_lvl, *meeseeksQuan, *maxLevel)) //We try to solve
                {
                    sprintf(flag, "Hola!. Logré resolver tu problema :D!! (pid: %d, ppid: %d, N: %d, Gi: %d, i:%d)\n", getpid(), getppid(), state.level, globalVar, state.slaveId); //Flag is changed in case problem is solved 
                    //printf("2. Hola!. Ya finalizamos con tu problema, hora de irnos!\n");
                    globalVar --;
                    sem_post(sem); //Semaphore close                    
                    while(wait(NULL) > 0); //Wait until all Meeseeks finish
                    return 0;
                }
                else
                {
                    //printf("Hola yo soy Mr. Meeseeks! Te voy a ayudar a resolver el problema (pid: %d, ppid: %d, N: %d, Gi: %d, i:%d)\n", getpid(), getppid(), state.level, globalVar, state.slaveId);
                    sem_post(sem); //Semaphore is close in case is not done yet
                    goto begin; //We try again
                }
            }
            else //If job is done
            {
                printf("Hola!. Ya finalizamos con tu problema, hora de irnos!\n");
                sem_post(sem); //Semaphore is close
                while(wait(NULL) > 0); //Wait until all Meeseeks finish
                return 0; //++
            }
        }
    }
    else //Is slave
    {
        sleep(drand48() * 4.5 + 0.5); //Time to wait for the job to be done
        srand(time(NULL)); //Seed for random
        
        sem_wait(sem); //Semaphore open
        //*meeseeksQuan += 1; //Meeseeks quantity ++
        globalVar= *meeseeksQuan;
        sem_post(sem);//Semaphore close

        state.level++; 
        state.slaveId = state.slavesNum; //Sequential Id
        state.slavesNum = 0; //The slave has no crate any new Meeseeks

        sem_wait(sem); //Semaphore open
        *maxLevel = state.level > *maxLevel ? state.level : *maxLevel; //We check if max level have changed
        sem_post(sem);//Semaphore close

        sem_wait(sem); //Semaphore open
        if(flag[0]=='$'){
            *meeseeksQuan += 1; //Meeseeks quantity ++
            printf("Hola yo soy Mr. Meeseeks! Te voy a ayudar a resolver el problema (pid: %d, ppid: %d, N: %d, Gi: %d, i:%d)\n", getpid(), getppid(), state.level, globalVar, state.slaveId); //New Meeseek have been created
        }
        sem_post(sem); //Semaphore close

        pid = getpid();

        sem_wait(sem); //Semaphore open
        if(flag[0] == '$'){ //Job isn't done yet
            if(done(state.level, ease_lvl, *meeseeksQuan, *maxLevel))
            { //We try to solve the problem
                sprintf(flag, "Hola!. Logré resolver tu problema :D!! (pid: %d, ppid: %d, N: %d, Gi: %d, i:%d)\n", getpid(), getppid(), state.level, globalVar, state.slaveId);
                //printf("4. Hola!. Ya finalizamos con tu problema, hora de irnos!\n");
                sem_post(sem); //Semaphore close                    
                while(wait(NULL) > 0); //Wait until all Meeseeks finish
                return 0;
            }
            else{
                sem_post(sem); //Semaphore close                    
                goto begin;
            }
        }
        else
        {
            printf("Hola!. Ya finalizamos con tu problema, hora de irnos!\n");
            sem_post(sem); //Semaphore close                
            while(wait(NULL) > 0); //Wait until all Meeseeks finish
            return 0;
        }
    }

    return 0;
}

void init(){ //Funtion to get shared memory

	sem= mmap(NULL, sizeof sem, PROT_READ | PROT_WRITE,  
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);//Shared memory for the semaphore

	meeseeksQuan= mmap(NULL, sizeof meeseeksQuan, PROT_READ | PROT_WRITE, 
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);//Shared memory for the max number of Meeseeks

	maxLevel= mmap(NULL, sizeof maxLevel, PROT_READ | PROT_WRITE, 
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);//Shared memory for the maxLevel

	flag = mmap(NULL, 200*sizeof(flag), PROT_READ | PROT_WRITE, 
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);//Shared memory for the flag

	timer = mmap(NULL, sizeof(timer), PROT_READ | PROT_WRITE, 
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);//Shared memory for the time

	*timer = clock();

	*meeseeksQuan = 0; //Variable inicialization
	*maxLevel=0;
	flag[0] = '$';

	sem_init(sem, 1, 1); //Semaphore inicialization to work with proceses 
}

void start_clock(){
    meeseeks_clock = mmap(NULL, sizeof(meeseeks_clock), PROT_READ | PROT_WRITE, 
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);//Shared memory for the time

	*meeseeks_clock = clock();
}

int askForHelp(double difficulty){ //Funtion that returns the number of Meeseeks is going to need
	if(difficulty<=85)
    {
        int n = 85 - difficulty + 1;
		return abs((rand() % (n - 1)) - difficulty);
	}
    else
    {
		return 0;
	}
    //return (difficulty + ((rand () % ((int)difficulty) + 1) * (difficulty/1000)));
}


void caos(){ //Problem is out of control??

	sem_wait(sem);
	clock_t t; 
	t = *timer - clock(); 
	double seconds = -1*((double)t/100);
	sem_post(sem);

	if(seconds > 300){

		sem_wait(sem);

		sprintf(flag, "\n");
		printf("Se despichó Tere!\n");
        printf("Tu problema no tiene solución :o\n ");
		sem_post(sem);
	} 
}

bool done(int level, double difficulty, int quantity, int maxLevel){ //Is the problem done?
    double aux = abs ((double)rand()/RAND_MAX*100 - (level*0.0005)- (quantity*0.00005) - (maxLevel*0.005));
    //printf("aux : %f\n", aux);

	if((aux == 0 ? 0.01 : aux ) < difficulty){
		return true;
	}
	return false;
}


void getLineAnySize(char **inputText){
	char * text = *inputText;
	char c = '\0';	
	int size = 0;
	int buffer_size = 16;

	while (c!='\n') {
		scanf("%c", &c);
		if (size + 1 == buffer_size) {
			buffer_size *= 2;
			text = (char *) realloc(text, buffer_size);
			if (text == NULL) {
				fprintf(stderr, "Memoria insuficiente\n");
			}
		}
		text[size] = c;
		size++;
	}
	text[size-1]='\0';
	*inputText = text;
}