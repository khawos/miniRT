/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-06 10:54:33 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-06 10:54:33 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	args_checker_c(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (4 != count_double_array(words))
		return (write(2, "Error: Wrong camera number of arguments\n", 41), free_double_array(words), false);
	if (!is_a_xyz_value(words[1]))
		return (write(2, "Error: Wrong camera coordinates\n", 26), free_double_array(words), false);
	if (!is_a_xyz_normalize_value(words[2]))
		return (write(2, "Error: Wrong camera normalized orientation vector\n", 44), free_double_array(words), false);
	if (!is_a_fov_value(words[3]))
		return (write(2, "Error: Wrong camera FOV\n", 25), free_double_array(words), false);
	return (free_double_array(words), true);
}

t_boolean	args_checker_l(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (4 != count_double_array(words))
		return (write(2, "Error: Wrong light number of arguments\n", 40), free_double_array(words), false);
	if (!is_a_xyz_value(words[1]))
		return (write(2, "Error: Wrong light coordinates\n", 26), free_double_array(words), false);
	if (!is_a_ratio(words[2]))
		return (write(2, "Error: Wrong light brightness ratio\n", 37), free_double_array(words), false);
	if (!is_a_rgb_value(words[3]))
		return (write(2, "Error: Wrong light RGB value\n", 30), free_double_array(words), false);
	return (free_double_array(words), true);
}

t_boolean	args_checker_sp(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (4 != count_double_array(words))
		return (write(2, "Error: Wrong sphere number of arguments\n", 41), free_double_array(words), false);
	if (!is_a_xyz_value(words[1]))
		return (write(2, "Error: Wrong sphere coordinates\n", 26), free_double_array(words), false);
	if (!is_a_strictly_positive_number(words[2]))
		return (write(2, "Error: Wrong sphere diameter\n", 30), free_double_array(words), false);
	if (!is_a_rgb_value(words[3]))
		return (write(2, "Error: Wrong sphere RGB value\n", 24), free_double_array(words), false);
	return (true);
}

t_boolean	args_checker_pl(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (4 != count_double_array(words))
		return (write(2, "Error: Wrong plane number of arguments\n", 40), free_double_array(words), false);
	if (!is_a_xyz_value(words[1]))
		return (write(2, "Error: Wrong plane coordinates\n", 26), free_double_array(words), false);
	if (!is_a_xyz_normalize_value(words[2]))
		return (write(2, "Error: Wrong plane normalized orientation vector\n", 44), free_double_array(words), false);
	if (!is_a_rgb_value(words[3]))
		return (write(2, "Error: Wrong plane RGB value\n", 24), free_double_array(words), false);
	return (true);
}

t_boolean	args_checker_cy(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (6 != count_double_array(words))
		return (write(2, "Error: Wrong cylinder number of arguments\n", 43), free_double_array(words), false);
	if (!is_a_xyz_value(words[1]))
		return (write(2, "Error: Wrong coordinates\n", 26), free_double_array(words), false);
	if (!is_a_xyz_normalize_value(words[2]))
		return (write(2, "Error: Wrong normalized orientation vector\n", 44), free_double_array(words), false);
	if (!is_a_strictly_positive_number(words[3]))
		return (write(2, "Error: Wrong cylender diameter\n", 32), free_double_array(words), false);
	if (!is_a_strictly_positive_number(words[4]))
		return (write(2, "Error: Wrong cylender height\n", 30), free_double_array(words), false);
	if (!is_a_rgb_value(words[5]))
		return (write(2, "Error: Wrong RGB value\n", 24), free_double_array(words), false);
	return (true);
}
