/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:31:49 by amedenec          #+#    #+#             */
/*   Updated: 2025/11/13 12:52:57 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	check_rt(char *file_name)
{
	if (ft_strlen(file_name) < 4)
		return (false);
	while (*file_name)
		file_name++;
	file_name -= 3;
	if (ft_strncmp(file_name, ".rt", 3))
		return (false);
	return (true);
}

t_boolean	parser(t_mini *mini, char **av)
{
	if (!check_rt(av[1]))
		return (write(2, "Error\nMiniRT:Wrong file name.\n", 31), false);
	if (!checker(av[1]))
		return (false);
	if (!count_line(mini, av[1]))
		return (false);
	if (!fill_mini(mini, av[1]))
		return (free_mini(mini), false);
	(void)mini;
	return (true);
}

t_boolean	alloc_mini(t_mini *mini, int n_array[4])
{
	int	i;

	i = -1;
	mini->sc.cam = malloc(sizeof(t_cam) * n_array[0]);
	if (!mini->sc.cam)
		return (false);
	while (++i < n_array[0])
		mini->sc.cam[i].name = NULL;
	mini->sc.nb_cam = n_array[0];
	mini->sc.objet = malloc(sizeof(t_objet) * (n_array[1]));
	if (!mini->sc.objet)
		return (free(mini->sc.cam), false);
	i = -1;
	while (++i < n_array[1])
		mini->sc.objet[i].name = NULL;
	mini->sc.nb_objet = n_array[1];
	mini->sc.light = malloc(sizeof(t_light) * n_array[2]);
	if (!mini->sc.light)
		return (free(mini->sc.objet), free(mini->sc.cam), false);
	if (false == alloc_mini_healper(mini, n_array))
		return (false);
	return (true);
}

static void	count_elements(char *buffer, int n_array[4])
{
	if (ft_strncmp(buffer, "C", 1) == 0)
		(n_array[0])++;
	else if (ft_strncmp(buffer, "L", 1) == 0
		|| ft_strncmp(buffer, "A", 1) == 0)
		(n_array[2])++;
	else if (*buffer != '\n' && *buffer != 't')
		(n_array[1])++;
	else if (ft_strncmp(buffer, "tr", 2) == 0)
		(n_array[3])++;
}

t_boolean	count_line(t_mini *mini, char *file)
{
	char			*buffer;
	int				fd;
	static int		n_array[4] = {0};

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	buffer = get_next_line(fd);
	while (buffer)
	{
		count_elements(buffer, n_array);
		free(buffer);
		buffer = get_next_line(fd);
	}
	if (!alloc_mini(mini, n_array))
		return (false);
	close(fd);
	printf("allocared\n");
	return (true);
}
