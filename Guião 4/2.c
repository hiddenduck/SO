#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd, fd_out, fd_error, fd_temp;

    if ((fd = open("/etc/passwd", O_RDONLY)) == -1){
        perror("Problema no fd");
        exit(1);
    }
    if ((fd_out = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600)) == -1){
        perror("Problema no fd_out");
        exit(1);
    }
    if ((fd_error = open("erros.txt", O_WRONLY|O_CREAT|O_TRUNC, 0600)) == -1){
        perror("Problema no fd_error");
        exit(1);
    }
    if((fd_temp = dup(1)) == -1){
        perror("Descritor fd_temp nao e valido");
        exit(1);
    }

    dup2(fd, 0);
    dup2(fd_out, 1);
    dup2(fd_error, 2);
    close(fd);
    close(fd_out);
    close(fd_error);

    pid_t pid = fork();
    if(pid==-1)
        exit(1);
    else if(pid == 0){
        char buff[1024];
        int n_read;
        while((n_read = read(0, buff, 1024)) > 0)
            write(1, buff, n_read);
        dup2(fd_temp, 1);
        close(fd_temp);
        printf("Terminei\n");
        _exit(0);
    }else{
        int stat;
        wait(stat);
        close(fd_temp);
    }
    
    return 0;
}