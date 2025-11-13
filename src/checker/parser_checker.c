/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:53:54 by amedenec          #+#    #+#             */
/*   Updated: 2025/11/02 15:15:23 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_first_word(char *line)
{
	int		i;
	int		len;
	char	*type;

	len = 0;
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	len = i;
	type = malloc(sizeof(char) * (len + 1));
	ft_memset(type, 0, len + 1);
	if (!type)
		return (NULL);
	i = 0;
	while (i < len)
	{
		type[i] = line[i];
		i++;
	}
	return (type);
}

static t_boolean	check_object_type(char *line)
{
	char	*type;

	type = get_first_word(line);
	if (!type)
		return (false);
	if (ft_strlen(type) > 2)
		return (write(2, "error: '", 9), write(2, type, ft_strlen(type)),
			write(2, "' : identifier\n", 16), free(type), false);
	if ((ft_strncmp(type, "A", 1) != 0
			&& ft_strncmp(type, "C", 1) != 0
			&& ft_strncmp(type, "L", 1) != 0
			&& ft_strncmp(type, "pl", 2) != 0
			&& ft_strncmp(type, "cy", 2) != 0
			&& ft_strncmp(type, "tr", 2) != 0
			&& ft_strncmp(type, "sp", 2) != 0))
		return (write(2, "error: '", 9), write(2, type, ft_strlen(type)),
			write(2, "' : identifier\n", 16), free(type), false);
	if (!args_type_checker(type, line))
		return (free(type), false);
	return (free(type), true);
}

static t_boolean	check_object_occurance(char *line, t_boolean last_call)
{
	static int	count_a = 0;
	static int	count_c = 0;
	static int	count_l = 0;
	char		*type;

	if (1 == last_call)
	{
		if (count_c == 0 || count_a == 0 || count_l == 0)
			return (false);
		return (true);
	}
	type = get_first_word(line);
	if (!type)
		return (false);
	if (ft_strncmp(type, "A", 1) == 0)
		count_a++;
	if (ft_strncmp(type, "C", 1) == 0)
		count_c++;
	if (ft_strncmp(type, "L", 1) == 0)
		count_l++;
	if (count_a > 1 || count_c > 1)
		return (free(type), false);
	return (free(type), true);
}

static t_boolean	check_object_func(char *buffer)
{
	if (!check_object_type(buffer))
		return (write(2, "object naming/occurence problem\n"
				, 33), free(buffer), false);
	if (!check_object_occurance(buffer, 0))
		return (write(2, "object naming/occurence problem\n", 33)
			, free(buffer), false);
	return (true);
}

t_boolean	checker(char *file)
{
	int		fd;
	char	*buffer;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if ((*buffer >= 9 && *buffer <= 13))
		{
			free(buffer);
			buffer = get_next_line(fd);
			continue ;
		}
		if (!check_object_func(buffer))
			return (clear_gnl(fd), false);
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	if (check_object_occurance(NULL, 1) == 0)
		return (write(2, "object occurence problem\n", 26), false);
	return (true);
}
