/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:40:37 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/30 21:52:27 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mini	mini;

	if (ac != 2)
		return (1);
	if (!init(&mini, av))
		return (1);
//	printAllObject(&mini);
	sem_unlink("/cast_init");
	sem_unlink("/image");
	mini.m_cast = sem_open("/cast_init", O_CREAT | O_EXCL, 0644, 1);
	mini.s_img = sem_open("/image", O_CREAT | O_EXCL, 0644, 24);
	set_up_cam(&mini);
	mini.sc.cam[mini.cam_lock].vec_dir = vec_normalize(
	mini.sc.cam[mini.cam_lock].vec_dir);
	set_normal_tr(&mini);
	if (!run_thread(&mini))
		return (-1);
	mlx_hook(mini.display.mlx_win, DestroyNotify,
		StructureNotifyMask, &close_window, &mini);
	mlx_hook(mini.display.mlx_win, KeyPress, KeyPressMask,
		handle_key_input, &mini);
	mlx_hook(mini.display.mlx_win, ButtonPress, ButtonPressMask, handle_mouse_press, &mini);
	mlx_hook(mini.display.mlx_win, ButtonRelease, ButtonReleaseMask, handle_mouse_release, &mini);
	mlx_hook(mini.display.mlx_win, MotionNotify, PointerMotionMask, handle_mouse_move, &mini);
	mlx_hook(mini.display.mlx_win, KeyPress, KeyPressMask, handle_key_press, &mini);
	mlx_hook(mini.display.mlx_win, KeyRelease, KeyReleaseMask, handle_key_release, &mini);
	mlx_loop_hook(mini.display.mlx, render_loop, &mini);
	mlx_loop(mini.display.mlx);
	sem_close(mini.m_cast);
	sem_unlink("/cast_init");
	return (0);
}
