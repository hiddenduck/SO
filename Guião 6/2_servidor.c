#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_BUFF 100

int main(int argc, char const *argv[])
{
    int fd_i, fd_log, fd_o;
    if((fd_i = open("fifo", O_RDONLY)) == -1){
        perror("Can't open input");
        exit(-1);
    }

    
    if((fd_o = open("fifo", O_WRONLY)) == -1){
        perror("Can't open output");
        exit(-1);
    }

    if((fd_log = open("log.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1){
        perror("Can't open log");
        exit(-1);
    }

    char buffer[300], bytesread;
    while((bytesread = read(fd_i, buffer, 100)) > 0){
        write(fd_log, buffer, bytesread);
    }
    
    close(fd_i);
    close(fd_log);
    close(fd_o);
    unlink("fifo");
    return 0;
}
