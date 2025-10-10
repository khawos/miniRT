/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_initalisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-09 17:22:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-09 17:22:09 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	get_ambiant(t_mini *mini)
{
	int	i;

	i = -1;
	while (i++ < mini->N_LIGHT)
		if (mini->sc.light[i].type == A)
			return (mini->sc.light[i]);
	return ((t_light){0});
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
	mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	if (!parser(mini, av))
		return (false);
	if (pthread_mutex_init(&mini->render_mutex, NULL) < 0)
		return (false);												// ATTENTION FREE
	mini->sc.ambiant = get_ambiant(mini);
	if (!open_window(mini))
		return (false);
	return (true);
}
