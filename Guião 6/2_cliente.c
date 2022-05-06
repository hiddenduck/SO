#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_BUFF 100

int main(int argc, char *argv[])
{
    if(argc < 1){
        printf("Argumentos insuficientes");
        return -1;
    }
    int fd_o;
    if((fd_o = open("fifo", O_WRONLY)) == -1){
        perror("Can't open file");
        exit(-1);
    }
    write(fd_o, argv[0], sizeof(argv[1]));
    close(fd_o);
    return 0;
}