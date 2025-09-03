/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-02 23:35:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025-09-02 23:35:09 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void free_mini(t_mini *mini){

    int i;

    i = -1;
    while (i++ < mini->scene.nb_cam)
        free(mini->scene.cam[i].name);
    free(mini->scene.cam);
    i = -1;
    while (i++ < mini->scene.nb_objet)
        free(mini->scene.objet[i].name);
    free(mini->scene.objet);
}