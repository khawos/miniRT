/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:46:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 16:57:03 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	is_digit_or_space_str(char *str)
{
	while (ft_isdigit(*str) || *str == ' ' || *str == '"' || *str == ',')
		str++;
	if (*str == '\n')
		return (true);
	return (false);
}

t_boolean	is_on_xpm_pixel_info(char *str)
{
	if (ft_strncmp(str, "/* pixels */\n", 14) == 0)
		return (true);
	return (false);
}

t_vec2	get_texture_dimension(int fd)
{
	char	*buffer;
	t_vec2	dimension;
	char	*tmp;

	buffer = get_next_line(fd);
	free(buffer);
	buffer = get_next_line(fd);
	while (!is_digit_or_space_str(buffer))
	{
		free(buffer);
		buffer = get_next_line(fd);
	}
	tmp = buffer;
	buffer++;
	dimension.u = __atoi_double(&buffer);
	dimension.v = __atoi_double(&buffer);
	free(tmp);
	return (dimension);
}	

char	*go_to_pixel_info(int fd)
{
	char	*buffer;

	buffer = get_next_line(fd);
	while (!is_on_xpm_pixel_info(buffer))
	{
		free(buffer);
		buffer = get_next_line(fd);
	}
	free(buffer);
	buffer = get_next_line(fd);
	return (buffer);
}
