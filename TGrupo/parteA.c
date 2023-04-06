#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 101

int andvancefromi(int *file, int n)
{
    int offset = lseek(file, n, SEEK_SET);
    return offset;
}

int returnfromf(int *file, int n)
{
    int offset = lseek(file, -n, SEEK_END);
    return offset;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        write(STDOUT_FILENO, "Binary file requiered\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        write(STDOUT_FILENO, "Error opening file\n");
        return 1;
    }

}