/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amedenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:42:36 by amedenec          #+#    #+#             */
/*   Updated: 2025/11/01 10:42:44 by amedenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	mini->sc.objet_tr[mini->n_tr]
		.roughness_default = get_roughness_default(buffer);
	mini->n_tr++;
}
