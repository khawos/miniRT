/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:20:18 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/30 15:48:03 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	kill_all_thread(pthread_t *thid, int n)
{
	int	i;

	i = 0;
	while (i < N_THREAD && thid)
	{
		if (i == n)
			i++;
		pthread_detach(thid[i]);
		i++;
	}
}

void	thread_create_failed(pthread_t *thid, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_detach(thid[i]);
		i++;
	}
}

void	error_in_thread(t_mini *mini)
{
	pthread_mutex_lock(mini->error);
	mini->thread_crash = true;
	pthread_mutex_unlock(mini->error);
}
