#include "libft.h"
#include <stdio.h>
#include <string.h>

int	main()
{
	char s[] = "abc";
	char d[] = "b";
	printf("%s\n", ft_strnstr(s, d, sizeof(char) + 3));
	printf("%s\n", strnstr(s, d, sizeof(char) + 3));
	//printf("%d\n", ft_isalpha('a'));
	return (0);
}	
