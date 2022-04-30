#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

void doExec(char *comando){
    char *exec_Args[20];
    int i=0;
    char *str = strtok(comando, " ");
    while(str!=NULL){
        exec_Args[i] = str;
        str = strtok(NULL, " ");
        i++;
    }
    exec_Args[i] = NULL;
    int r = execvp(exec_Args[0],exec_Args);
    perror("exec error");
    _exit(r);
}


int main(int argc, char const *argv[])
{
    char args[4][40] = {"grep -v ^# /etc/passwd", "cut -f7 -d:", "uniq", "wc -l"};
    int n_args = 4;
    
    int i, p[n_args - 1][2];
    for(i=0; i<n_args; i++){
        if(i==0){
            pipe(p[i]);
            switch(fork()){
            case -1:
                perror("fork error");
                exit(-1);
            case 0:
                close(p[i][0]);
                if((dup2(p[i][1], 1)) == -1){
                    perror("Dup error");
                    _exit(-1);
                }
                close(p[i][1]);
                doExec(args[i]);
            default:
                close(p[i][1]);
            }
            }else if(n_args -1 == i){
                switch(fork()){
                case -1:
                    perror("fork error");
                    exit(-1);
                case 0:
                    if((dup2(p[i-1][0], 0)) == -1){
                        perror("Dup error");
                        _exit(-1);
                    }
                    close(p[i-1][0]);
                    doExec(args[i]);
                default:
                    close(p[i-1][0]);
                }
        }else{
            pipe(p[i]);
            switch(fork()){
            case -1:
                perror("fork error");
                exit(-1);
            case 0:
                close(p[i][0]);
                if((dup2(p[i][1], 1)) == -1){
                    perror("Dup error");
                    _exit(-1);
                }
                close(p[i][1]);
                if((dup2(p[i-1][0], 0)) == -1){
                    perror("Dup error");
                    _exit(-1);
                }
                close(p[i-1][0]);
                doExec(args[i]);
            default:
                close(p[i][1]);
                close(p[i-1][0]);
            }
        }
    }

    int stat[n_args-1];
    for(i=0; i<n_args; i++)
        wait(&stat[i]);

    return 0;
}
