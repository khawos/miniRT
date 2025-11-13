/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:54:33 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 14:45:58 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	args_checker_c(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (4 != count_double_array(words))
		return (write(2, "Error: Wrong camera number of arguments\n", 41),
			free_double_array(words), false);
	if (!is_a_xyz_value(words[1]))
		return (write(2, "Error: Wrong camera coordinates\n", 33),
			free_double_array(words), false);
	if (!is_a_xyz_normalize_value(words[2]))
		return (write(2,
				"Error: Wrong camera normalized orientation vector\n", 51),
			free_double_array(words), false);
	if (!is_a_fov_value(words[3]))
		return (write(2,
				"Error: Wrong camera FOV\n", 25),
			free_double_array(words), false);
	return (free_double_array(words), true);
}

t_boolean	args_checker_l(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (4 != count_double_array(words))
		return (write(2,
				"Error: Wrong light number of arguments\n", 40),
			free_double_array(words), false);
	if (!is_a_xyz_value(words[1]))
		return (write(2,
				"Error: Wrong light coordinates\n", 32),
			free_double_array(words), false);
	if (!is_a_ratio(words[2]))
		return (write(2,
				"Error: Wrong light brightness ratio\n", 37),
			free_double_array(words), false);
	if (!is_a_rgb_value(words[3]))
		return (write(2,
				"Error: Wrong light RGB value\n", 30),
			free_double_array(words), false);
	return (free_double_array(words), true);
}

t_boolean	args_checker_sp(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (!is_a_xyz_value(words[1]))
		return (write(2,
				"Error: Wrong sphere coordinates\n", 33),
			free_double_array(words), false);
	if (!is_a_strictly_positive_number(words[2]))
		return (write(2,
				"Error: Wrong sphere diameter\n", 30),
			free_double_array(words), false);
	if (!is_a_rgb_value(words[3]))
		return (write(2,
				"Error: Wrong sphere RGB value\n", 31),
			free_double_array(words), false);
	return (free_double_array(words), true);
}

t_boolean	args_checker_pl(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (!is_a_xyz_value(words[1]))
		return (write(2,
				"Error: Wrong plane coordinates\n", 32),
			free_double_array(words), false);
	if (!is_a_xyz_normalize_value(words[2]))
		return (write(2,
				"Error: Wrong plane normalized orientation vector\n", 50),
			free_double_array(words), false);
	if (!is_a_rgb_value(words[3]))
		return (write(2,
				"Error: Wrong plane RGB value\n", 30),
			free_double_array(words), false);
	return (free_double_array(words), true);
}
