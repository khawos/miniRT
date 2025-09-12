/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:26:16 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 14:40:02 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	fill_mini_switch(t_mini *mini, char *buffer, int i)
{
	if (!ft_strncmp(buffer, "C", i))
		return (parse_cam(mini, buffer), true);
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
