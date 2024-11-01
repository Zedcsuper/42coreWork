#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
int	main()
{
	char	*line;
	int		fd;

	fd = open("/etc/passwd", O_RDONLY);
	//line = get_next_line(fd);
	//printf("%s", line);
	//free(line);
	
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	
	return (0);
}
