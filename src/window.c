#include "miniRT.h"

t_boolean	open_window_2(t_mini *mini)
{
	mini->display.img.img = mlx_new_image(mini->display.mlx, HEIGHT, WIDTH);
	if (!mini->display.img.img)
		return (mlx_destroy_window(mini->display.mlx, mini->display.mlx_win),
			mlx_destroy_display(mini->display.mlx),
			free(mini->display.mlx), false);
	mini->display.img.addr = mlx_get_data_addr(mini->display.img.img,
			&mini->display.img.bits_per_pixel,
			&mini->display.img.line_length,
			&mini->display.img.endian);
	if (!mini->display.img.addr)
	{
		mlx_destroy_image(mini->display.mlx, mini->display.img.img);
		mlx_destroy_window(mini->display.mlx, mini->display.mlx_win);
		return (mlx_destroy_display(mini->display.mlx),
			free(mini->display.mlx), false);
	}
	return (true);
}

t_boolean	open_window(t_mini *mini)
{
	mini->display.mlx = mlx_init();
	if (!mini->display.mlx)
		return (false);
	mini->display.mlx_win = mlx_new_window(mini->display.mlx,
			HEIGHT, WIDTH, "miniRT");
	if (!mini->display.mlx_win)
		return (mlx_destroy_display(mini->display.mlx),
			free(mini->display.mlx), false);
	open_window_2(mini);
	return (true);
}

int	close_window(t_mini *mini)
{
	mlx_destroy_image(mini->display.mlx, mini->display.img.img);
	mlx_destroy_window(mini->display.mlx, mini->display.mlx_win);
	mlx_destroy_display(mini->display.mlx);
	free(mini->display.mlx);
	free_mini(mini);
	exit(0);
	return (0);
}
