/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:28:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025/09/25 14:34:10 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_cam(t_mini *mini, char *buffer)
{
	mini->sc.cam[mini->n_cam].id = mini->n_cam;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.cam[mini->n_cam].pos = get_point(&buffer);
	mini->sc.cam[mini->n_cam].vec_dir = get_point(&buffer);
	mini->sc.cam[mini->n_cam].fov = __atoi_double(&buffer);
	mini->n_cam++;
}

void	parse_a(t_mini	*mini, char	*buffer)
{
	mini->sc.light[mini->N_LIGHT].id = mini->N_OBJ;
	mini->sc.light[mini->N_LIGHT].type = A;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.light[mini->N_LIGHT].ratio = __atoi_double(&buffer);
	mini->sc.light[mini->N_LIGHT].color = get_color(&buffer);
	mini->n_a++;
	mini->N_LIGHT++;
}

void	parse_l(t_mini	*mini, char	*buffer)
{
	mini->sc.light[mini->N_LIGHT].id = mini->N_OBJ;
	mini->sc.light[mini->N_LIGHT].type = L;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.light[mini->N_LIGHT].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.light[mini->N_LIGHT].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.light[mini->N_LIGHT].pos.z = __atoi_double(&buffer);
	mini->sc.light[mini->N_LIGHT].ratio = __atoi_double(&buffer);
	mini->sc.light[mini->N_LIGHT].color = get_color(&buffer);
	mini->n_l++;
	mini->N_LIGHT++;
}

void	parse_sp(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = sp;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos = get_point(&buffer);
	mini->sc.objet[mini->N_OBJ].diameter = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color = get_color(&buffer);
	mini->sc.objet[mini->N_OBJ].spec = get_spec(buffer);
	mini->n_sp++;
	mini->N_OBJ++;
}

void	parse_pl(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = pl;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos = get_point(&buffer);
	mini->sc.objet[mini->N_OBJ].vec_dir = get_point(&buffer);
	mini->sc.objet[mini->N_OBJ].color = get_color(&buffer);
	mini->sc.objet[mini->N_OBJ].spec = get_spec(buffer);
	mini->n_pl++;
	mini->N_OBJ++;
}

void	parse_tr(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = tr;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].p0 = get_point(&buffer);
	mini->sc.objet[mini->N_OBJ].p1 = get_point(&buffer);
	mini->sc.objet[mini->N_OBJ].p2 = get_point(&buffer);
	mini->sc.objet[mini->N_OBJ].color = get_color(&buffer);
	mini->sc.objet[mini->N_OBJ].spec = get_spec(buffer);
	mini->n_tr++;
	mini->N_OBJ++;
}