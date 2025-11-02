/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:28:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/01 10:38:13 by amedenec         ###   ########.fr       */
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
	mini->sc.ambiant.id = mini->N_OBJ;
	mini->sc.ambiant.type = A;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.ambiant.ratio = __atoi_double(&buffer);
	mini->sc.ambiant.color = get_color(&buffer);
	mini->n_a++;
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

t_boolean	parse_sp(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->N_OBJ].id = mini->N_OBJ;
	mini->sc.objet[mini->N_OBJ].type = sp;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->N_OBJ].pos = get_point(&buffer);
	mini->sc.objet[mini->N_OBJ].diameter = __atoi_double(&buffer);
	mini->sc.objet[mini->N_OBJ].color = get_color(&buffer);
	mini->sc.objet[mini->N_OBJ].spec = get_spec(buffer);
	mini->sc.objet[mini->N_OBJ]
		.roughness_default = get_roughness_default(buffer);
	if (get_material(&mini->sc.objet[mini->N_OBJ], buffer) == 0)
		return (false);
	mini->n_sp++;
	mini->N_OBJ++;
	return (true);
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
	mini->sc.objet[mini->N_OBJ]
		.roughness_default = get_roughness_default(buffer);
	mini->n_pl++;
	mini->N_OBJ++;
}
