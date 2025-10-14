/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-14 09:31:00 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-14 09:31:00 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bounds	found_first_bound(t_mini *mini)
{
	t_objet obj;
	t_vec3	max;
	t_vec3	min;
	int	i;

	i = 0;
	max = vec_create(-RENDER_DISTANCE, -RENDER_DISTANCE, -RENDER_DISTANCE);
	min = vec_create(RENDER_DISTANCE, RENDER_DISTANCE, RENDER_DISTANCE);
	while (i < mini->N_OBJ)
	{
		obj = mini->sc.objet[i];
		if (tr == obj.type)
		{
			max = try_max_bound(obj, max);
			min = try_min_bound(obj, min);
		}
		i++;
	}
	return ((t_bounds){max, min, 0});
}

t_bounds find_bounds_x(t_bounds old_bounds, int direction, t_var_bounds var)
{
	t_bounds 	new_bounds;

	if (direction == 0)
	{
		new_bounds.min = old_bounds.min;
		new_bounds.max = (t_vec3){var.mid_x, old_bounds.max.y, old_bounds.max.z};
	}
	else
	{
		new_bounds.min = (t_vec3){var.mid_x, old_bounds.min.y, old_bounds.min.z};
		new_bounds.max = old_bounds.max;
	}
	return (new_bounds);
}

t_bounds find_bounds_y(t_bounds old_bounds, int direction, t_var_bounds var)
{
	t_bounds 		new_bounds;

	if (direction == 0)
	{
		new_bounds.min = old_bounds.min;
		new_bounds.max = (t_vec3){old_bounds.max.x, var.mid_y, old_bounds.max.z};
	}
	else
	{
		new_bounds.min = (t_vec3){old_bounds.min.x, var.mid_y, old_bounds.min.z};
		new_bounds.max = old_bounds.max;
	}
	return (new_bounds);
}

t_bounds find_bounds_z(t_bounds old_bounds, int direction, t_var_bounds var)
{
	t_bounds 	new_bounds;

	if (direction == 0)
	{
		new_bounds.min = old_bounds.min;
		new_bounds.max = (t_vec3){old_bounds.max.x, old_bounds.max.y, var.mid_z};
	}
	else
	{
		new_bounds.min = (t_vec3){old_bounds.min.x, old_bounds.min.y, var.mid_z};
		new_bounds.max = old_bounds.max;
	}
	return (new_bounds);
}

t_bounds find_bounds(t_bounds old_bounds, int direction)
{
	t_bounds 		new_bounds;
	t_var_bounds	var;

	find_bounds_utils(&var, old_bounds);
	if (var.dx >= var.dy && var.dx >= var.dz)
		new_bounds = find_bounds_x(old_bounds, direction, var);
	else if (var.dy >= var.dx && var.dy >= var.dz)
		new_bounds = find_bounds_y(old_bounds, direction, var);
	else
		new_bounds = find_bounds_z(old_bounds, direction, var);
	new_bounds.deepth = old_bounds.deepth + 1;
	return new_bounds;
}
