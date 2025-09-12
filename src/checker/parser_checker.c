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

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	while ((buffer = get_next_line(fd)))
	{
		if (!check_object_type(buffer))
			return (free(buffer), false);
		free(buffer);
	}
	close(fd);
	return (true);
}