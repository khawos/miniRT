/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:35:47 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:31:49 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	tab_len(char **line_split)
{
	int	i;

	if (!line_split)
		return (0);
	i = 0;
	while (line_split[i])
		i++;
	return (i);
}

char	**new_tab_init(char **new_tab, char *new)
{
	new_tab[0] = ft_strdup(new);
	if (!new_tab[0])
		return (free_double_array_error((void **)new_tab, 2), NULL);
	new_tab[1] = NULL;
	return (new_tab);
}

char	**realloc_add_to_tab(char **tab, char *new)
{
	char	**new_tab;
	int		len;
	int		i;

	if (!new)
		return (tab);
	i = -1;
	len = tab_len(tab);
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (free_double_array(tab), NULL);
	if (!tab)
		return (new_tab_init(new_tab, new));
	while (tab[++i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
			return (free_double_array(tab),
				free_double_array_error((void **)new_tab, i), NULL);
	}
	new_tab[i] = ft_strdup(new);
	if (!new_tab[i])
		return (free_double_array(tab),
			free_double_array_error((void **)new_tab, i), NULL);
	return (new_tab[i + 1] = NULL, free_double_array(tab), new_tab);
}
