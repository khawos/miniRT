/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-06 10:41:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-06 10:41:03 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	is_a_xyz_value(char	*word)
{
	char	**words;
	int		i;

	i = 0;
	words = ft_split(word, ',');
	if (!words)
		return (false);
	while (words[i])
	{
		if (!(atoi_double(words[i]) >= INT_MIN && atoi_double(words[i]) <= INT_MAX)) // A CHANGER pour les doubles
			return (free_double_array(words), false);
		i++;
	}
	return (free_double_array(words), true);
}

t_boolean	is_a_xyz_normalize_value(char *word)
{
	char	**words;
	int		i;

	i = 0;
	words = ft_split(word, ',');
	if (!words)
		return (false);
	while (words[i])
	{
		if (!(atoi_double(words[i]) >= -1 && atoi_double(words[i]) <= 1))
			return (free_double_array(words), false);
		i++;
	}
	return (free_double_array(words), true);
}

t_boolean	is_a_ratio(char	*word)
{
	if (!(atoi_double(word) >= 0 && atoi_double(word) <= 1))
		return (false);
	return (true);
}

t_boolean	is_a_rgb_value(char *word)
{
	char	**words;
	int		i;

	i = 0;
	words = ft_split(word, ',');
	if (!words)
		return (false);
	while (words[i])
	{
		if (!(ft_atoi(words[i]) >= 0 && ft_atoi(words[i]) <= 255)) // check if the rgb value is between 0 ans 255
			return (free_double_array(words), false);
		i++;
	}
	return (free_double_array(words), true);
}

int	count_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);

}
