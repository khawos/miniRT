/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:28:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/12 14:36:52 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_cam(t_mini *mini, char *buffer)
{
	mini->sc.cam[mini->n_cam].id = mini->n_cam;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.cam[mini->n_cam].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.cam[mini->n_cam].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.cam[mini->n_cam].pos.z = __atoi_double(&buffer);
	mini->sc.cam[mini->n_cam].vec_dir.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.cam[mini->n_cam].vec_dir.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.cam[mini->n_cam].vec_dir.z = __atoi_double(&buffer);
	mini->sc.cam[mini->n_cam].fov = __atoi_double(&buffer);
	mini->n_cam++;
}

void	parse_a(t_mini	*mini, char	*buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = A;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].ratio = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[2] = __atoi_double(&buffer);
	mini->n_a++;
	mini->N_OBJ++;
}

void	parse_l(t_mini	*mini, char	*buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = L;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].ratio = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[2] = __atoi_double(&buffer);
	mini->n_l++;
	mini->N_OBJ++;
}

void	parse_sp(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = sp;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].diameter = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[2] = __atoi_double(&buffer);
	mini->n_sp++;
	mini->N_OBJ++;
}

void	parse_pl(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = pl;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].vec_dir.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].vec_dir.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].vec_dir.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[2] = __atoi_double(&buffer);
	mini->n_pl++;
	mini->N_OBJ++;
}

void	parse_cy(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = cy;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].pos.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].vec_dir.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].vec_dir.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].vec_dir.z = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].diameter = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].height = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color[0] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[1] = __atoi_double(&buffer);
	buffer++;
	mini->sc.objet[mini->N_OBJ].color[2] = __atoi_double(&buffer);
	mini->n_cy++;
	mini->N_OBJ++;
}
