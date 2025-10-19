/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynamic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:36:49 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 14:50:36 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "stdlib.h"

char	*dynamic_delete(char *old)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(old);
	new = malloc(sizeof(char) * len);
	if (!new)
		return (free(old), NULL);
	i = 0;
	j = 1;
	while (i < len - 1)
	{
		new[i] = old[j];
		j++;
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}

char	*dynamic_copy(char *old, char c)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(old);
	new = malloc(sizeof(char) * len + 2);
	if (!new)
		return (free(old), NULL);
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	if (old)
		free(old);
	return (new);
}