/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:11:16 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/02 13:15:25 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_boolean	run_thread_utils(t_mini *mini, int *h)
{
	mini->thid = malloc(sizeof(pthread_t) * N_THREAD);
	if (!mini->thid)
		return (false);
	set_up_cam(mini);
	mini->sc.cam[mini->cam_lock].vec_dir = vec_normalize(
			mini->sc.cam[mini->cam_lock].vec_dir);
	mini->left_corner = get_left_corner_viewport(*mini);
	*h = HEIGHT / N_THREAD;
	mini->min = 0;
	mini->max = *h;
	return (true);
}

t_boolean	wait_for_thread(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < N_THREAD)
	{
		pthread_join(mini->thid [i], NULL);
		pthread_mutex_lock(mini->error);
		if (mini->thread_crash)
			return (kill_all_thread(mini->thid, i),
				pthread_mutex_unlock(mini->error), false);
		pthread_mutex_unlock(mini->error);
		i++;
	}
	return (true);
}

t_boolean	run_thread(t_mini *mini)
{
	int			h;
	int			i;

	if (!run_thread_utils(mini, &h))
		return (false);
	i = -1;
	while (++i < N_THREAD)
	{
		sem_wait(mini->m_cast);
		if (i != 0)
			mini->min = mini->max;
		mini->max = h + (h * i);
		if (pthread_create(&mini->thid [i], NULL, cast, mini) < 0)
			return (thread_create_failed(mini->thid, i), free(mini->thid),
				false);
	}
	if (!wait_for_thread(mini))
		return (free(mini->thid), false);
	free(mini->thid);
	mini->thid = NULL;
	mlx_put_image_to_window(mini->display.mlx, mini->display.mlx_win,
		mini->display.img.img, 0, 0);
	return (true);
}

int	render_loop(t_mini *mini)
{
	unsigned long	time;
	unsigned long	limit;

	time = 0;
	limit = 250;
	time = chrono() - mini->last_input;
	if (mini->block_size == 1)
		return (0);
	if (mini->block_size > 1 && time >= limit
		&& mini->block_size > BLOCK_SIZE_MIN)
	{
		if (mini->block_size == 2)
				mini->block_size--;
		else
			mini->block_size -= 2;
	}
	if (!run_thread(mini))
	{
		write(2, "Something goes wrong during rendering.\n", 40);
		close_window(mini);
	}
	return (0);
}
