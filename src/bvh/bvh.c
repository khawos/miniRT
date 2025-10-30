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

void	bvh_free(t_bvh *bvh)
{
	t_bvh	*z1;
	t_bvh	*z2;

	z1 = bvh->zone_1;
	z2 = bvh->zone_2;
	free(bvh->idx_tr_hbv);
	free(bvh);
	bvh = NULL;
	if (z1)
		bvh_free(z1);
	if (z2)
		bvh_free(z2);
}

void	*bvh_recursive_free(t_bvh *bvh)
{
	if (bvh == NULL)
		return (NULL);
	while (bvh->previous != NULL)
		bvh = bvh->previous;
	bvh_free(bvh);
	return (NULL);
}

t_bvh *bvh_alloc(t_bvh *old, int dir, t_mini *mini)
{
	t_bvh *bvh;

	bvh = malloc(sizeof(t_bvh));
	if (!bvh)
		return (NULL);	
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
		bvh->previous = old;
		bvh->idx_tr_hbv = NULL;
		bvh->n_obj = 0;
	}
	return (bvh);
}

void	*bvh_recurse(t_mini *mini, t_bvh *old, t_bvh *bvh)
{
	if (bvh->bounds.deepth == DEEPTH)
	{
		bvh->zone_1 = NULL;
		bvh->zone_2 = NULL;
	}
	else
	{
		bvh->zone_1 = bvh_fill(mini, 0, bvh);
		if (!bvh)
			return (bvh_recursive_free(old));
		bvh->zone_2 = bvh_fill(mini, 1, bvh);
		if (!bvh)
			return (bvh_recursive_free(old));
	}
	return (NULL);
}

t_bvh	*bvh_fill(t_mini *mini, int dir, t_bvh *old)
{
	t_bvh	*bvh;
	int			i;

	i = 0;
	bvh = bvh_alloc(old, dir, mini);
	if (!bvh)
		return (bvh_recursive_free(old));
	while (i < old->n_obj)
	{
		if (tr_is_in_bounds(mini->sc.objet_tr[old->idx_tr_hbv[i]], bvh->bounds))
		{
			bvh->idx_tr_hbv = in_view_realloc(bvh->idx_tr_hbv,
									old->idx_tr_hbv[i], bvh->n_obj);
			if (!bvh->idx_tr_hbv)
				return (bvh_recursive_free(old));
			bvh->n_obj++;;
		}
		i++;
	}
	bvh_recurse(mini, old, bvh);
	return (bvh); 
}

