#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void	ft_putchar_len(int *len, char c)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putnbr_len(int *len, int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_len(len, '-');
		ft_putnbr_len(len, -n);
	}
	else if (n > 9)
		ft_putnbr_len(len, n / 10);
	ft_putchar_len(len, n % 10 + '0' );
}


static void	ft_putstr_len(int *len, char * s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (*s)
	{
		ft_putchar_len(len, *s);
		s++;
	}
}

static void	ft_puthex_len(int *len, unsigned int x)
{
	if ( x >= 16)
	{
		ft_puthex_len(len, x / 16);
		ft_puthex_len(len, x % 16);
	}
	if (x > 9 && x < 16)
	{
		ft_putchar_len(len, 87 + x);
	}
	else if (x < 10)
	{
		ft_putchar_len(len, x + '0');
	}
}

static void	ft_printf_type(char c, va_list *arg, int *len, int *i)
{
	if (c == 's')
		ft_putstr_len(len, va_arg(*arg, char *));
	else if (c == 'd')
		ft_putnbr_len(len, va_arg(*arg, int));
	else if (c == 'x')
		ft_puthex_len(len, va_arg(*arg, unsigned int));
	else
		(*i)--;
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int	i;
	int	len;

	i = 0;
	len = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_printf_type(format[i], &arg, &len, &i);
			i++;
		}
		else
		{
			ft_putchar_len(&len, format[i]);
			i++;
		}
	}
	va_end(arg);
	return (len);
}

/*
int	main()
{
	int i;
	//i =  
	i = ft_printf("%x\n",1549999);
	ft_printf("%d\n", i);
	i = printf("%x\n", 1549999);
	printf("%d\n", i);

	return (0);
}
*/
