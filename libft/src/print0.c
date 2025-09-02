/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:02:49 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/19 17:17:14 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_intlen(int i)
{
	int		j;

	j = 0;
	if (i == 0)
		return (1);
	while (i)
	{
		j++;
		i = i / 10;
	}
	return (j);
}

int	ft_intlen_u(unsigned int i)
{
	int		j;

	j = 0;
	if (i == 0)
		return (1);
	while (i)
	{
		j++;
		i = i / 10;
	}
	return (j);
}

int	ft_print(va_list ap, char c)
{
	int		i;
	long	j;

	i = 0;
	j = 0;
	if (c == 'd' || c == 'i')
	{
		j = va_arg(ap, int);
		ft_putnbr(j);
		if (j < 0)
			i++;
		i = ft_intlen(j) + i;
	}
	else if (c == 'c')
	{
		j = va_arg(ap, int);
		i = 1;
		write(1, &j, 1);
	}
	else if (c == 's' || c == 'x' || c == 'X'
		|| c == 'u' || c == 'p' || c == '%')
		i = ft_print_2(ap, c);
	return (i);
}
