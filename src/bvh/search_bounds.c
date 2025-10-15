/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-14 09:39:48 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-14 09:39:48 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	*ft_strdup_int(int *b, int size)
{
	int	*dup;
	int	i;

	dup = malloc(sizeof(int) * size);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = b[i];
		i++;
	}
	return (dup);
}

int *cat_int_array(int *a, int *b, int size_a, int size_b)
{
	int *new;
	int i;
	int j;
	
	if (!a)
		return (ft_strdup_int(b, size_b));
	new = malloc(sizeof(int) * (size_a + size_b));
	if (!new)
		return (free(a), NULL);
	i = -1;
	j = -1;
	while (++i < size_a)
		new[i] = a[i];
	while (++j < size_b)
		new[i + j] = b[j];
	free(a);
	return (new);
}

t_boolean	is_in_bounds(t_bounds bounds, t_vec3 origin, t_vec3 dir)
{
	
}


int *search_tr_in_tree(t_bvh *bvh, t_vec3 origin, t_vec3 ray_direction, int *size, int *tr_in_view)
{
	int i;

	i = 0;
	if (is_in_bounds(bvh->bounds, origin, ray_direction))
	{
		if (bvh->bounds.deepth == DEEPTH)
		{
			tr_in_view = cat_int_array(tr_in_view, bvh->idx_tr_hbv, *size, bvh->n_obj);
			if (!tr_in_view)
				return (*size = -1, NULL);
			*size = *size + bvh->n_obj;
		}
		else
		{
			tr_in_view = search_tr_in_tree(bvh->zone_1, origin, ray_direction, size, tr_in_view);
			if (*size == -1)
				return (NULL);
			tr_in_view = search_tr_in_tree(bvh->zone_2, origin, ray_direction, size, tr_in_view);
			if (*size == -1)
				return (NULL);
		}
	}
	return (tr_in_view);
}