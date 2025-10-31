/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tringle_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 14:33:11 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-31 14:33:11 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_nearest_triangle_utils(double tmp, int *closest, double t, int i)
{
	if (tmp > 0 && tmp < t)
	{
		*closest = i;
		return (tmp);
	}
	else
		return (t);
}

double	get_nearest_triangle(int *closest, t_ray *ray, t_mini *mini)
{
	double	tmp;
	int		*tr_index;
	int		size;
	int		i;

	size = 0;
	tr_index = NULL;
	tr_index = search_tr_in_tree(mini->bvh, *ray, &size, tr_index);
	if (size == -1)
		return (ray->t = -1, ray->t);
	i = -1;
	if (tr_index)
	{
		while (++i < size)
		{
			tmp = intersect_tr(ray->origin,
					ray->current_dir, mini->sc.objet_tr[tr_index[i]]);
			ray->t = get_nearest_triangle_utils(tmp, closest, ray->t,
					tr_index[i]);
		}
		free(tr_index);
	}
	return (ray->t);
}
