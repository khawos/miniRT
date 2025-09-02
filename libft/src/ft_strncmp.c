/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:02:31 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/13 00:22:00 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_u;
	unsigned char	*s2_u;

	s1_u = (unsigned char *)s1;
	s2_u = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*s1_u && --n)
	{
		if (*s1_u != *s2_u)
			return (*s1_u - *s2_u);
		s1_u++;
		s2_u++;
	}
	return (*s1_u - *s2_u);
}

/*
int main(void)
{
	const char		*s1 = "Salut les gens";
	const char		*s2 = "Salut\n les gens";
	size_t			n = 1;

	printf("ft_strncmp : %d", ft_strncmp(s1, s2, n));
	printf("   strncmp : %d", strncmp(s1, s2, n));
}*/
