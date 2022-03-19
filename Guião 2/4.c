#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

#define MAX_BUFF 100

int main(int argc, char const *argv[])
{
    int i = 1, stat, pid;
    
    while(i<=10){
        if((pid = fork())==0){
            _exit(i);
        }
        i++;
    }

    i = 1;
    while(i<=10){
        char buffer[MAX_BUFF] = "";
        wait(&stat);
        if(WIFEXITED(stat)){
            sprintf(buffer, "Código de saída do filho: %d\n", WEXITSTATUS(stat));
            write(1, buffer, 50);
        }
        i++;
    }
    
    
    return 0;
}