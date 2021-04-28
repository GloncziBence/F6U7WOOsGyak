
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handleSignals(int signum);
int main()
{
    void (*sigHandlerInterrupt)(int);
    void (*sigHandlerQuit)(int);
    void (*sigHandlerReturn)(int);

    sigHandlerInterrupt=sigHandlerQuit=handleSignals;
    sigHandlerReturn=signal(SIGINT,sigHandlerInterrupt);
    if(sigHandlerReturn==SIG_ERR){
        perror("signal error: ");
        return 1;
    }
    sigHandlerReturn=signal(SIGQUIT,sigHandlerQuit);

    if(sigHandlerReturn==SIG_ERR){
        perror("signal error: ");
        return 1;
    }
    while (1){
        printf("\nA program leallitasahoz a kovetkezot vegezze el! \n Egy masik terminalba adja ki a kill %d vagy hasznalja a CTRL+C kombinaciot.",getpid());
        sleep(10);
    }
    return 0;
}
void handleSignals(int signum){
    switch(signum){
        case SIGINT:
            printf("Nyomja meg a CTRL+C billentyukombinaciot.");
            signal(SIGINT,SIG_DFL);
            break;
        case SIGQUIT:
            printf("Nyomja meg a CTRL+C billentyukombinaciot.");
            break;
        default:
            printf("\nFogadott jel szama %d",signum);
            break;
    }
    return;
}
