/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:35:37 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:25:34 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	intersect_loop_bis(t_mini *mini, t_ray *ray, int *closest)
{
	int		tmp;
	int		tmp_closet;
	t_color	final;

	final = (t_color){0, 0, 0};
	tmp_closet = *closest;
	if (mini->bvh)
	{
		tmp = ray->t;
		ray->t = get_nearest_triangle(closest, ray, mini);
		if (ray->t == -1)
			return ((t_color){0, 0, 0});
		if (tmp > ray->t)
			return (light_ray(mini, ray, mini->sc.objet_tr[*closest]));
	}
	if (ray->t != RENDER_DISTANCE)
	{
		final = light_ray(mini, ray, mini->sc.objet[tmp_closet]);
	}
	return (final);
}

t_color	intersect_loop(t_mini *mini, t_ray *ray)
{
	int		i;
	int		closest;
	double	tmp;
	t_color	final;

	final = (t_color){0, 0, 0};
	ray->color = (t_color){0, 0, 0};
	closest = 0;
	i = -1;
	ray->t = RENDER_DISTANCE;
	while (++i < mini->N_OBJ)
	{
		tmp = handle_object(mini, *ray, i, ray->t);
		if (tmp < ray->t)
		{
			ray->t = tmp;
			closest = i;
		}
	}
	final = intersect_loop_bis(mini, ray, &closest);
	return (final);
}

t_color	multiple_ray(t_mini *mini, t_ray *ray)
{
	t_color	*ray_color;
	t_color	final;
	int		i;

	i = -1;
	ray->color = (t_color){0, 0, 0};
	ray_color = malloc(sizeof(t_color) * SAMPLE_MAX);
	if (!ray_color)
		return (ray->t = -1, (t_color){0, 0, 0});
	ray->current_dir = ray->dir_tab[0];
	if (mini->block_size != 1)
		return (free(ray_color), intersect_loop(mini, ray));
	else
	{
		while (++i < SAMPLE_MAX)
		{
			ray->current_dir = ray->dir_tab[i];
			ray->color = (t_color){0, 0, 0};
			ray_color[i] = intersect_loop(mini, ray);
			if (ray->t == -1)
				return (free(ray_color), (t_color){0, 0, 0});
		}
		final = mix_ray(ray_color);
		return (free(ray_color), final);
	}
}
