/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:28:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025/10/19 14:19:11 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (!get_material(&mini->sc.objet[mini->N_OBJ], buffer));
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
	mini->sc.objet_tr[mini->n_tr].id = mini->n_tr;
	mini->sc.objet_tr[mini->n_tr].type = tr;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet_tr[mini->n_tr].p0 = get_point(&buffer);
	mini->sc.objet_tr[mini->n_tr].p1 = get_point(&buffer);
	mini->sc.objet_tr[mini->n_tr].p2 = get_point(&buffer);
	mini->sc.objet_tr[mini->n_tr].color = get_color(&buffer);
	mini->sc.objet_tr[mini->n_tr].spec = get_spec(buffer);
	mini->n_tr++;
}