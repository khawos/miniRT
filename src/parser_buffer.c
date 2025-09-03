/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-03 00:28:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-03 00:28:07 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_cam(t_mini *mini, char *buffer)
{
	static int	nb;

	mini->scene.cam[nb].id = nb;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->scene.cam[nb].pos[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.cam[nb].pos[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.cam[nb].pos[2] = __atoi_double(&buffer);
	mini->scene.cam[nb].vec_dir[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.cam[nb].vec_dir[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.cam[nb].vec_dir[2] = __atoi_double(&buffer);
	mini->scene.cam[nb].fov = __atoi_double(&buffer);
	nb++;
}

void	parse_a(t_mini	*mini, char	*buffer)
{
	static int	nb;

	mini->scene.objet[nb].id = nb;
	mini->scene.objet[nb].type = A;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->scene.objet[nb].ratio =__atoi_double(&buffer);
	mini->scene.objet[nb].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[2] = __atoi_double(&buffer);
}

void	parse_l(t_mini	*mini, char	*buffer)
{
	static int	nb;

	mini->scene.objet[nb].id = nb;
	mini->scene.objet[nb].type = L;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->scene.objet[nb].pos[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[2] = __atoi_double(&buffer);	
	mini->scene.objet[nb].ratio = __atoi_double(&buffer);
	mini->scene.objet[nb].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[2] = __atoi_double(&buffer);
}

void	parse_sp(t_mini *mini, char *buffer)
{
	static int	nb;

	mini->scene.objet[nb].id = nb;
	mini->scene.objet[nb].type = sp;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->scene.objet[nb].pos[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[1] =__atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[2] = __atoi_double(&buffer);	
	mini->scene.objet[nb].diameter = __atoi_double(&buffer);
	mini->scene.objet[nb].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[2] = __atoi_double(&buffer);
}

void	parse_pl(t_mini *mini, char *buffer)
{
	static int	nb;

	mini->scene.objet[nb].id = nb;
	mini->scene.objet[nb].type = pl;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->scene.objet[nb].pos[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[2] = __atoi_double(&buffer);	
	mini->scene.objet[nb].vec_dir[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].vec_dir[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].vec_dir[2] = __atoi_double(&buffer);
	mini->scene.objet[nb].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[2] = __atoi_double(&buffer);
}

void	parse_cy(t_mini *mini, char *buffer)
{
	static int	nb;

	mini->scene.objet[nb].id = nb;
	mini->scene.objet[nb].type = cy;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->scene.objet[nb].pos[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].pos[2] = __atoi_double(&buffer);	
	mini->scene.objet[nb].vec_dir[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].vec_dir[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].vec_dir[2] = __atoi_double(&buffer);
	mini->scene.objet[nb].diameter = __atoi_double(&buffer);
	mini->scene.objet[nb].height = __atoi_double(&buffer);
	mini->scene.objet[nb].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->scene.objet[nb].color[2] = __atoi_double(&buffer);
}
