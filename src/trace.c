/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-06 14:22:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-06 14:22:31 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_boolean	trace(t_mini *mini)
{
	t_vec3	vec;

	find_first_ray_pos(&vec, mini);
	return (true);
}