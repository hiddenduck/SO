#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

#define MAX_BUFF 100

int main(int argc, char const *argv[])
{
    int fd_o;
    if((fd_o = open("fifo", O_WRONLY)) == -1){
        perror("Can't open file");
        exit(-1);
    }

    int n_read;
    char buffer[MAX_BUFF];
    while((n_read = read(0, buffer, MAX_BUFF)) > 0){
        write(fd_o, buffer, n_read);
    }

    close(fd_o);
    unlink("fifo");
    return 0;
}
