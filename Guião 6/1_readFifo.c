#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

#define MAX_BUFF 100

int main(int argc, char const *argv[])
{
    int fd_i;
    if((fd_i = open("fifo", O_RDONLY)) == -1){
        perror("Can't open");
        exit(-1);
    }

    int n_read;
    char buffer[MAX_BUFF];
    while((n_read = read(fd_i, buffer, MAX_BUFF)) > 0){
        write(1, buffer, n_read);
    }
    
    if(n_read == 0)
        printf("Terminou\n");
    else
        printf("Erro no read");

    close(fd_i);

    return 0;
}
