#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int	main()
{
	int fd = open("txt.txt", O_RDONLY);
	char *c;
	c = malloc(sizeof(char) * 1);
	int r = read(fd, c, 1);
	while (r > 0)
	{
		printf("%s", c);
		r = read(fd, c, 1);
	}
	free(c);
	close(fd);
}
			
