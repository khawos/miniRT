/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:31:49 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/30 23:14:14 by jbayonne         ###   ########.fr       */
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
	//if (!checker(av[1]))
	//	return (false);
	if (!count_line(mini, av[1]))
		return (false);
	if (!fill_mini(mini, av[1]))
		return (free_mini(mini), false);
	return (true);
}

t_boolean	alloc_mini(t_mini *mini, int n_cam, int n_obj, int n_light, int n_tr)
{
	int	i;

	i = -1;
	mini->sc.cam = malloc(sizeof(t_cam) * n_cam);
	if (!mini->sc.cam)
		return (false);
	while (++i < n_cam)
		mini->sc.cam[i].name = NULL;
	mini->sc.nb_cam = n_cam;
	mini->sc.objet = malloc(sizeof(t_objet) * (n_obj));
	if (!mini->sc.objet)
		return (free(mini->sc.cam), false);
	i = -1;
	while (++i < n_obj)
		mini->sc.objet[i].name = NULL;
	mini->sc.nb_objet = n_obj;
	mini->sc.light = malloc(sizeof(t_light) * n_light);
	if (!mini->sc.light)
		return (free(mini->sc.objet), free(mini->sc.cam), false);
	i = -1;
	while (++i < n_light)
		mini->sc.light[i].name = NULL;
	mini->sc.nb_light = n_light;
	i = -1;
	mini->sc.objet_tr = malloc(sizeof(t_objet) * n_tr);
	if (!mini->sc.objet_tr)
		return (free(mini->sc.objet), free(mini->sc.cam), free(mini->sc.light), false);
	while (++i < n_tr)
		mini->sc.objet_tr[i].name = NULL;
	return (true);
}

static void	count_elements(char *buffer, int *n_cam, int *n_obj, int *n_light, int *n_tr)
{
	if (ft_strncmp(buffer, "C", 1) == 0)
		(*n_cam)++;
	else if (ft_strncmp(buffer, "L", 1) == 0
		|| ft_strncmp(buffer, "A", 1) == 0)
		(*n_light)++;
	else if (*buffer != '\n' && *buffer != 't')
		(*n_obj)++;
	else if (ft_strncmp(buffer, "tr", 2) == 0)
		(*n_tr)++;
}

t_boolean	count_line(t_mini *mini, char *file)
{
	char	*buffer;
	int		fd;
	int		n_cam;
	int		n_obj;
	int		n_tr;
	int		n_light;

	n_cam = 0;
	n_obj = 0;
	n_tr = 0;
	n_light = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	buffer = get_next_line(fd);
	while (buffer)
	{
		count_elements(buffer, &n_cam, &n_obj, &n_light, &n_tr);
		free(buffer);
		buffer = get_next_line(fd);
	}
	if (!alloc_mini(mini, n_cam, n_obj, n_light, n_tr))
		return (false);
	close(fd);
	return (true);
}
