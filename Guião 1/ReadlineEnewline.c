#include <unistd.h>
#include <stdio.h>

#define MAX_BUFF 1024

char buffer[MAX_BUFF];
int bytes_Total = 0;
int bytes_now = 0;


int readc(int fd, char *c){ // faz muitos system calls, ou seja, atrasa o desempenho
    return read(fd, c, 1);
}

int readc2(int fd, char *c){ // otimizacao do readC anterior
    if(bytes_now==bytes_Total){
        bytes_Total = read(fd, buffer, MAX_BUFF);

        if(bytes_Total == -1 || bytes_Total == 0) return bytes_Total; // excecoes, erro ou EOF

        // else
        bytes_now = 0; // caso normal
    }

    *c = buffer[bytes_now++];

    return 1; // return 1 no sentido em que entrega apenas 1 byte
}

ssize_t readln(int fd, char *line, size_t size){ // faz apenas a verificacao
    int i = 0;

    while(i<size && readc(fd, &line[i])>0){
        i++;
        if (line[i-1]=='\n') // (char *), cast para char desnecessário, por vezes o compilador pode reclamar
            return i; // ou break
    }

    return i;
}

// newline:
int main(int argc, char const *argv[]){
    int line_counter = 1, new_line = 1, bytes_read = 0;
    char buffer[MAX_BUFF+1];

    while((bytes_read = readln(0, buffer, MAX_BUFF))>0){
        char linha[MAX_BUFF+16] = ""; // caso alternativo, podia ser só 16 bytes de tamanho
        buffer[bytes_read] = '\0'; // desnecessário se for feito um write(1, buffer, sizeof(buffer)) asseguir ao da linha
        if(new_line && buffer[0]!='\n')
            sprintf(linha, "%d: %s", line_counter++, buffer);
        write(1, linha, sizeof(linha));
        new_line = (buffer[bytes_read-1] != '\n') ? 0 : 1;
    }

    return 0;
}
