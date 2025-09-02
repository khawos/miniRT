/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:33:55 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/20 11:41:28 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

char	ft_convert_hex(int nb)
{
	char	*hex;
	char	c;

	c = 0;
	hex = "0123456789abcdef";
	if (nb >= 0 && nb <= 15)
	{
		c = hex[nb];
		return (c);
	}
	return ('?');
}

int	ft_hex_len(unsigned int n, int i)
{
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n)
	{	
		i = ft_hex_len(n / 16, i + 1);
	}
	return (i);
}

void	ft_fill_hex_up(unsigned int n)
{
	int		c;

	c = 0;
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
	}
	if (n < 16)
	{
		c = ft_convert_hex(n);
		c = ft_toupper(c);
		write(1, &c, 1);
	}	
	else
	{	
		ft_fill_hex_up(n / 16);
		ft_fill_hex_up(n % 16);
	}
}

void	ft_fill_hex(unsigned int n)
{
	int		c;

	c = 0;
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
	}
	if (n < 16)
	{
		c = ft_convert_hex(n);
		write(1, &c, 1);
	}	
	else
	{	
		ft_fill_hex(n / 16);
		ft_fill_hex(n % 16);
	}
}
