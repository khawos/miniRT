/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:43:34 by amedenec          #+#    #+#             */
/*   Updated: 2025/11/01 10:43:35 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	alloc_mini_healper(t_mini *mini, int n_array[4])
{
	int	i;

	i = -1;
	while (++i < n_array[2])
		mini->sc.light[i].name = NULL;
	mini->sc.nb_light = n_array[2];
	i = -1;
	mini->sc.objet_tr = malloc(sizeof(t_objet) * n_array[3]);
	if (!mini->sc.objet_tr)
		return (free(mini->sc.objet), free(mini->sc.cam),
			free(mini->sc.light), false);
	while (++i < n_array[3])
		mini->sc.objet_tr[i].name = NULL;
	return (true);
}
