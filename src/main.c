#include "miniRT.h"

t_boolean	init(t_mini *mini)
{
	if (!open_window(mini))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_mini	mini;
	
	(void)ac;
	(void)av;
	if (!init(&mini))
		return (1);
	mlx_hook(mini.display.mlx_win, DestroyNotify,
		StructureNotifyMask, &close_window, &mini);
	mlx_loop(mini.display.mlx);
	return (0);
}
