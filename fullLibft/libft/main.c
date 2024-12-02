#include "libft.h"

int	main()
{
	char	*str = "33";
	char	*line;
	ft_printf("%d\n", ft_atoi(str));

	int fd = open("ft_isalpha.c", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("%s", line);
		free(line);
	}
	return (0);
}
