#include "miniRT.h"

t_boolean	check_rt(char *file_name)
{
	while (file_name)
		file_name++;
	file_name -= 3;
	if (ft_strncmp(file_name, ".rt", 3))
		return (false);
	return (true);
}

t_boolean	parser(t_mini *mini, char **av)
{
	int	fd;
	char	*buffer;
	int	n_cam;

	n_cam = 0;
	if (!check_rt(av[1]))
		return (false);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (false);
	count_line(mini, av[1]);

}

t_boolean	alloc_mini(t_mini *mini, int n_cam, int n_line)
{
	mini->scene.cam = malloc(sizeof(t_cam) * n_cam);
	if (!mini->scene.cam)
		return (false);
	mini->scene.nb_cam = n_cam;
	mini->scene.nb_objet = malloc(sizeof(t_objet) * (n_line - n_cam));
	if (!mini->scene.nb_objet)
		return (false);
	mini->scene.nb_objet = n_line - n_cam;
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
		while (buffer == ' ')
			buffer++;					// IS_SPACE
		if (ft_strncmp(buffer, "C", 1) == 0)
			n_cam++;
		n_line++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
	if (!alloc_mini(mini, n_cam, n_line))
		return (false);
	return (true);
}
