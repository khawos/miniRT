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
	if (!open_window(mini))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_mini	mini;

	if (ac != 2)
		return (1);
	if (!init(&mini, av))
		return (1);
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
