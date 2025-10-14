/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-14 09:39:48 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-14 09:39:48 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int *cat_int_array(int *a, int *b, int size_a, int size_b)
{
    int *new;
    int i;
    int j;
    
    if (!a)
        return (b);
    new = malloc(sizeof(int) * (size_a + size_b));
    if (!new)
        return (free(a), NULL);
    i = -1;
    j = -1;
    while (++i < size_a)
        new[i] = a[i];
    while (++j < size_b)
        new[i + j] = b[j];
    free(a);
    return (new);
}

int *search_tr_in_tree(t_bvh *bvh, t_vec3 origin, t_vec3 ray_direction, int *size)
{
    int *tr_in_view;
    int i;

    tr_in_view = NULL;
    *size = 0;
    i = 0;
    (void)bvh;
    (void)origin;
    (void)ray_direction;
    (void)size;
    // il manque un gros bout j'ai pas la vision 
    // i = 0;
    // if (bounds_in_view(bvh->bounds, origin, ray_direction))
    // {
    //     tr_in_view = cat_int_array(tr_in_view, bvh->idx_tr_hbv, *size, bvh->n_obj);
    //     if (!tr_in_view)
    //         return (*size = -1, NULL);
    //     *size = *size + bvh->n_obj;
    // }
    return (tr_in_view);
}