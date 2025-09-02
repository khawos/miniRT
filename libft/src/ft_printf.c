/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:32:53 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/26 11:12:13 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

char	is_arg(const char *format)
{
	char	*charset;
	int		i;

	charset = "diupscxX%";
	i = 0;
	if (format[i] == '%' && ft_strchr(charset, format[i + 1]))
		return (1);
	return (0);
}

int	arg_count(const char *format)
{
	int		i;
	int		c;
	char	*charset;

	charset = "diupscxX%";
	c = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr(charset, (format[i + 1])))
			c++;
		i++;
	}
	return (c);
}

int	ft_display(const char *format, va_list ap)
{
	int	i;
	int	argc;

	i = 0;
	argc = arg_count(format);
	format = format - 1;
	while (*++format)
	{
		if (is_arg(format) && argc--)
		{
			format++;
			i = ft_print(ap, *format) + i;
		}
		else if (!is_arg(format))
		{
			write(1, &*format, 1);
			i++;
		}
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, format);
	if (!is_valid(ap, format))
	{
		va_end(ap);
		return (-1);
	}
	va_end(ap);
	va_start(ap, format);
	i = ft_display(format, ap);
	va_end(ap);
	return (i);
}

/*
int	main(void)
{
	int	i;

	i = ft_printf(NULL);
		printf(" %d ", i);
//	i = printf(" %u ", 0);
//		printf(" %d ", i);
}*/
