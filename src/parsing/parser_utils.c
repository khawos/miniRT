/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-08 16:56:30 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-08 16:56:30 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_point(char **buffer)
{
	t_vec3	result;

	result.x = __atoi_double(buffer);
	*buffer += 1;
	result.y = __atoi_double(buffer);
	*buffer += 1;
	result.z = __atoi_double(buffer);
	return (result);
}

t_color	get_color(char **buffer)
{
	t_color	color;

	color.r = __atoi_double(buffer);
	*buffer += 1;
	color.g = __atoi_double(buffer);
	*buffer += 1;
	color.b = __atoi_double(buffer);
	return (color);
}

double	get_spec(char *buffer)
{
	char	*str;
	double	spec;

	spec = -1;
	str = ft_strnstr(buffer, "spec=", ft_strlen(buffer));
	if (str)
	{
		while(ft_isalpha(*str))
			str++;
		str++;
		spec = atoi_double(str);
	}
	return (spec);
}