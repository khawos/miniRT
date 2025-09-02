/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:33:31 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/14 09:07:56 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = ft_strlen(s);
	ptr = 0;
	while (c > 255)
		c = c - 256;
	if (c == 0)
		return ((char *)&s[i]);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (ptr);
}

/*
int	main(void)
{
	const char	*str ="oa\no";

	printf("ft_strchr :%p\n", ft_strchr(str, 'z'+256));
	printf("   strchr :%p\n", strchr(str, 'z'+256));
}
*/
