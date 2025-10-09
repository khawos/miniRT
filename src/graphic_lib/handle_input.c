/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:10:15 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/09 14:50:59 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	handle_key_input_bis(int keysym, t_mini *mini, t_cam *cam)
{
	if (keysym == 0xff52)
		cam->pos = vec_add(cam->pos, vec_scale(cam->vec_dir, 6));
	if (keysym == 0xff54)
		cam->pos = vec_substact(cam->pos, vec_scale(cam->vec_dir, 6));
	return (keysym);
}

int	handle_key_input(int keysym, t_mini *mini)
{
	t_cam	*cam;

	pthread_mutex_lock(&mini->render_mutex);
	mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	pthread_mutex_unlock(&mini->render_mutex);
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
	if (keysym == 4)
	{
		pthread_mutex_lock(&mini->render_mutex);
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
		pthread_mutex_unlock(&mini->render_mutex);
		if (mini->sc.cam[mini->cam_lock].fov * 0.85 < 20)
			return (keysym);
		mini->sc.cam[mini->cam_lock].fov *= 0.85;
	}
	if (keysym == 5)
	{
		pthread_mutex_lock(&mini->render_mutex);
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
		pthread_mutex_unlock(&mini->render_mutex);
		if (mini->sc.cam[mini->cam_lock].fov * 1.15 > 180)
			return (keysym);
		mini->sc.cam[mini->cam_lock].fov *= 1.15;
	}
	return (keysym);
}
