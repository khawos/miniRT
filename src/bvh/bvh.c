/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+  z   */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-11 16:20:41 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-11 16:20:41 by jbayonne         ###   ########.fr       */
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
	// new[1] = 0;
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
	while(i < nb - 1)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = add;
	// new[i + 1] = 0;
	return (new);
}



t_bvh   *bvh_fill(t_mini *mini, int dir, t_bvh *old)
{
	t_bvh       *bvh;
	int			i;

	i = 0;
	if (old->bounds.deepth > DEEPTH)
		return (NULL);
	printf("%d\n", old->bounds.deepth);
	bvh = malloc(sizeof(t_bvh));
	if (!bvh)
		return (NULL);				// protect ... attention a free recursivement + kill window
	if (0 == old->bounds.deepth)
	{
		bvh->bounds = found_first_bound(mini);
		bvh->idx_tr_hbv = NULL;
		bvh->previous = NULL;
		bvh->bounds.deepth++;
		bvh->n_obj = 0;
	}
	else
	{
		bvh->bounds = find_bounds(old->bounds, dir);
		printVec(bvh->bounds.max);
		printVec(bvh->bounds.min);
		bvh->previous = old;
		bvh->idx_tr_hbv = NULL;
		bvh->n_obj = 0;
	}
	while (i < old->n_obj)
	{
		// printObject(mini->sc.objet[old->idx_tr_hbv[i]]);
		// printVec(bvh->bounds.max);
		// printVec(bvh->bounds.min);
		// printf("%d\n", old->n_obj);
		if (tr_is_in_bounds(mini->sc.objet[old->idx_tr_hbv[i]], bvh->bounds))
		{
			bvh->idx_tr_hbv = in_view_realloc(bvh->idx_tr_hbv, old->idx_tr_hbv[i], bvh->n_obj);
			if (!bvh->idx_tr_hbv)
				return (NULL);					// protect... attention a free recursivement + kill window
			bvh->n_obj++;;
		}
		i++;
	}
	bvh->zone_1 = bvh_fill(mini, 0, bvh);
	if (!bvh)
		return (NULL);							// protect ... attention a free recursivement + kill window
	bvh->zone_2 = bvh_fill(mini, 1, bvh);
	if (!bvh)
		return (NULL);							// protect ... attention a free recursivement + kill window
	return (bvh); 
}

