/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:10:15 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/01 09:22:21 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	toggle_hook(t_mini mini)
{
	mlx_hook(mini.display.mlx_win, DestroyNotify,
		StructureNotifyMask, &close_window, &mini);
	mlx_hook(mini.display.mlx_win, KeyPress, KeyPressMask,
		handle_key_input, &mini);
	mlx_hook(mini.display.mlx_win, ButtonPress,
		ButtonPressMask, handle_mouse_press, &mini);
	mlx_hook(mini.display.mlx_win, ButtonRelease,
		ButtonReleaseMask, handle_mouse_release, &mini);
	mlx_hook(mini.display.mlx_win, MotionNotify,
		PointerMotionMask, handle_mouse_move, &mini);
	mlx_hook(mini.display.mlx_win, KeyPress,
		KeyPressMask, handle_key_press, &mini);
	mlx_hook(mini.display.mlx_win, KeyRelease,
		KeyReleaseMask, handle_key_release, &mini);
	mlx_loop_hook(mini.display.mlx, render_loop, &mini);
	mlx_loop(mini.display.mlx);
}

int	handle_key_input_bis(int keysym, t_mini *mini, t_cam *cam)
{
	(void)mini;
	if (keysym == 0xff52)
		cam->pos = vec_add(cam->pos, vec_scale(cam->vec_dir, 6));
	if (keysym == 0xff54)
		cam->pos = vec_substact(cam->pos, vec_scale(cam->vec_dir, 6));
	return (keysym);
}

int	handle_key_input(int keysym, t_mini *mini)
{
	t_cam	*cam;

	mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	cam = &mini->sc.cam[mini->cam_lock];
	if (keysym == 0xff1b)
		close_window(mini);
	if (keysym == 0xff53)
		cam->pos = vec_add(cam->pos, vec_scale(cam->right, 6));
	if (keysym == 0xff51)
		cam->pos = vec_substact(cam->pos, vec_scale(cam->right, 6));
	return (handle_key_input_bis(keysym, mini, cam));
}

int	handle_mouse_input(int keysym, int x, int y, t_mini *mini)
{
	(void)x;
	(void)y;
	if (keysym == 4)
	{
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
		if (mini->sc.cam[mini->cam_lock].fov * 0.85 < 20)
			return (keysym);
		mini->sc.cam[mini->cam_lock].fov *= 0.85;
	}
	if (keysym == 5)
	{
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
		if (mini->sc.cam[mini->cam_lock].fov * 1.15 > 180)
			return (keysym);
		mini->sc.cam[mini->cam_lock].fov *= 1.15;
	}
	return (keysym);
}
