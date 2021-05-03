#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>

static void sigHandler(int);
static void sendSignal();

int main ()
{
    if(signal(SIGUSR1, sigHandler) == SIG_ERR){                                 //ha a ket rendszerhivas SIG_ERR el tér vissza, akkor a illegalis signal
        printf("Parent: An error occurred while creating handler SIGUSR1\n");   //Ezert kell ellenorzes
    }
    if(signal(SIGUSR2, sigHandler) == SIG_ERR){
        printf("Parent: An error occurred while creating handler for SIGUSR2\n");
    }

    sendSignal();
}

static void sendSignal(){

    int child_pid;
    int status;

    if((child_pid = fork()) == 0) {

        for (;;) pause();

    }
    else {

        int run = 0;

        do{

            kill(child_pid, SIGUSR1);   //signalt kuld
            sleep(2);                   //ket masodpercig var. Atlathatobb a program futás közben
            kill(child_pid, SIGUSR2);
            sleep(2);
            run++;                      //hozzaad egyet minden alkalommal ahanyszor lefut

        }while(run<5); //amig el nem eri az 5 erteket a valtozo addig csinalja ujra

        printf("Parent: Terminating child ...\n"); //miutan elerte az 5 erteket
        kill(child_pid, SIGTERM);
        wait(&status);
        printf("Done\n");
    }
}

static void sigHandler(int signum) {

    static int counter = 0;

    switch(signum) { //megnezi melyik signalt kapta, es az alapjan vegzi a feladatokat.
        case SIGUSR1:

            printf("Child: Caught signal %d, increasing counter.\n", signum);
            counter++;
            break;

        case SIGUSR2:

            printf("Child: Caught signal %d, printing counter.\n", signum);
            printf("Counter %d\n",counter);
            break;

        default:
            break; //ha veletlenul mas jelet kapna. De nem kellene megtortennie
    }
    return;
}
