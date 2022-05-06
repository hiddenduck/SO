#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int segundos = 0;
int n_ctrlC = 0;

void contaSegundos(int v){
    segundos++;
    alarm(1);
    write(1, "segundo\n", 9);
}

void contaCtrlC(int v){
    n_ctrlC++;
    char buffer[100];
    sprintf(buffer, "\nTotal: %d segundos\n", segundos);
    write(1, buffer, strlen(buffer));
}

void terminar(int v){
    char buffer[100];
    sprintf(buffer, "\nO ctrl+c foi usado %d vezes\n", n_ctrlC);
    write(1, buffer, strlen(buffer));
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGALRM, contaSegundos);
    signal(SIGINT, contaCtrlC);
    signal(SIGQUIT, terminar);

    alarm(1);
    while(1){
        //pause();
    }
    return 0;
}
