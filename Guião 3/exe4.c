#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <string.h>

int mysystem(char *comando){
    char *exec_Agrs[20];
    char *string;
    int i=0;
    int status;
    string = strtok(comando, " ");

    while(string!=NULL){
        exec_Agrs[i] = string;
        string = strtok(NULL, " ");
        i++;
    }
    exec_Agrs[i] = NULL;
    int res=0;
    int fork_ret = fork(), exec_ret;
    if(fork_ret==0){
        exec_ret = execvp(exec_Agrs[0], exec_Agrs);
        _exit(exec_ret);
    }else{
        if(fork_ret!= -1){
            int wait_ret = waitpid(fork_ret, &status, 0);
            if(WIFEXITED(status)){
                res = WEXITSTATUS(status);
                if(res==255){
                    return -1;
                }else{
                    return res;
                }
                
            }else
                res=-1;
        }else{
                    res = -1;
                }
    }

    return res;
}
// system é bloqueante: espera que o comando termine antes de devolver, aka esperar pelo filho
// o & é um operador da bash e portanto não funciona em execs!!!!
int main(int argc, char const *argv[])
{
    int ret;
    char comando1[] = "ls -l -a -h";
    char comando2[] = "sleep 10";
    char comando3[] = "ps";

    printf("a executar mysystem para %s\n", comando1);
    ret = mysystem(comando1);
    printf("ret: %d\n", ret);

    printf("a executar mysystem para %s\n", comando2);
    ret = mysystem(comando2);
    printf("ret: %d\n", ret);

    printf("a executar mysystem para %s\n", comando2);
    ret = mysystem(comando2);
    printf("ret: %d\n", ret);
    return 0;
}
