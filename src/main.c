/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:40:37 by amedenec          #+#    #+#             */
/*   Updated: 2025/10/09 14:56:22 by amedenec         ###   ########.fr       */
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
	mini->last_input = chrono();
	mini->block_size = BLOCK_SIZE_MAX;
	if (!parser(mini, av))
		return (false);
	if (pthread_mutex_init(&mini->render_mutex, NULL) < 0)
		return (false);												// ATTENTION FREE
	mini->sc.ambiant = get_ambiant(mini);
	if (!open_window(mini))
		return (false);
	return (true);
}

t_boolean	run_thread(t_mini *mini)
{
	int			h;
	pthread_t	thid[N_THREAD];
	int			i;

	set_up_cam(mini);
	mini->sc.cam[mini->cam_lock].vec_dir = vec_normalize(
			mini->sc.cam[mini->cam_lock].vec_dir);
	mini->left_corner = get_left_corner_viewport(*mini);
	h = HEIGHT / N_THREAD;
	mini->min = 0;
	mini->max = h;
	i = -1;
	while (++i < N_THREAD)
	{
		sem_wait(mini->m_cast);
		if (i != 0)
			mini->min = mini->max;
		mini->max = h + (h * i);
		if (pthread_create(&thid[i], NULL, cast, mini) < 0)
			return (false);										// ATTENTION FREE + KILL THREAD
	}
	i = -1;
	while (++i < N_THREAD)
		pthread_join(thid[i], NULL);
	mlx_put_image_to_window(mini->display.mlx, mini->display.mlx_win,
		mini->display.img.img, 0, 0);
	return (true);
}

int render_loop(t_mini *mini)
{
	unsigned long	time;
	unsigned long	limit;

	time = 0;
	limit = 1500;
	pthread_mutex_lock(&mini->render_mutex);
	time = chrono() - mini->last_input;
	if (mini->block_size > 1 && time >= limit)
	{
		if (mini->block_size == 2)
			mini->block_size--;
		else
			mini->block_size -= 2;
	}
	pthread_mutex_unlock(&mini->render_mutex);
	run_thread(mini);
}

int	main(int ac, char **av)
{
	t_mini	mini;

	if (ac != 2)
		return (1);
	if (!init(&mini, av))
		return (1);
	sem_unlink("/cast_init");
	sem_unlink("/image");
	mini.m_cast = sem_open("/cast_init", O_CREAT | O_EXCL, 0644, 1);
	mini.s_img = sem_open("/image", O_CREAT | O_EXCL, 0644, 1);
	set_up_cam(&mini);
	mini.sc.cam[mini.cam_lock].vec_dir = vec_normalize(
			mini.sc.cam[mini.cam_lock].vec_dir);
	mlx_hook(mini.display.mlx_win, DestroyNotify,
		StructureNotifyMask, &close_window, &mini);
	mlx_hook(mini.display.mlx_win, KeyPress, KeyPressMask,
		handle_key_input, (t_mini *)&mini);
	mlx_mouse_hook(mini.display.mlx_win, handle_mouse_input, (t_mini *)&mini);
	mlx_loop_hook (mini.display.mlx, render_loop, &mini);
	mlx_loop(mini.display.mlx);
	sem_close(mini.m_cast);
	sem_unlink("/cast_init");
	pthread_mutex_destroy(&mini.render_mutex);
	return (0);
}
