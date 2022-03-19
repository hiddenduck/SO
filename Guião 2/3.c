#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

#define MAX_BUFF 100

int main(int argc, char const *argv[])
{
    int i = 1, stat, pid_de_quem_terminou;
    while(i<=10){
        char buffer[MAX_BUFF] = "";
        if(fork()==0){
            sprintf(buffer, "pid pai:%d pid atual:%d i: %d\n", getppid(), getpid(), i);
            write(1, buffer, 40);
            _exit(i);
        }
        pid_de_quem_terminou =  wait(&stat);
        sprintf(buffer, "código de saída do %dº filho (PID: %d): %d\n\n", i, pid_de_quem_terminou, WEXITSTATUS(stat));
        write(1, buffer, 50);
        i++;
    }
    
    return 0;
}