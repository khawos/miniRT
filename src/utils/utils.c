/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-16 08:39:00 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-16 08:39:00 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s__atoi_utils{
	double	integer_part;
	double	float_part;
	double	power;
	int		neg;

}				t_au;

void	init_atoi_var(t_au *au, char **str)
{
	au->integer_part = 0;
	au->float_part = 0;
	au->power = 1;
	au->neg = 1;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		*str += 1;
}

double	atoi_double(char *str)
{
	double	integer_part;
	double	float_part;
	double	power;
	int		neg;

	integer_part = 0;
	float_part = 0;
	power = 1;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg = -1;
	while (*str != '.' && (*str >= '0' && *str <= '9'))
		integer_part = (*str++ - 48) + (integer_part * 10);
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		power /= 10;
		float_part += (*str++ - 48) * power;
	}
	return ((integer_part + float_part) * neg);
}

double	__atoi_double(char **str)
{
	t_au	var;

	init_atoi_var(&var, str);
	while (**str == '-' || **str == '+')
	{
		if (**str == '-')
		{
			var.neg = -1;
			*str += 1;
		}
	}
	while (**str != '.' && (**str >= '0' && **str <= '9'))
	{
		var.integer_part = (**str - 48) + (var.integer_part * 10);
		*str += 1;
	}
	if (**str == '.')
		*str += 1;
	while (**str >= '0' && **str <= '9')
	{
		var.power /= 10;
		var.float_part += (**str - 48) * var.power;
		*str += 1;
	}
	return ((var.integer_part + var.float_part) * var.neg);
}
