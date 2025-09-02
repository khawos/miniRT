/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:09:17 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/13 13:49:38 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dest, const char *src, size_t siz)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (siz == 0)
		return (len);
	while (src[i] && siz -1)
	{
		dest[i] = src[i];
		i++;
		siz--;
	}
	dest[i] = '\0';
	return (len);
}

/*
int	main(void)
{
	char *str = "0123456";
	char dst[100];
	char *str1 = "0123456";
	char dst1[100];
	
	printf("     ft_strlcpy = %zu\n", ft_strlcpy(dst, str, 25));
	printf("ft_strlcpy dest = %s", dst);
	printf("\n\n");
	printf("        strlcpy = %zu\n", strlcpy(dst1, str1, 25));
	printf("   strlcpy dest = %s", dst1);
}*/
