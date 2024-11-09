/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:17:51 by zjamaien          #+#    #+#             */
/*   Updated: 2024/09/18 20:24:37 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putchar_len(char c, int *len);
void	ft_putstr_len(char *s, int *len);
void	ft_putnbr_len(int n, int *len);
void	ft_hex_len(unsigned int x, int *len, char xX);
void	ft_putunsignednbr_len(unsigned int u, int *len);
void	ft_putptr_len(size_t ptr, int *len);
int		ft_printf(const char *s, ...);

#endif
