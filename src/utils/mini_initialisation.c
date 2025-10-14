/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/13 10:05:17 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	get_ambiant(t_mini *mini)
{
	int	i;

	i = -1;
	while (i++ < mini->N_LIGHT)
		if (mini->sc.light[i].type == A)
			return (mini->sc.light[i]);
	return ((t_light){0});
}

t_boolean	bvh_init(t_mini *mini)
{
	t_bvh	*head;
	int		i;
	int		j;

	i = -1;
	j = 0;
	head = malloc(sizeof(t_bvh));
	if (!head)
		return (false);
	head->bounds.deepth = 0;
	head->idx_tr_hbv = malloc(sizeof(int)* mini->n_tr);
	if (!head->idx_tr_hbv)
		return (false);
	head->n_obj = mini->n_tr;
	while (++i < mini->N_OBJ)
	{
		if (tr == mini->sc.objet[i].type)
		{
			head->idx_tr_hbv[j] = i;
			j++; 
		}
	}
	mini->bvh = bvh_fill(mini, 0, head);
	if (!mini->bvh)
		return (false);
	return (true);
}

t_boolean	init(t_mini *mini, char **av)
{
	mini->n_a = 0;
	mini->n_l = 0;
	mini->n_cam = 0;
	mini->n_pl = 0;
	mini->n_sp = 0;
	mini->n_cy = 0;
	mini->N_OBJ = 0;
	mini->N_LIGHT = 0;
	mini->cam_lock = 0;
	mini->n_tr = 0;
	mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	if (!parser(mini, av))
		return (false);
	// if (pthread_mutex_init(&mini->render_mutex, NULL) < 0)
	// 	return (false);									// ATTENTION FREE
	if (mini->n_tr != 0)
	{
		if (!bvh_init(mini))
			return (free_mini(mini), false);
	}
	else
		mini->bvh = NULL;
	mini->sc.ambiant = get_ambiant(mini);
	if (!open_window(mini))
		return (free_mini(mini), false);
	return (true);
}
