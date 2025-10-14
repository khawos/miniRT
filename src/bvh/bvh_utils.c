/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-14 09:49:04 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-14 09:49:04 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	*first_init(int add)
{
	int	*new;

	new = malloc(sizeof(int) * 1);
	if (!new)
		return (NULL);
	new[0] = add;
	return (new);
}

int	*in_view_realloc(int *old, int add, int nb)
{
	int	*new;
	int	i;

	if (!old)
	{
		old = first_init(add);
		if (!old)
			return (NULL);
		return (old);
	}
	new = malloc(sizeof(int) * (nb + 1));
	if (!new)
		return (free(old), NULL);
	i = 0;
	while(i < nb)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = add;
	return (new);
}
