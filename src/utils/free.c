/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:35:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:29:23 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_map(t_objet obj)
{
	int	i;

	i = -1;
	if (obj.mat.albedo.map)
	{
		while (++i < obj.mat.albedo.size.v)
			free(obj.mat.albedo.map[i]);
		free(obj.mat.albedo.map);
	}
	i = -1;
	if (obj.mat.normal.map)
	{
		while (++i < obj.mat.normal.size.v)
			free(obj.mat.normal.map[i]);
		free(obj.mat.normal.map);
	}
	i = -1;
	if (obj.mat.roughness.map)
	{
		while (++i < obj.mat.roughness.size.v)
			free(obj.mat.roughness.map[i]);
		free(obj.mat.roughness.map);
	}
}

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
		if (mini->sc.objet[i].type == sp)
			free_map(mini->sc.objet[i]);
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
