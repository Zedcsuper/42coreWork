#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int	main()
{
	char *s;
	int x = open("txt.txt", O_RDONLY);
	while ((s = get_next_line(x)) != NULL)
	{
		printf("%s", s);
		free(s);
	}
	return (0);
}
