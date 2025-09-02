/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_is_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:41:29 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/26 11:11:39 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	ap_is_valid(va_list ap, char *c)
{
	if (*c == 'd' || *c == 'i')
	{	
		if (va_arg(ap, int) == -2147483648)
			return (-1);
	}
	else if (*c == 'u')
	{	
		if (va_arg(ap, unsigned) < 0)
			return (0);
	}
	return (1);
}	

int	is_valid(va_list ap, const char *format)
{
	int		i;
	char	*c;
	char	*charset;

	if (!format)
		return (0);
	i = 0;
	c = 0;
	charset = "diupscxX%";
	while (format[i])
	{
		if (format[i] == '%' && !ft_strchr(charset, format[i + 1]))
			return (0);
		if (format[i] == '%' && format[i + 1] == '%')
			i++;
		else if (format[i] == '%' && ft_strchr(charset, format[i + 1]))
		{
			c = ft_strchr(charset, format[i + 1]);
			if (!ap_is_valid(ap, c))
				return (0);
		}
		i++;
	}
	return (1);
}
