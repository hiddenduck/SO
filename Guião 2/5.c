#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

#define MAX_BUFF 100

int main(int argc, char const *argv[])
{
    if(argc <2){
        perror("No number specified\n");
        _exit(-1);
    }

    int linhas = 10,
        colunas = 10000,
        rand_max = 10000,
        num = atoi(argv[1]),
        matriz[linhas][colunas];
    
    for(int i = 0; i < linhas; i++)
        for(int j = 0; j < colunas; j++)
            matriz[i][j] = rand() % rand_max;

    for(int i = 0; i < linhas; i++){
        if(fork()==0){
            int found = 0;
            for(int j = 0; j < colunas && found==0; j++){
                if(num == matriz[i][j])
                    found = 1;
            }

            _exit((found == 1) ? i : -1);
        }
    }

    char buffer[40] = "";
    int stat;
    for(int i = 0; i < linhas; i++){
        wait(&stat);
        if(WEXITSTATUS(stat)!=255){
            sprintf(buffer,"Valor encontrado na linha: %d\n", WEXITSTATUS(stat));    
            write(1, buffer, 30);
        }
    }

    return 0;
}