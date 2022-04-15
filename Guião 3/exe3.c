#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

#define MAX_BUFF 100

int main(int argc, char const *argv[])
{
    int i = 1, stat, pid;
    
    // char *exec_args[] = {"/bin/ls", "-l", NULL}
    // ret = execl("/bin/ls", "/bin/ls", "-l", NULL)
    // ret = execlp("ls", "/bin/ls", "-l", NULL)
    // ret = execv("/bin/ls", exec_args)
    // ret = execvp("/bin/ls", exec_args) 
    int fork_ret, exec_ret;
    while(i<=argc){
        fork_ret = fork();
        if(fork_ret==0){
            exec_ret = execlp(argv[i], argv[i], NULL);
            _exit(i);
            perror("reach reeturn");
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