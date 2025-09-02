/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:05:54 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/19 09:40:16 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);

static int	ft_alloc(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*nb_str;
	int		len;
	long	nb;

	nb = n;
	len = ft_alloc(nb);
	nb_str = malloc(sizeof(char) * len + 1);
	if (!nb_str)
		return (NULL);
	nb_str[len] = '\0';
	if (nb == 0)
		nb_str[0] = '0';
	if (nb < 0)
	{
		nb = nb * -1;
		nb_str[0] = '-';
	}
	while (nb)
	{
		nb_str[--len] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (nb_str);
}
