/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:35:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/12 14:53:21 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	free_double_array_error(void **array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(array[i]);
	}
	free(array);
}