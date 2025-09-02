/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:06:27 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/20 13:34:15 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdint.h>
#include <unistd.h>

int	ft_print_5(va_list ap, char c)
{
	int					i;
	unsigned int		j;

	j = 0;
	i = 0;
	if (c == 'X')
	{
		j = va_arg(ap, unsigned int);
		if (j == 0)
		{
			write(1, "0", 1);
			return (1);
		}
		ft_fill_hex_up(j);
		i = ft_hex_len(j, 0);
	}
	return (i);
}

int	ft_print_4(va_list ap, char c)
{
	uintptr_t	ptr_v;
	int			i;

	if (c == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	if (c == 'p')
	{
		ptr_v = va_arg(ap, unsigned long long);
		if (!ptr_v)
		{
			ft_putstr("(nil)");
			return (5);
		}
		write(1, "0x", 2);
		ft_fill_hex_ptr(ptr_v);
		i = ft_hex_len_ptr(ptr_v, 0) + 2;
	}
	if (c == 'X')
		i = ft_print_5(ap, c);
	return (i);
}

int	ft_print_3(va_list ap, char c)
{
	int					i;
	unsigned int		j;

	j = 0;
	if (c == 'u')
	{
		j = va_arg(ap, unsigned int);
		ft_putnbr_u(j);
		i = ft_intlen_u(j);
	}
	if (c == 'x')
	{
		j = va_arg(ap, unsigned int);
		if (j == 0)
		{
			write(1, "0", 1);
			return (1);
		}
		ft_fill_hex(j);
		i = ft_hex_len(j, 0);
	}
	else if (c == 'p' || c == '%' || c == 'X')
		i = ft_print_4(ap, c);
	return (i);
}

int	ft_print_2(va_list ap, char c)
{
	char			*str;
	int				i;

	i = 0;
	str = 0;
	if (c == 's')
	{
		str = va_arg(ap, char *);
		if (!str)
		{
			ft_putstr("(null)");
			return (6);
		}
		i = ft_strlen(str);
		ft_putstr(str);
	}
	else if (c == 'X' || c == 'p' || c == 'u' || c == '%'
		|| c == 'x')
		i = ft_print_3(ap, c);
	return (i);
}
