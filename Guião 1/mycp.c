#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_BUFF 1024 // colocar 1024, assim diminuimos o número de system calls por 1024, ao ter MAX_BUFF = 1,
int main(int argc, char *argv[]){
    int ofd, dfd, n;
    char buffer[MAX_BUFF];
    ofd = open(argv[1], O_RDONLY);
    if(ofd == -1){
        perror(argv[1]);
        return 1; /* EXIT_FAILURE */
    }
    dfd = open(argv[2], O_CREAT|O_TRUNC|O_WRONLY, 0666);
    if(dfd == -1){
        perror(argv[2]);
        return 1; /* EXIT_FAILURE */
    }

    while((n = read(ofd, buffer, sizeof(buffer))) > 0)
        write(dfd, buffer, n);

    close(ofd);
    close(dfd);

    return 0; /* EXIT_SUCCESS */
}
