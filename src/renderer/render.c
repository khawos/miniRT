/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:11:16 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/17 10:46:19 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	run_thread_utils(t_mini *mini, int *h)
{
	mini->sc.cam[mini->cam_lock].vec_dir = vec_normalize(
			mini->sc.cam[mini->cam_lock].vec_dir);
	mini->left_corner = get_left_corner_viewport(*mini);
	*h = HEIGHT / N_THREAD;
	mini->min = 0;
	mini->max = *h;
}

t_boolean	run_thread(t_mini *mini)
{
	int			h;
	pthread_t	thid[N_THREAD];
	int			i;

	set_up_cam(mini);
	run_thread_utils(mini, &h);
	i = -1;
	while (++i < N_THREAD)
	{
		sem_wait(mini->m_cast);
		if (i != 0)
			mini->min = mini->max;
		mini->max = h + (h * i);
		if (pthread_create(&thid[i], NULL, cast, mini) < 0)
			return (false);									// ATTENTION FREE + KILL THREAD
	}
	i = -1;
	while (++i < N_THREAD)
		pthread_join(thid[i], NULL);
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
	if (mini->block_size > 1 && time >= limit && mini->block_size > BLOCK_SIZE_MIN)
	{
		if (mini->block_size == 2)
			mini->block_size--;
		else
			mini->block_size -= 2;
	}
	run_thread(mini);
	return (0);
}
