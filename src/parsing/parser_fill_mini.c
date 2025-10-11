/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:26:16 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/25 14:33:32 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	fill_mini_switch(t_mini *mini, char *buffer, int i)
{
	if (!ft_strncmp(buffer, "C", i))
	{
		parse_cam(mini, buffer);
		return (true);
	}
	if (!ft_strncmp(buffer, "A", i))
		return (parse_a(mini, buffer), true);
	if (!ft_strncmp(buffer, "L", i))
		return (parse_l(mini, buffer), true);
	if (!ft_strncmp(buffer, "sp", i))
		return (parse_sp(mini, buffer), true);
	if (!ft_strncmp(buffer, "pl", i))
		return (parse_pl(mini, buffer), true);
	if (!ft_strncmp(buffer, "cy", i))
		return (parse_cy(mini, buffer), true);
	if (!ft_strncmp(buffer, "tr", i))
		return (parse_tr(mini, buffer), true);
	return (false);
}

t_boolean	fill_mini_decrypt(t_mini *mini, char *buffer)
{
	int	i;

	i = 0;
	if (*buffer == '\n')
		return (true);
	while (ft_isalpha(*buffer))
	{
		i++;
		buffer++;
	}
	buffer -= i;
	if (!fill_mini_switch(mini, buffer, i))
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
		return (free_mini(mini), false);
	buffer = get_next_line(fd);
	while (buffer)
	{
		tmp = buffer;
		fill_mini_decrypt(mini, buffer);
		free(tmp);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (true);
}

void	parse_cy(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = cy;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].vec_dir.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].vec_dir.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].vec_dir.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].diameter = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].height = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color.r = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color.g = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color.b = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].spec = get_spec(buffer);
	mini->n_cy++;
	mini->N_OBJ++;
}
