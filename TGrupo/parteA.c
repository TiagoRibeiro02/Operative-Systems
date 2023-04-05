#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 101

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

    char buffer[BUFFER_SIZE];
    int buffer_size = 0;

    case 'i': {
                // ir para o inicio do ficheiro e avançar n bytes
                int offset = lseek(fd, n, SEEK_SET);
                if (offset == -1) {
                    write(STDOUT_FILENO, "Error\n");
                    close(fd);
                    return 1;
                }
                break;
            }
    case 'f': {
                // ir para o fim do ficheiro e recuar n bytes
                int offset = lseek(fd, -n, SEEK_END);
                if (offset == -1) {
                    write(STDOUT_FILENO, "Error\n");
                    close(fd);
                    return 1;
                }
                break;
            }

}