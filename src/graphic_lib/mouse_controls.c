
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
	res.x = v.x * c + (axis.y * v.z - axis.z * v.y) * s + axis.x * dot * (1 - c);
	res.y = v.y * c + (axis.z * v.x - axis.x * v.z) * s + axis.y * dot * (1 - c);
	res.z = v.z * c + (axis.x * v.y - axis.y * v.x) * s + axis.z * dot * (1 - c);
	return (res);
}

int	handle_mouse_press(int button, int x, int y, t_mini *mini)
{
	if (button == 2) // clic molette
	{
        printf("clic molette\n");

		mini->mouse.mid_pressed = 1;
		mini->mouse.prev_x = x;
		mini->mouse.prev_y = y;
        mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
	}
	else if (button == 4)
	{
        printf("molette haut\n");
		if (mini->sc.cam[mini->cam_lock].fov * 0.85 >= 20)
			mini->sc.cam[mini->cam_lock].fov *= 0.85;
		mini->last_input = chrono();
		mini->block_size = BLOCK_SIZE_MAX;
	}
	else if (button == 5)
	{
        printf("molette bas\n");
		if (mini->sc.cam[mini->cam_lock].fov * 1.15 <= 180)
			mini->sc.cam[mini->cam_lock].fov *= 1.15;
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
    {
        printf("clique molette relacher\n");
		mini->mouse.mid_pressed = 0;
    }
	return (0);
}

int	handle_mouse_move(int x, int y, t_mini *mini)
{
	t_cam	*cam;
	double	dx;
	double	dy;
	t_vec3	new_dir;

    mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	if (!mini->mouse.mid_pressed)
		return (0);
	cam = &mini->sc.cam[mini->cam_lock];
	dx = (x - mini->mouse.prev_x);
	dy = (y - mini->mouse.prev_y);
	mini->mouse.prev_x = x;
	mini->mouse.prev_y = y;

	if (mini->mouse.shift_pressed)
	{
		double	yaw = dx * 0.002;
		double	pitch = dy * 0.002;

		// rota axe "up" (gauche/droite)
		new_dir = vec_rotate(cam->vec_dir, cam->up, -yaw);

		// Rota axe "right" (haut/bas)
		new_dir = vec_rotate(new_dir, cam->right, -pitch);

		// Normal
		cam->vec_dir = vec_normalize(new_dir);
		get_right_local_vector(mini, mini->cam_lock);
		get_up_local_vector(mini, mini->cam_lock);
	}
	else
	{
		cam->pos = vec_add(cam->pos, vec_scale(cam->right, dx * 0.1));
		cam->pos = vec_add(cam->pos, vec_scale(cam->up, -dy * 0.1));
	}
	return (0);
}

int	handle_key_press(int keycode, t_mini *mini)
{
	if (keycode == 0xffe1) // Shift gauche
    {
        printf("shift presse\n");
		mini->mouse.shift_pressed = 1;
    }
	return (0);
}

int	handle_key_release(int keycode, t_mini *mini)
{
	if (keycode == 0xffe1)
    {
        printf("shift relache\n");
		mini->mouse.shift_pressed = 0;
    }
	return (0);
}
