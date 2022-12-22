
#include "get_next_line.h"
int main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
    //fd = ;
	while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line); 
    }
    printf("%s", line);
    return (0);
} 