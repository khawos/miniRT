/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_controls_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:27:47 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 16:30:18 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_boolean	is_a_bad_rotation(t_vec3 v_new, t_vec3 v_old)
{
	if ((v_old.x > 0 && v_new.x < 0)
		&& (v_old.y < 0 && v_new.y > 0) && (v_old.z > 0.999 || v_old.z < 0.001))
		return (true);
	if ((v_old.x < 0 && v_new.x > 0)
		&& (v_old.y > 0 && v_new.y < 0) && (v_old.z > 0.999 || v_old.z < 0.001))
		return (true);
	if ((v_old.x > 0 && v_new.x > 0)
		&& (v_old.x < 0 && v_new.y < 0) && (v_old.z > 0.999 || v_old.z < 0.001))
		return (true);
	if ((v_old.x > 0 && v_old.y > 0)
		&& (v_new.x < 0 && v_new.y < 0) && (v_old.z > 0.999 || v_old.z < 0.001))
		return (true);
	if ((v_old.x < 0 && v_old.y < 0)
		&& (v_new.x > 0 && v_new.y > 0) && (v_old.z > 0.999 || v_old.z < 0.001))
		return (true);
	return (false);
}

void	handle_mouse_compute(t_cam *cam, t_mini *mini, double dx, double dy)
{
	t_vec3	up_world;
	double	yaw;
	double	pitch;
	t_vec3	vec_dir_tmp;

	if (mini->mouse.shift_pressed)
	{
		up_world = (t_vec3){0, 0, 1};
		yaw = dx * -0.002;
		pitch = dy * -0.002;
		vec_dir_tmp = cam->vec_dir;
		cam->vec_dir = vec_rotate(cam->vec_dir, up_world, -yaw);
		get_right_local_vector(mini, mini->cam_lock);
		get_up_local_vector(mini, mini->cam_lock);
		cam->vec_dir = vec_rotate(cam->vec_dir, cam->right, -pitch);
		cam->vec_dir = vec_normalize(cam->vec_dir);
		get_right_local_vector(mini, mini->cam_lock);
		get_up_local_vector(mini, mini->cam_lock);
		if (is_a_bad_rotation(cam->vec_dir, vec_dir_tmp))
			cam->vec_dir = vec_dir_tmp;
	}
	else
		cam->pos = vec_add(vec_add(cam->pos, vec_scale(cam->right, dx * 0.3)),
				vec_scale(cam->up, -dy * 0.3));
}

int	handle_mouse_move(int x, int y, t_mini *mini)
{
	t_cam	*cam;
	double	dx;
	double	dy;

	if (!mini->mouse.mid_pressed)
		return (0);
	cam = &mini->sc.cam[mini->cam_lock];
	dx = (mini->mouse.prev_x - x);
	dy = (mini->mouse.prev_y - y);
	mini->mouse.prev_x = x;
	mini->mouse.prev_y = y;
	handle_mouse_compute(cam, mini, dx, dy);
	mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	return (0);
}
