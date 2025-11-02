/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-02 12:17:23 by jbayonne          #+#    #+#             */
/*   Updated: 2025-11-02 12:17:23 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	light_ray(t_mini *mini, t_vec3 ray_dir, double t, t_objet obj)
{
	t_color	color;
	t_color	ambiant;
	t_color	final;

	if (obj.type == sp)
		color = light_sp(mini, obj, ray_dir, t);
	else if (obj.type == pl)
		color = light_pl(mini, obj, ray_dir, t);
	else
		color = light_cy(mini, obj, ray_dir, t);
	ambiant = apply_ambiant(mini, obj.color);
	final = mix_colors(color, ambiant);
	return (final.hit = true, final);
}
