#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
	int fd_input, fd_output;
    if(argc <= 1){
        printf("Argumentos insuficientes\n");
        return 1;
    }

    char *Args[20];
    int i, j;
    for(i=1, j=0; i<argc; i++){
        if(strcmp(argv[i],"-i")==0){
            fd_input = open(argv[++i], O_RDONLY);
            dup2(fd_input, 0);
            close(fd_input);
        }
        else if(strcmp(argv[i],"-o")==0){
            fd_output = open(argv[++i], O_WRONLY|O_CREAT|O_TRUNC, 0600);
            dup2(fd_output, 1);
            close(fd_output);
        }else
            Args[j++] = argv[i];
    }

    if(j!=0){
        Args[i] = NULL;
        execvp(Args[0], Args);
    }
    return 0;
}
