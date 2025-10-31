/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:39:48 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/30 21:31:39 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct is_in_bounds_var
{
	double	tx1;
	double	tx2;
	double	ty1;
	double	ty2;
	double	tz1;
	double	tz2;
}			t_is_in_bounds_var;

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

int	*cat_int_array(int *a, int *b, int size_a, int size_b)
{
	int	*new;
	int	i;
	int	j;

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

void	is_in_bounds_bis(t_bounds bounds, t_vec3 origin, t_vec3 dir,
	t_is_in_bounds_var *var)
{
	if (dir.y != 0)
	{
		var->ty1 = (bounds.min.y - origin.y) / dir.y;
		var->ty2 = (bounds.max.y - origin.y) / dir.y;
	}
	else
	{
		var->ty1 = -RENDER_DISTANCE;
		var->ty2 = RENDER_DISTANCE;
	}
	if (dir.z != 0)
	{
		var->tz1 = (bounds.min.z - origin.z) / dir.z;
		var->tz2 = (bounds.max.z - origin.z) / dir.z;
	}
	else
	{
		var->tz1 = -RENDER_DISTANCE;
		var->tz2 = RENDER_DISTANCE;
	}
}

t_boolean	is_in_bounds(t_bounds bounds, t_vec3 origin, t_vec3 dir)
{
	double				tmin;
	double				tmax;
	t_is_in_bounds_var	var;

	if (dir.x != 0)
	{
		var.tx1 = (bounds.min.x - origin.x) / dir.x;
		var.tx2 = (bounds.max.x - origin.x) / dir.x;
	}
	else
	{
		var.tx1 = -RENDER_DISTANCE;
		var.tx2 = RENDER_DISTANCE;
	}
	is_in_bounds_bis(bounds, origin, dir, &var);
	tmin = fmax(fmax(fmin(var.tx1, var.tx2), fmin(var.ty1, var.ty2)),
			fmin(var.tz1, var.tz2));
	tmax = fmin(fmin(fmax(var.tx1, var.tx2), fmax(var.ty1, var.ty2)),
			fmax(var.tz1, var.tz2));
	if (tmax < 0 || tmin > tmax)
		return (false);
	return (true);
}

int	*search_tr_in_tree(t_bvh *bvh, t_ray ray, int *size, int *tr_in_view)
{
	if (is_in_bounds(bvh->bounds, ray.origin, ray.current_dir))
	{
		if (bvh->bounds.deepth == DEEPTH)
		{
			tr_in_view = cat_int_array(tr_in_view, bvh->idx_tr_hbv,
					*size, bvh->n_obj);
			if (!tr_in_view)
				return (*size = -1, NULL);
			*size = *size + bvh->n_obj;
		}
		else
		{
			tr_in_view = search_tr_in_tree(bvh->zone_1, ray, size, tr_in_view);
			if (*size == -1)
				return (NULL);
			tr_in_view = search_tr_in_tree(bvh->zone_2, ray, size, tr_in_view);
			if (*size == -1)
				return (NULL);
		}
	}
	return (tr_in_view);
}
