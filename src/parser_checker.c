#include "miniRT.h"

static char	*get_first_word(char *line)
{
	int		i;
	int		len;
	char	*type;

	len = 0;
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	len = i;
	type = malloc(sizeof(char *) * len + 1);
	ft_memset(type, 0, 3);
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
static t_boolean	is_a_rgb_value(char *word)
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

static	t_boolean	is_a_xyz_value(char	*word)
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

static	t_boolean	is_a_xyz_normalize_value(char	*word)
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

static	t_boolean	is_a_ratio(char	*word)
{
	if (!(atoi_double(word) >= 0 && atoi_double(word) <= 1))
		return (false);
	return (true);
}


static int	count_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);

}	

static t_boolean	args_checker_a(char *line)
{
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (3 != count_double_array(words))
		return (write(2, "Error: Wrong ambient number of arguments\n", 42), free_double_array(words), false);
	if (!is_a_ratio(words[1]))
		return (write(2, "Error: Wrong ambient light brightness ratio\n", 37), free_double_array(words), false);
	if (!is_a_rgb_value(words[2]))
		return (write(2, "Error: Wrong ambient RGB value\n", 24), free_double_array(words), false);
	
	return (free_double_array(words), true);
}

static	t_boolean	is_a_fov_value(char	*word)
{
	if (!(atoi_double(word) >= 0 && atoi_double(word) <= 180))
		return (false);
	return (true);
}

static t_boolean	args_checker_c(char *line)
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

static t_boolean	args_checker_l(char *line)
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

static	t_boolean	is_a_strictly_positive_number(char *word)
{
	if (atoi_double(word) > 0 && atoi_double(word) <= INT_MAX)
		return (true);
	return (false);
}

static	t_boolean	args_checker_sp(char *line)
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

static	t_boolean	args_checker_pl(char *line)
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

static	t_boolean	args_checker_cy(char *line)
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



static t_boolean	args_type_checker(char *type, char *line)
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

static t_boolean	alpha_problem(char *line)
{
	if (*line == '\n')
		return (true);
	line += 2;
	while (*line)
	{
		if (*line != ' ' &&  *line != '.' && *line != ',' && !ft_isdigit(*line)
			&& *line != '-' && *line != '\n')
			return (write(2, "error: '", 9), write(2, line, 1),
				write(2, "' : wrong input\n", 17), false);
		line++;
	}
	return (true);
}

static int	count_coma(char *line)
{
	int i;

	i = 0;
	while (*line)
	{
		if (*line == ',')
			i++;
		line++;
	}
	return (i);
}

static t_boolean	nb_data_problem(char *line , char *type)
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

static t_boolean	basic_line_checks(char *line, char *type)
{
	if (!alpha_problem(line))
		return (false);
	if (!nb_data_problem(line, type))
		return (write(2, "error : too much data on one line", 34), false);
	return (true);
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
	if (!(ft_strncmp(type, "A", 1) != 0 ||
		ft_strncmp(type, "C", 1) != 0 ||
		ft_strncmp(type, "L", 1) != 0 ||
		ft_strncmp(type, "pl", 2) != 0 ||
		ft_strncmp(type, "cy", 2) != 0 ||
		ft_strncmp(type, "sp", 2) != 0))
		return (write(2, "error: '", 19), write(2, type, ft_strlen(type)), 
			write(2, "' : identifier\n", 16), free(type), false);
	if (!basic_line_checks(line, type))
		return (free(type), false);
	if (!args_type_checker(type, line))
		return (free(type), false);
	return (free(type), true);
}

t_boolean	checker(char *file)
{
	int 	fd;
	char	*buffer;

	(void)check_object_type;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	while ((buffer = get_next_line(fd)))
	{
		if (!check_object_type(buffer))
			return (false);
		free(buffer);
	}
	close(fd);
	return (true);
}