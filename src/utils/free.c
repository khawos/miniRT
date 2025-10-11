/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:35:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 15:24:14 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_mini(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->sc.nb_cam)
	{
		free(mini->sc.cam[i].name);
		i++;
	}
	free(mini->sc.cam);
	i = 0;
	while (i < mini->sc.nb_objet)
	{
		free(mini->sc.objet[i].name);
		i++;
	}
	free(mini->sc.objet);
	i = 0;
	while (i < mini->sc.nb_light)
	{
		free(mini->sc.light[i].name);
		i++;
	}
	free(mini->sc.light);
}

void	free_double_array(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
		free(dest[i++]);
	free(dest);
}
