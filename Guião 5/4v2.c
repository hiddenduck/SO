#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int readc(int fd, char *c){ // faz muitos system calls, ou seja, atrasa o desempenho
    return read(fd, c, 1);
}

ssize_t readln(int fd, char *line, size_t size){ // faz apenas a verificacao
    int i = 0;

    while(i<size && readc(fd, &line[i])>0){
        i++;
        if (line[i-1]=='\n') // (char *), cast para char desnecessário, por vezes o compilador pode reclamar
            return i; // ou break
    }

    return i;
}

int main(int argc, char const *argv[])
{
    //pai: 1) cria pipe, 2) fork(), 3) redireciona o stdin 4) exec wc -l
    //filho: 1) redireciona o stdout para extremo de escrita pipe 2) exec ls /etc
    int fildes[2];
    if((pipe(fildes)) == -1){
        perror("Erro no pipe");
        exit(-1);
    }
    
    int f = fork();
    if(f==-1){
        perror("Erro a criar pipe");
        exit(-1);
    }else if(f==0){
        close(fildes[0]);
        if((dup2(fildes[1],1)) == -1){
            perror("Erro na criacao do dup");
            _exit(-1);
        }
        close(fildes[1]);
        execlp("ls", "/bin/ls", "/etc", NULL);        
    }else{
        close(fildes[1]);
    }

    int f2 = fork();
    if(f2==-1){
        perror("Erro na criacao do segundo fork");
        exit(-1);
    }else if(f2==0){
        if((dup2(fildes[0],0)) == -1){
            perror("Erro na criacao do dup");
            _exit(-1);
        }
        close(fildes[0]);
        execlp("wc", "/bin/wc", "-l", NULL);
    }else{
        close(fildes[0]);
    }

    int i, stat[2];
    for(i=0; i<2; i++)
        wait(&stat[i]);
    
    return 0;
}