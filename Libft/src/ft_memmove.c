/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:29:22 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/14 03:48:06 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*m_dest;
	unsigned char	*m_src;

	if (!dest && !src)
		return (0);
	m_dest = (unsigned char *) dest;
	m_src = (unsigned char *) src;
	if (dest == src || n == 0)
		return (dest);
	if (dest < src)
	{
		while (n--)
			*m_dest++ = *m_src++;
	}
	else
	{
		m_dest = m_dest + (n);
		m_src = m_src + (n);
		while (n--)
			*--m_dest = *--m_src;
	}
	return (dest);
}

/*
int    main(void)
{
//    char dest[] = "111111111111";
//    char src[] = "55555000";
	char	*ptr;
   	char	*nul;
	char	*nu;

	nu = NULL;
	nul = NULL;
	ptr = ft_memmove(nu, nul, 7);
    printf("%s", ptr);
    return (0);
}*/
