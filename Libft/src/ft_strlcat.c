/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:06:00 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/13 18:58:18 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <bsd/string.h>
#include <stdio.h>

size_t	ft_strlen(const char *str);

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{	
	size_t	dest_len;
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	dest_len = ft_strlen(dst);
	while (dst[pos])
		pos++;
	while (src[i] && (1 + pos + i) < siz)
	{
		dst[pos + i] = src[i];
			i++;
	}
	if (i < siz)
		dst[pos + i] = '\0';
	if (siz <= dest_len)
		return (ft_strlen(src) + siz);
	else
		return (ft_strlen(src) + dest_len);
}

/*
int main(void)
{
	char 	dst[10] = "non momo";
	char	*src = "A l'aide aidez moi";
	char 	dst1[10] = "non momo";
	char	*src1 = "A l'aide aidez moi";


	int		a;
	int		b;

	a = ft_strlcat(dst, src, sizeof(char) * 0);	
	b = strlcat(dst1, src1, sizeof(char) * 0);	
	printf("     ft_strlcat : %d\n", a);
	printf("ft_strlcat dest : %s\n\n", dst);
	printf("        strlcat : %d\n", b);
	printf("   strlcat dest : %s\n", dst1);
}*/
