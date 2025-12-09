/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:26:16 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 16:21:15 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	fill_mini_switch(t_mini *mini, char *buffer)
{
	if (!ft_strncmp(buffer, "C", 1))
	{
		parse_cam(mini, buffer);
		return (true);
	}
	if (!ft_strncmp(buffer, "A", 1))
		return (parse_a(mini, buffer), true);
	if (!ft_strncmp(buffer, "L", 1))
		return (parse_l(mini, buffer), true);
	if (!ft_strncmp(buffer, "sp", 2))
		return (parse_sp(mini, buffer));
	if (!ft_strncmp(buffer, "pl", 2))
		return (parse_pl(mini, buffer));
	if (!ft_strncmp(buffer, "cy", 2))
		return (parse_cy(mini, buffer), true);
	if (!ft_strncmp(buffer, "tr", 2))
		return (parse_tr(mini, buffer), true);
	return (false);
}

t_boolean	fill_mini_decrypt(t_mini *mini, char *buffer)
{
	int	i;

	i = 0;
	if ((*buffer >= 9 && *buffer <= 13))
		return (true);
	while (ft_isalpha(*buffer))
	{
		i++;
		buffer++;
	}
	buffer -= i;
	if (!fill_mini_switch(mini, buffer))
		return (false);
	return (true);
}

t_boolean	fill_mini(t_mini *mini, char *file_name)
{
	int		fd;
	char	*buffer;
	char	*tmp;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (false);
	buffer = get_next_line(fd);
	while (buffer)
	{
		tmp = buffer;
		if (!fill_mini_decrypt(mini, buffer))
			return (free(buffer), false);
		free(tmp);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (true);
}

void	parse_cy(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->n_obj].id = mini->n_obj;
	mini->sc.objet[mini->n_obj].type = cy;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->n_obj].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->n_obj].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->n_obj].pos.z = __atoi_double(&buffer);
	mini->sc.objet[mini->n_obj].vec_dir.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->n_obj].vec_dir.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->n_obj].vec_dir.z = __atoi_double(&buffer);
	mini->sc.objet[mini->n_obj].vec_dir
		= vec_normalize(mini->sc.objet[mini->n_obj].vec_dir);
	mini->sc.objet[mini->n_obj].diameter = __atoi_double(&buffer);
	mini->sc.objet[mini->n_obj].height = __atoi_double(&buffer);
	mini->sc.objet[mini->n_obj].color = get_color(&buffer);
	mini->sc.objet[mini->n_obj].spec = get_spec(buffer);
	mini->sc.objet[mini->n_obj]
		.roughness_default = get_roughness_default(buffer);
	mini->n_cy++;
	mini->n_obj++;
}
