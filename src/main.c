/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:40:37 by amedenec          #+#    #+#             */
/*   Updated: 2025/11/02 12:58:31 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	mini.s_img = sem_open("/image", O_CREAT | O_EXCL, 0644, 24);
	set_up_cam(&mini);
	mini.sc.cam[mini.cam_lock].vec_dir = vec_normalize(
			mini.sc.cam[mini.cam_lock].vec_dir);
	set_normal_tr(&mini);
	if (!run_thread(&mini))
		return (-1);
	toggle_hook(mini);
	sem_close(mini.m_cast);
	sem_close(mini.s_img);
	sem_unlink("/image");
	sem_unlink("/cast_init");
	return (0);
}
