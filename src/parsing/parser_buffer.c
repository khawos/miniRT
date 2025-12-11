/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <amedenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 00:28:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025/11/12 16:21:52 by amedenec         ###   ########.fr       */
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
	mini->sc.ambiant.id = mini->n_obj;
	mini->sc.ambiant.type = A;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.ambiant.ratio = __atoi_double(&buffer);
	mini->sc.ambiant.color = get_color(&buffer);
	mini->n_a++;
}

void	parse_l(t_mini	*mini, char	*buffer)
{
	mini->sc.light[mini->n_light].id = mini->n_obj;
	mini->sc.light[mini->n_light].type = L;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.light[mini->n_light].pos.x = __atoi_double(&buffer);
	buffer++;
	mini->sc.light[mini->n_light].pos.y = __atoi_double(&buffer);
	buffer++;
	mini->sc.light[mini->n_light].pos.z = __atoi_double(&buffer);
	mini->sc.light[mini->n_light].ratio = __atoi_double(&buffer);
	mini->sc.light[mini->n_light].color = get_color(&buffer);
	mini->n_l++;
	mini->n_light++;
}

t_boolean	parse_sp(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->n_obj].id = mini->n_obj;
	mini->sc.objet[mini->n_obj].type = sp;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->n_obj].pos = get_point(&buffer);
	mini->sc.objet[mini->n_obj].diameter = __atoi_double(&buffer);
	mini->sc.objet[mini->n_obj].color = get_color(&buffer);
	mini->sc.objet[mini->n_obj].spec = get_spec(buffer);
	mini->sc.objet[mini->n_obj]
		.roughness_default = get_roughness_default(buffer);
	if (get_material(&mini->sc.objet[mini->n_obj], buffer) == 0)
		return (false);
	mini->sc.objet[mini->n_obj].mat.ior = get_ior(buffer);
	mini->n_sp++;
	mini->n_obj++;
	return (true);
}

t_boolean	parse_pl(t_mini *mini, char *buffer)
{
	mini->sc.objet[mini->n_obj].id = mini->n_obj;
	mini->sc.objet[mini->n_obj].type = pl;
	while (ft_isalpha(*buffer))
		buffer++;
	mini->sc.objet[mini->n_obj].pos = get_point(&buffer);
	mini->sc.objet[mini->n_obj].vec_dir = get_point(&buffer);
	mini->sc.objet[mini->n_obj].color = get_color(&buffer);
	mini->sc.objet[mini->n_obj].spec = get_spec(buffer);
	mini->sc.objet[mini->n_obj]
		.roughness_default = get_roughness_default(buffer);
	if (get_material(&mini->sc.objet[mini->n_obj], buffer) == 0)
		return (false);
	mini->n_pl++;
	mini->n_obj++;
	return (true);
}
