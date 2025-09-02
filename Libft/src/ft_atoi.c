/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:36:19 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/10 23:40:20 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	s;

	nb = 0;
	s = 0;
	while ((*nptr <= 13 && *nptr >= 9) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			s = 1;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + *nptr - '0';
		nptr++;
	}
	if (s == 1)
		nb = -nb;
	return (nb);
}
