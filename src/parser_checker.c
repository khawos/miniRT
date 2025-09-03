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
	while (words[i])
	{
		if (!(ft_atoi(words[i]) >= 0 && ft_atoi(words[i]) <= 255)) // check if the rgb value is between 0 ans 255
			return (free_double_array(words), false);
		i++;
	}
	return (free_double_array(words), true);
}

static t_boolean	args_checker_a(char *line)
{
	char **words;

	words = ft_split(line, ' ');
	if (!words)
		return (false);
	if (!(atoi_double(words[1]) >= 0 && atoi_double(words[1]) <= 1))
		return (free_double_array(words), false);
	if (!is_a_rgb_value(words[2]))
		return (free_double_array(words), false);
	
	return (free_double_array(words), true);
}

static t_boolean	args_type_checker(char *type, char *line)
{
	if (ft_strncmp(type, "A", 1) == 0)
		if (!args_checker_a(line))
			return (false);
	printf("JE SUIS LA\n");
	(void)line;
	return (true);		
}

static t_boolean check_object_type(char *line)
{
	char	*type;

	type = get_first_word(line);
	if (!type)
		return (false);
	printf("%s\n", type);
	

	if (!(ft_strncmp(type, "A", 1) != 0 ||
		ft_strncmp(type, "C", 1) != 0 ||
		ft_strncmp(type, "L", 1) != 0 ||
		ft_strncmp(type, "pl", 2) != 0 ||
		ft_strncmp(type, "cy", 2) != 0 ||
		ft_strncmp(type, "sp", 2) != 0))
		return (free(type), false);
	if (!args_type_checker(type, line))
		return (free(type), false);
	return (free(type), true);
}

t_boolean checker(char *file)
{
	int 	fd;
	char	*buffer;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);

	buffer = get_next_line(fd);
	if (buffer == NULL)
		return (false);
	while (buffer)
	{
		if (!check_object_type(buffer))
			return (false);
		printf("JE SUIS ICI\n");
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (true);
}