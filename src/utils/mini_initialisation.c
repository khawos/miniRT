/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:22:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/30 15:47:33 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	bvh_init(t_mini *mini)
{
	t_bvh	*head;
	int		i;

	i = -1;
	head = malloc(sizeof(t_bvh));
	if (!head)
		return (false);
	head->bounds.deepth = 0;
	head->idx_tr_hbv = malloc(sizeof(int)* mini->n_tr);
	if (!head->idx_tr_hbv)
		return (false);
	head->n_obj = mini->n_tr;
	while (++i < mini->n_tr)
			head->idx_tr_hbv[i] = i;
	mini->bvh = bvh_fill(mini, 0, head);
	if (!mini->bvh)
		return (false);
	head->zone_1 = NULL;
	head->zone_2 = NULL;
	mini->tmp = head;
	return (true);
}

void	init_mini_stack(t_mini *mini)
{
	mini->n_a = 0;
	mini->n_l = 0;
	mini->n_cam = 0;
	mini->thid = NULL;
	mini->n_pl = 0;
	mini->n_sp = 0;
	mini->n_cy = 0;
	mini->N_OBJ = 0;
	mini->N_LIGHT = 0;
	mini->cam_lock = 0;
	mini->n_tr = 0;
	mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	mini->thread_crash = false;
	mini->mouse.mid_pressed = 0;
}

t_boolean	init(t_mini *mini, char **av)
{
	init_mini_stack(mini);
	if (!parser(mini, av))
		return (false);
	if (mini->n_tr != 0)
	{
		if (!bvh_init(mini))
			return (free_mini(mini), false);
	}
	else
		mini->bvh = NULL;
	if (!open_window(mini))
		return (free_mini(mini), false);
	mini->error = malloc(sizeof(pthread_mutex_t));
	if (!mini->error)
		return(close_window(mini), false);
	if (pthread_mutex_init(mini->error, NULL) < 0)
		return (close_window(mini), false);
	return (true);
}
