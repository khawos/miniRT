/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:45:30 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/25 15:20:26 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	is_a_fov_value(char	*word)
{
	if (!(atoi_double(word) >= 0 && atoi_double(word) <= 180))
		return (false);
	return (true);
}

t_boolean	is_a_strictly_positive_number(char *word)
{
	if (atoi_double(word) > 0 && atoi_double(word) <= INT_MAX)
		return (true);
	return (false);
}

int	count_coma(char *line)
{
	int	i;

	i = 0;
	while (*line)
	{
		if (*line == ',')
			i++;
		line++;
	}
	return (i);
}

t_boolean	alpha_problem(char *line)
{
	if (*line == '\n')
		return (true);
	line += 2;
	while (*line)
	{
		if (*line != ' ' && *line != '.' && *line != ',' && !ft_isdigit(*line)
			&& *line != '-' && *line != '\n')
			return (write(2, "error: '", 9), write(2, line, 1),
				write(2, "' : wrong input\n", 17), false);
		line++;
	}
	return (true);
}

t_boolean	nb_data_problem(char *line, char *type)
{
	if (ft_strncmp(type, "A", 1) == 0)
		if (count_coma(line) != 2)
			return (false);
	if (ft_strncmp(type, "C", 1) == 0 || ft_strncmp(type, "L", 1) == 0
		|| ft_strncmp(type, "sp", 2) == 0)
		if (count_coma(line) != 4)
			return (false);
	if (ft_strncmp(type, "pl", 2) == 0 || ft_strncmp(type, "cy", 2) == 0)
		if (count_coma(line) != 6)
			return (false);
	return (true);
}
