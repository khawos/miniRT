/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-11 16:20:41 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-11 16:20:41 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bvh   *bvh_fill(t_bounds bounds, int deepth)
{
	t_bvh       *bvh;
	t_bounds    bounds_z1;
	t_bounds    bounds_z2;

	if (deepth > DEEPTH)
		return (NULL);
	bvh = malloc(sizeof(bvh));
	if (!bvh)
		return (NULL);							// protect




	deepth++;
	bvh->zone_1 = bvh_fill(bounds_z1, deepth);
	if (!bvh)
		return (NULL);							// protect
	bvh->zone_2 = bvh_fill(bounds_z1, deepth);
	if (!bvh)
		return (NULL);							// protect
	return (bvh); 
}

