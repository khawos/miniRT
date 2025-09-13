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

t_boolean	alloc_mini(t_mini *mini, int n_cam, int n_obj, int n_light)
{
	int	i;

	i = -1;
	mini->sc.cam = malloc(sizeof(t_cam) * n_cam);
	if (!mini->sc.cam)
		return (false);
	while (++i < n_cam)
		mini->sc.cam[i].name = NULL;
	mini->sc.nb_cam = n_cam;
	mini->sc.objet = malloc(sizeof(t_objet) * (n_obj));
	if (!mini->sc.objet)
		return (free(mini->sc.cam), false);
	i = -1;
	while (++i < n_obj)
		mini->sc.objet[i].name = NULL;
	mini->sc.nb_objet = n_obj;
	mini->sc.light = malloc(sizeof(t_light) * n_light);
	if (!mini->sc.light)
		return (free(mini->sc.objet), free(mini->sc.cam), false);
	i = -1;
	while (++i < n_light)
		mini->sc.light[i].name = NULL;
	mini->sc.nb_light = n_light;
	return (true);
}

t_boolean	count_line(t_mini *mini, char *file)
{
	char	*buffer;
	int		fd;
	int		n_cam;
	int		n_obj;
	int		n_light;

	n_cam = 0;
	n_obj = 0;
	n_light = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (ft_strncmp(buffer, "C", 1) == 0)
			n_cam++;
		else if (ft_strncmp(buffer, "L", 1) == 0 || ft_strncmp(buffer, "A", 1) == 0)
			n_light++;
		else if (*buffer != '\n')
			n_obj++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	printf("n_llight : %d, n_cam : %d, n_object : %d\n", n_light, n_cam, n_obj);
	if (!alloc_mini(mini, n_cam, n_obj, n_light))
		return (false);
	return (close(fd), true);
}
