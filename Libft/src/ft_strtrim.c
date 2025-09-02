/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:58:42 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/14 09:08:39 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str);

static int	is_inset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*buffer;
	int		i;
	int		len;
	int		c;

	i = 0;
	c = 0;
	len = ft_strlen(s1);
	while (is_inset(s1[c], set))
		c++;
	while (is_inset(s1[--len], set) && len > c)
		i++;
	buffer = malloc((sizeof(char) * ft_strlen(s1)) - i - c + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < len - c + 1)
	{
		buffer[i] = s1[c + i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

/*
int	main(void)
{
	char 		*buffer; 
	
	buffer = ft_strtrim("  a aaa", " a");
	printf("%s", buffer);
	free(buffer);
	return (0);
}*/
