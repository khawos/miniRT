/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:46:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 15:33:40 by jbayonne         ###   ########.fr       */
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

void	get_texture_dimension(int fd, t_vec2 *dimension)
{
	char	*buffer;

	buffer = get_next_line(fd);
	printf("buffer : %s\n", buffer);
	while (!is_digit_or_space_str(buffer))
	{
		free(buffer);
		buffer = get_next_line(fd);
	}
	buffer++;
	dimension->u = __atoi_double(&buffer);
	dimension->v = __atoi_double(&buffer);
	printf("u : %d, v : %d\n", dimension->u,dimension->v);
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