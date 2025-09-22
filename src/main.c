/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:40:37 by amedenec          #+#    #+#             */
/*   Updated: 2025/09/15 14:58:56 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	get_ambiant(t_mini *mini)
{
	int	i;

	i = -1;
	while (i++ < mini->N_LIGHT)
		if (mini->sc.light[i].type == A)
			return (mini->sc.light[i]);
	return ((t_light){0});
}

t_boolean	init(t_mini *mini, char **av)
{
	mini->n_a = 0;
	mini->n_l = 0;
	mini->n_cam = 0;
	mini->n_pl = 0;
	mini->n_sp = 0;
	mini->n_cy = 0;
	mini->N_OBJ = 0;
	mini->N_LIGHT = 0;
	mini->cam_lock = 0;
	if (!parser(mini, av))
		return (false);
	mini->sc.ambiant = get_ambiant(mini);
	if (!open_window(mini))
		return (false);
	return (true);
}

void testcolor(t_mini *mini)
{
	t_color red = (t_color){255,0,0,0};
	t_color blue = (t_color){0,0,255,0};
	t_color green = (t_color){0,255,0,0};
	t_color white = (t_color){255,255,255,0};

	(void)blue;
	(void)green;
	(void)red;
	(void)white;
	for (int i = 0; i < HEIGHT ; i++){
		for (int j = 0; j < WIDTH; j++){
			my_mlx_pixel_put(mini, j, i, color_shift(color_multiplie(blue, green)));
		}
	}
}

int	main(int ac, char **av)
{
	t_mini	mini;

	if (ac != 2)
		return (1);
	if (!init(&mini, av))
		return (1);
	mini.sc.cam[mini.cam_lock].vec_dir = vec_normalize(mini.sc.cam[mini.cam_lock].vec_dir);
	//testcolor(&mini);
	set_up_cam(&mini);
	cast(&mini);
	mlx_hook(mini.display.mlx_win, DestroyNotify,
		StructureNotifyMask, &close_window, &mini);
	mlx_put_image_to_window(mini.display.mlx, mini.display.mlx_win,
		mini.display.img.img, 0, 0);
	printf("Render finish\n");
	mlx_hook(mini.display.mlx_win, KeyPress, KeyPressMask, handle_key_input, (t_mini *)&mini);
	mlx_loop(mini.display.mlx);
	return (0);
}
