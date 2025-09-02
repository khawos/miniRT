/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:35:27 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/20 11:43:52 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	ft_hex_len_ptr(unsigned long long n, int i)
{
	while (n)
	{
		n = n / 16;
		i++;
	}
	if (n % 16 != 0)
		i++;
	return (i);
}

void	ft_fill_hex_ptr(unsigned long long n)
{
	int	c;

	c = 0;
	if (n < 16)
	{
		c = ft_convert_hex((int)n);
		write(1, &c, 1);
	}
	else
	{
		ft_fill_hex_ptr(n / 16);
		ft_fill_hex_ptr(n % 16);
	}
}
