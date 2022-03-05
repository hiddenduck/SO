#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_BUFF 1024

int main(int argc, char const *argv[])
{
    int n;
    char buffer[MAX_BUFF];

    while((n = read(0, buffer, sizeof(buffer))) > 0)
        write(1, buffer, n);
    return 0;
}
