/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 15:21:42 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-31 15:21:42 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec_rotate(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	res;
	double	c;
	double	s;
	double	dot;

	c = cos(angle);
	s = sin(angle);
	dot = vec_dot(axis, v);
	res.x = v.x * c + (axis.y * v.z - axis.z * v.y)
		* s + axis.x * dot * (1 - c);
	res.y = v.y * c + (axis.z * v.x - axis.x * v.z)
		* s + axis.y * dot * (1 - c);
	res.z = v.z * c + (axis.x * v.y - axis.y * v.x)
		* s + axis.z * dot * (1 - c);
	return (res);
}

int	handle_mouse_press(int button, int x, int y, t_mini *mini)
{
	if (button == 2)
	{
		mini->mouse.mid_pressed = 1;
		mini->mouse.prev_x = x;
		mini->mouse.prev_y = y;
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
	}
	else if (button == 4)
	{
		mini->sc.cam[mini->cam_lock].pos = vec_add(
				mini->sc.cam[mini->cam_lock].pos,
				vec_scale(mini->sc.cam[mini->cam_lock].vec_dir, 10));
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
	}
	else if (button == 5)
	{
		mini->sc.cam[mini->cam_lock].pos = vec_substact(
				mini->sc.cam[mini->cam_lock].pos,
				vec_scale(mini->sc.cam[mini->cam_lock].vec_dir, 10));
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
	}
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_mini *mini)
{
	(void)x;
	(void)y;
	if (button == 2)
		mini->mouse.mid_pressed = 0;
	return (0);
}

int	handle_key_press(int keycode, t_mini *mini)
{
	if (keycode == 0xffe1)
		mini->mouse.shift_pressed = 1;
	if (keycode == 0xff1b)
		close_window(mini);
	return (0);
}

int	handle_key_release(int keycode, t_mini *mini)
{
	if (keycode == 0xffe1)
		mini->mouse.shift_pressed = 0;
	return (0);
}
