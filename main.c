#include "get_next_line.h"
#include <libc.h>

int main()
{
    int fd = open("test.txt", O_CREAT | O_RDWR, 0755);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s",line);
        free(line);
    }
    close(fd);
    return(0);
}