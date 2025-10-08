/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:10:15 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/08 19:41:13 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	handle_key_input_bis(int keysym, t_mini *mini, t_cam *cam)
{
	if (keysym == 0xff52)
	{
		
		cam->pos = vec_add(cam->pos, vec_scale(cam->vec_dir, 6));
		run_thread(mini);
	}
	if (keysym == 0xff54)
	{
		cam->pos = vec_substact(cam->pos, vec_scale(cam->vec_dir, 6));
		run_thread(mini);
	}
	return (keysym);
}

int	handle_key_input(int keysym, t_mini *mini)
{
	t_cam	*cam;

	cam = &mini->sc.cam[mini->cam_lock];
	if (keysym == 0xff1b)
		close_window(mini);
	if (keysym == 0xff53)
	{
		cam->pos = vec_add(cam->pos, vec_scale(cam->right, 6));
		run_thread(mini);
	}
	if (keysym == 0xff51)
	{
		cam->pos = vec_substact(cam->pos, vec_scale(cam->right, 6));
		run_thread(mini);
	}
	return (handle_key_input_bis(keysym, mini, cam));
}

int	handle_mouse_input(int keysym, int x, int y, t_mini *mini)
{
	(void)mini;
	//printf("x : %d, y : %d\n");
	if (keysym == 4)
	{
		if (mini->sc.cam[mini->cam_lock].fov * 0.85 < 20)
			return (keysym);
		mini->sc.cam[mini->cam_lock].fov *= 0.85;
	}
	if (keysym == 5)
	{
		if (mini->sc.cam[mini->cam_lock].fov * 1.15 > 180)
			return (keysym);
		mini->sc.cam[mini->cam_lock].fov *= 1.15;
	}
	run_thread(mini);
	return (keysym);
}
