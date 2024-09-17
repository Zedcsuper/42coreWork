#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
int	main()
{
	char	*line;
	int		fd;

	fd = open("txt.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
