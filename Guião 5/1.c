#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fildes[2];
    
    if(pipe(fildes) == -1){
        perror("erro no pipe");
        return -1;
    }    

    int f = fork();

    if(f==-1){
        perror("erro no fork");
        return -1;
    }else if(f==0){
        close(fildes[0]);
        char linha[] = "linhaDeTexto\n";
        write(1, "filho\n", 6);
        write(fildes[1], linha, sizeof(linha));
        close(fildes[1]);
        _exit(0);
    }else{
        close(fildes[1]);
        char buffer[20];
        int stat;
        int n_read = read(fildes[0], buffer, sizeof(buffer));
        printf("Pai: %s", buffer);
        close(fildes[0]);
        wait(&stat);

    }

    return 0;
}
