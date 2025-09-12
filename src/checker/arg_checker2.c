/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:00:56 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 14:22:28 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	args_checker_a(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (3 != count_double_array(words))
		return (write(2, "Error: Wrong ambient number of arguments\n", 42), free_double_array(words), false);
	if (!is_a_ratio(words[1]))
		return (write(2, "Error: Wrong ambient light brightness ratio\n", 45), free_double_array(words), false);
	if (!is_a_rgb_value(words[2]))
		return (write(2, "Error: Wrong ambient RGB value\n", 32), free_double_array(words), false);
	
	return (free_double_array(words), true);
}

t_boolean	args_type_checker(char *type, char *line)
{
	if (ft_strncmp(type, "A", 1) == 0)
		if (!args_checker_a(line))
			return (false);
	if (ft_strncmp(type, "C", 1) == 0)
		if (!args_checker_c(line))
			return (false);
	if (ft_strncmp(type, "L", 1) == 0)
		if (!args_checker_l(line))
			return (false);
	if (ft_strncmp(type, "sp", 2) == 0)
		if (!args_checker_sp(line))
			return (false);
	if (ft_strncmp(type, "pl", 2) == 0)
		if (!args_checker_pl(line))
			return (false);
	if (ft_strncmp(type, "cy", 2) == 0)
		if (args_checker_cy(line) == 0)
			return (false);

	return (true);		
}