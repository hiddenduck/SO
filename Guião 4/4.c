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
    int changeIN = 0, changeOut = 0, i, j;
    for(i=1, j=0; i<argc; i++){
        if(strcmp(argv[i],"-i")==0)
            changeIN = 1;
        else if(strcmp(argv[i],"-o")==0)
            changeOut = 1;
        else if(changeIN){
            fd_input = open(argv[i], O_RDONLY);
            dup2(fd_input, 0);
            close(fd_input);
            changeIN = 0;
        }
        else if(changeOut){
            fd_output = open(argv[i], O_WRONLY|O_CREAT|O_TRUNC, 0600);
            dup2(fd_output, 1);
            close(fd_output);
            changeOut = 0;
        }else{
            Args[j++] = argv[i];
        }   
    }

    if(j!=0){
        Args[i] = NULL;
        execvp(Args[0], Args);
    }
    return 0;
}
