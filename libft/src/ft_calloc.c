/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:48:46 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/14 09:10:22 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

void	*ft_memset(void *s, int c, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*alloc;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	alloc = malloc((size * nmemb));
	if (!alloc)
		return (NULL);
	ft_memset(alloc, 0, nmemb * size);
	return (alloc);
}
