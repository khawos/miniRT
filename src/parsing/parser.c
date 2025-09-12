#include "miniRT.h"

t_boolean	check_rt(char *file_name)
{
	if (ft_strlen(file_name) < 4)
		return (false);
	while (*file_name)
		file_name++;
	file_name -= 3;
	if (ft_strncmp(file_name, ".rt", 3))
		return (false);
	return (true);
}

t_boolean	parser(t_mini *mini, char **av)
{
	int	n_cam;

	n_cam = 0;
	if (!check_rt(av[1]))
		return (write(2, "Error\nMiniRT:Wrong file name.\n", 31), false);
	if (!checker(av[1]))
		return (false);
	count_line(mini, av[1]);
	fill_mini(mini, av[1]);
	return (true);
}

t_boolean	alloc_mini(t_mini *mini, int n_cam, int n_line)
{
	int	i;

	i = -1;
	mini->sc.cam = malloc(sizeof(t_cam) * n_cam);
	if (!mini->sc.cam)
		return (false);
	while (++i < n_cam)
		mini->sc.cam[i].name = NULL;
	mini->sc.nb_cam = n_cam;
	mini->sc.objet = malloc(sizeof(t_objet) * (n_line - n_cam));
	if (!mini->sc.objet)
		return (false);
	i = -1;
	while (++i < n_line - n_cam)
		mini->sc.objet[i].name = NULL;
	mini->sc.nb_objet = n_line - n_cam;
	return (true);
}

t_boolean	count_line(t_mini *mini, char *file)
{
	char	*buffer;
	int		fd;
	int		n_cam;
	int		n_line;

	n_cam = 0;
	n_line = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (ft_strncmp(buffer, "C", 1) == 0)
			n_cam++;
		if (*buffer != '\n')
			n_line++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	if (!alloc_mini(mini, n_cam, n_line))
		return (false);
	return (close(fd), true);
}
