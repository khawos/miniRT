/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 11:58:30 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/12 12:15:16 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec2	get_uv_sp(t_vec3 p, t_objet sp)
{
	t_vec2	texture;
	double	phi;
	double	theta;

	phi = atan2(p.z, p.x);
	theta = acos(p.x / (sp.diameter / 2));
	texture.u = (-phi + M_PI) / (2 * M_PI);
	texture.v = theta / M_PI;
	return (texture);
}