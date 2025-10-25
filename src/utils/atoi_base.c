/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:22:30 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 14:49:53 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i + 1] != '\0')
	{
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j] || base [i] == '+' || base[i] == '-'
				|| base[j] == '+' || base[j] == '-' || base[i] <= ' '
				|| base[i] > 126 || base[j] <= ' ' || base[j] > 126)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	base_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atoi_base(char *str, char *base)
{
	int	base_length;
	int	i;
	unsigned int res;

	i = 0;
	res = 0;
	base_length = ft_strlen(base);
	if (!check_base(base))
		return (0);
//	printf("%s\n", str);
	while ((str[i] >= 9 && str[i] <= 13 || str[i] == ' ' || str[i] == '#'))
		i++;
	while (str[i] != '"')
	{
		if (base_index(str[i], base) == -1)
			return (0);
		res *= base_length;
		res += base_index(str[i], base);
		i++;
	}
	return (res);
}